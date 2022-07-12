//
//  Controller.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/18.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import "Controller.h"
#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonHMAC.h>

#define SC_CONTROL_DEF_PIN             @"57289961"

@implementation Controller
@synthesize control_sock, control_data, ack_data;

-(id)init
{
    NSError *err;
    control_sock = [[AsyncUdpSocket alloc]initWithDelegate:self];
    [control_sock bindToPort:(LOCAL_PORT_NUM) error:&err];
    m_mode = MODE_INIT;
    m_result = RTK_FAILED;
    
    return [super init];
}

-(void)dealloc
{
#ifdef ARC
    [control_data release];
    [control_sock dealloc];
    [ack_data release];
    [m_dev_pin release];

    [super dealloc];
#endif
}

-(void)rtk_sc_close_sock
{
    if (![control_sock isClosed]) {
        NSLog(@"m_controller close");
        [control_sock close];
    }
}
-(void)rtk_sc_reopen_sock
{
    NSError *err;
    if ([control_sock isClosed]) {
        NSLog(@"m_controller reopen");
        control_sock = [[AsyncUdpSocket alloc]initWithDelegate:self];
        [control_sock bindToPort:(LOCAL_PORT_NUM) error:&err];
    }
}

-(int)rtk_sc_get_mode
{
    return m_mode;
}

-(int) rtk_sc_get_control_result
{
    return (m_result==1)?RTK_SUCCEED:RTK_FAILED;
}

- (unsigned int)rtk_sc_convert_host_to_ip: (NSString *)host
{
    unsigned char ip[4] = {0x0};
    int idx = 3;
    NSArray *arr = [host componentsSeparatedByString:@"."];
    for(NSString *s in arr)
    {
        int a = [s intValue];
        ip[idx] = a & 0xFF;
        idx--;
    }
    unsigned int ret;
    memcpy(&ret, ip, 4);

    return ret;
}

-(void)rtk_sc_gen_control_data: (unsigned int)type pin: (NSString *)pin name: (NSString *)name
{
    if (type==RTK_SC_CONTROL_DELETE) {
        [self gen_control_data:REQ_DEL_PROFILE length:(CONTROL_DATA_LEN-1-1-2) psw:SC_CONTROL_DEF_PIN dev_pin:pin name:name];
        m_mode = MODE_CONTROL;
    }else if(type==RTK_SC_CONTROL_RENAME){
        [self gen_control_data:REQ_RENAME_DEV length:(unsigned int)(CONTROL_DATA_LEN-1-1-2+[name length]) psw:SC_CONTROL_DEF_PIN dev_pin:pin name:name];
        m_mode = MODE_CONTROL;
    }else{
        NSLog(@"ERROR: UNKNOWN CONTROL TYPE!!");
    }
}

-(void)rtk_sc_gen_control_new_AP_data:(NSString*)pin ssid:(NSString*)AP_ssid password:(NSString*)AP_pwd
{
    [self gen_control_newAP_data:REQ_NEW_AP length:(unsigned int)(CONTROL_DATA_LEN-1-1-2+64+64) psw:SC_CONTROL_DEF_PIN dev_pin:pin name:AP_ssid password:AP_pwd];
    
    m_mode = MODE_CONTROL;
}

-(int)rtk_sc_send_control_data: (unsigned int)ip
{
    if (m_mode != MODE_CONTROL) {
        return RTK_FAILED;
    }
    
    int ret = RTK_FAILED;
    if(control_sock == nil){
        NSLog(@"udpSocket doesn't exist!!!");
        return -1;
    }
    
    NSString *host = [[NSString alloc] initWithString:[NSString stringWithFormat:@"%d.%d.%d.%d", (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>>8)&0xFF, ip&0xFF]];
    
    // send data(unicast)
    [control_sock receiveWithTimeout:-1 tag:0];
    
    BOOL result = [control_sock sendData:control_data toHost:host port:UNICAST_PORT_NUM withTimeout:-1 tag:0];
    // deal with send result
    if(!result)
        ret=RTK_FAILED;
    else
        ret=RTK_SUCCEED;
    
#ifdef ARC
    [host release];
#endif
    
    return ret;
}

/* private funcs */
- (void) gen_control_data:(unsigned char)flag length:(unsigned int)length psw:(NSString *)psw dev_pin:(NSString *)dev_pin name:(NSString *)name
{
    NSLog(@"Control: m_mode=%d", m_mode);
    unsigned char buffer[CONTROL_DATA_LEN*2]={0x0};
    unsigned int len = 0;
    unsigned char m_security_level = SC_USE_ENCRYPTION;
    m_dev_pin = [[NSString alloc] initWithString:dev_pin];
#ifdef ARC
    [m_dev_pin retain];
#endif
    
    /* flag */
    memcpy(buffer+len, &flag, 1);
    len+=1;
    NSLog(@"Control: flag = %02x", flag);
    
    /* security level */
    memcpy(buffer+len, &m_security_level, 1);
    len += 1;
    NSLog(@"Control: security level = %02x", m_security_level);
    
    /* length */
    const char *name_p = [name UTF8String];
    NSLog(@"Control: name=%s", name_p);
    unsigned char data_len[2]={0};
    if (flag == REQ_RENAME_DEV)
        data_len[1]= (unsigned char)(length+strlen(name_p));
    else
        data_len[1]= (unsigned char)(length);
    memcpy(buffer+len, data_len, 2);
    len+=2;
    NSLog(@"Control: length = %02x%02x", data_len[0], data_len[1]);
    
    /* Nonce: a random value */
    unsigned char nonce[64] = {0x0};
    int nonce_idx = 0;
    for (nonce_idx=0; nonce_idx<64; nonce_idx++) {
        nonce[nonce_idx] = 0 + rand()%255;
        //NSLog(@"[%d]: %02x", nonce_idx, nonce[nonce_idx]);
    }
    memcpy(buffer+len, nonce, 64);
    len += 64;
    
    NSLog(@"Control: default pin = %@", psw);
    NSLog(@"Control: dev pin = %@", dev_pin);
    const unsigned char *psw_char = (const unsigned char *)[psw cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int psw_len = (unsigned int)strlen((const char *)psw_char);
    const unsigned char *pin_char = (const unsigned char*)[dev_pin cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int dev_pin_len = (unsigned int)strlen((const char *)pin_char);
    
    unsigned char md5_buffer[64+64]={0x0};
    unsigned char md5_result[16] = {0x0};
    /* Digest1: md5 buffer is nonce+default_pin */
    //NSLog(@"Control: default_pin_char(%d) = %s", psw_len, psw_char);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, psw_char, psw_len);
    CC_MD5(md5_buffer, 64+psw_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    /* Digest2: md5 buffer is nonce+dev_pin */
    //NSLog(@"Control: dev pin_char(%d) = %s", dev_pin_len, pin_char);
    memset(md5_buffer, 0x0, 64+64);
    memset(md5_result, 0x0, 16);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, pin_char, dev_pin_len);
    CC_MD5(md5_buffer, 64+dev_pin_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    control_data = [NSData dataWithBytes:(const void*)buffer length:CONTROL_DATA_LEN];
#ifdef ARC
    [control_data retain];
#endif
    
    /* Add name if necessary */
    if (flag == REQ_RENAME_DEV) {
        NSMutableData *pkt = [NSMutableData dataWithData:control_data];
        NSData *b = [name dataUsingEncoding:NSUTF8StringEncoding];
        NSLog(@"dev name is(%d) %s", (unsigned int)[b length], (unsigned char *)[b bytes]);
        [pkt appendData:b];
        control_data = [NSData dataWithData:pkt];
    }
}

- (void) gen_control_newAP_data:(unsigned char)flag length:(unsigned int)length psw:(NSString *)psw dev_pin:(NSString *)dev_pin name:(NSString *)ap_ssid password:(NSString *)ap_pwd
{
    NSLog(@"Control: m_mode=%d", m_mode);
    unsigned char buffer[CONTROL_DATA_LEN*2]={0x0};
    unsigned int len = 0;
    unsigned char m_security_level = SC_USE_ENCRYPTION;
    m_dev_pin = [[NSString alloc] initWithString:dev_pin];
#ifdef ARC
    [m_dev_pin retain];
#endif
    
    /* flag */
    memcpy(buffer+len, &flag, 1);
    len+=1;
    //NSLog(@"Control: flag = %02x", flag);
    
    /* security level */
    memcpy(buffer+len, &m_security_level, 1);
    len += 1;
    //NSLog(@"Control: security level = %02x", m_security_level);
    
    /* length */
    const char *name_p = [ap_ssid UTF8String];
    NSLog(@"Control: name=%s", name_p);
    unsigned char data_len[2]={0};
    data_len[1]= (unsigned char)(length);
    memcpy(buffer+len, data_len, 2);
    len+=2;
    //NSLog(@"Control: length = %02x%02x", data_len[0], data_len[1]);
    
    /* Nonce: a random value */
    unsigned char nonce[64] = {0x0};
    int nonce_idx = 0;
    for (nonce_idx=0; nonce_idx<64; nonce_idx++) {
        nonce[nonce_idx] = 0 + rand()%255;
        //NSLog(@"[%d]: %02x", nonce_idx, nonce[nonce_idx]);
    }
    memcpy(buffer+len, nonce, 64);
    len += 64;
    
    //NSLog(@"Control: default pin = %@", psw);
    //NSLog(@"Control: dev pin = %@", dev_pin);
    const unsigned char *psw_char = (const unsigned char *)[psw cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int psw_len = (unsigned int)strlen((const char *)psw_char);
    const unsigned char *pin_char = (const unsigned char*)[dev_pin cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int dev_pin_len = (unsigned int)strlen((const char *)pin_char);
    
    unsigned char md5_buffer[64+64]={0x0};
    unsigned char md5_result[16] = {0x0};
    /* Digest1: md5 buffer is nonce+default_pin */
    //NSLog(@"Control: default_pin_char(%d) = %s", psw_len, psw_char);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, psw_char, psw_len);
    CC_MD5(md5_buffer, 64+psw_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    /* Digest2: md5 buffer is nonce+dev_pin */
    //NSLog(@"Control: dev pin_char(%d) = %s", dev_pin_len, pin_char);
    memset(md5_buffer, 0x0, 64+64);
    memset(md5_result, 0x0, 16);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, pin_char, dev_pin_len);
    CC_MD5(md5_buffer, 64+dev_pin_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    control_data = [NSData dataWithBytes:(const void*)buffer length:CONTROL_DATA_LEN];
#ifdef ARC
    [control_data retain];
#endif
    
    const unsigned char *char_ssid = (const unsigned char *)[ap_ssid cStringUsingEncoding:NSASCIIStringEncoding];
    const unsigned char *char_pwd = (const unsigned char *)[ap_pwd cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned char newProfle_buffer[64+64]={0x0};

    memcpy(newProfle_buffer,char_ssid,(int)[ap_ssid length]);
    memcpy(newProfle_buffer+64,char_pwd,[ap_pwd length]);
    
    NSData *newProfle_data = [NSData dataWithBytes:(const void*)newProfle_buffer length:64+64];
    
    NSMutableData *pkt = [NSMutableData dataWithData:control_data];
    [pkt appendData:newProfle_data];
    
    control_data = [NSData dataWithData:pkt];
    
    NSUInteger myLength = control_data.length;
    //NSLog(@"control_data.length:%lu",(unsigned long)myLength);
    
    NSUInteger pktLen = [control_data length];
    Byte *byteData = (Byte*)malloc(pktLen);
    memcpy(byteData, [control_data bytes], pktLen);
    
    /*const unsigned char *byte = [control_data bytes];
    unsigned int plength = (unsigned int)[control_data length];
    for (int i=0; i<plength; i++) {
        unsigned char n = byte[i];
        printf("[%d]%02x\n",i,n);
    }*/
    //NSLog(@"gen_control_newAP_data finish");
    
}

-(void)gen_control_ack_data:(unsigned char)control_type length:(unsigned int)length
{
    unsigned char buffer[ACK_TO_CONTROL_DATA_LEN]={0x0};
    unsigned int len = 0;
    unsigned char m_security_level = SC_USE_ENCRYPTION;
    NSString *psw = SC_CONTROL_DEF_PIN;
    NSString *dev_pin = m_dev_pin;
    
    /* flag */
    unsigned char flag = REQ_ACK;
    memcpy(buffer+len, &flag, 1);
    len+=1;
    //NSLog(@"Control ACK: flag = %02x", flag);
    
    /* length */
    unsigned char data_len[2]={0x0, (unsigned char)length};
    memcpy(buffer+len, data_len, 2);
    len+=2;
    //NSLog(@"Control ACK: length = %02x%02x", data_len[0], data_len[1]);
    
    /* security level */
    memcpy(buffer+len, &m_security_level, 1);
    len += 1;
    //NSLog(@"Control ACK: security level = %02x", m_security_level);
    
    /* Nonce: a random value */
    unsigned char nonce[64] = {0x0};
    int nonce_idx = 0;
    for (nonce_idx=0; nonce_idx<64; nonce_idx++) {
        nonce[nonce_idx] = 0 + rand()%255;
        //NSLog(@"[%d]: %02x", nonce_idx, nonce[nonce_idx]);
    }
    memcpy(buffer+len, nonce, 64);
    len += 64;
    
    //NSLog(@"Control ACK: default pin = %@", psw);
    //NSLog(@"Control ACK: dev pin = %@", dev_pin);
    const unsigned char *psw_char = (const unsigned char *)[psw cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int psw_len = (unsigned int)strlen((const char *)psw_char);
    const unsigned char *pin_char = (const unsigned char*)[dev_pin cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int dev_pin_len = (unsigned int)strlen((const char *)pin_char);
    
    unsigned char md5_buffer[64+64]={0x0};
    unsigned char md5_result[16] = {0x0};
    /* Digest1: md5 buffer is nonce+default_pin */
    //NSLog(@"Control ACK: default_pin_char(%d) = %s", psw_len, psw_char);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, psw_char, psw_len);
    CC_MD5(md5_buffer, 64+psw_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    /* Digest2: md5 buffer is nonce+dev_pin */
    //NSLog(@"Control ACK: dev pin_char(%d) = %s", dev_pin_len, pin_char);
    memset(md5_buffer, 0x0, 64+64);
    memset(md5_result, 0x0, 16);
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, pin_char, dev_pin_len);
    CC_MD5(md5_buffer, 64+dev_pin_len, md5_result);
    memcpy(buffer+len, md5_result, 16);
    len += 16;
    
    /* control type */
    NSLog(@"Control ACK: control type is %02x", control_type);
    unsigned char last_byte;
    switch (control_type) {
        case 0x22:
            last_byte = BIT(0);
            break;
        case 0x23:  //remove device
            last_byte = BIT(1);
            break;
        case 0x24:  //rename
            last_byte = BIT(1)|BIT(0);
            break;
        case 0x27:  //switch new AP
            last_byte = BIT(2)|BIT(1)|BIT(0);
            break;
        default:
            last_byte = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4);
            break;
    }
    //NSLog(@"Control ACK: last byte is %02x", last_byte);
    memcpy(buffer+len, &last_byte, 1);
    len += 1;
    
    ack_data = [NSData dataWithBytes:(const void*)buffer length:ACK_TO_CONTROL_DATA_LEN];
#ifdef ARC
    [ack_data retain];
#endif
}

-(int)send_control_ack_data: (unsigned int)ip
{
    int ret = RTK_FAILED;
    if(control_sock == nil){
        NSLog(@"udpSocket doesn't exist!!!");
        return -1;
    }
    
    NSString *host = [[NSString alloc] initWithString:[NSString stringWithFormat:@"%d.%d.%d.%d", (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>>8)&0xFF, ip&0xFF]];
    
    // send data(unicast)
    [control_sock receiveWithTimeout:-1 tag:0];
    BOOL result = [control_sock sendData:ack_data toHost:host port:UNICAST_PORT_NUM withTimeout:-1 tag:0];
    // deal with send result
    if(!result)
        ret=RTK_FAILED;
    else
        ret=RTK_SUCCEED;
    
#ifdef ARC
    [host release];
#endif
    
    return ret;
}

/* AsyncUDPSocket delegate */
- (BOOL)onUdpSocket:(AsyncSocket *)sock didReceiveData:(NSData *)data withTag:(long)tag fromHost:(NSString *)host port:(UInt16)port
{
    if (data==nil||host==nil) {
        return NO;
    }
    NSLog(@"========== Control: received data from %@:%d ==========", host, port);
    
    /* step 1: get the received data */
    unsigned char flag;
    unsigned char *data_p = (unsigned char*)[data bytes];
    if (data_p == nil) {
        NSLog(@"data received is nil!!!");
        return false;
    }
    unsigned int data_length = (unsigned int)(data.length);
    if (data_length<RESP_MIN_LEN) {
        NSLog(@"Control illegel received data with length %d", data_length);
        return false;
    }

    flag = data_p[0];
    if (flag==RSP_DEL_PROFILE || flag==RSP_RENAME_DEV || flag==RSP_NEW_AP ) {
        //NSLog(@"%d",flag);
    }

    /* step 2: parse the data and send ack*/
        unsigned int ack_ip = [self rtk_sc_convert_host_to_ip:host];
        unsigned char ack_result = data_p[3];
        //NSLog(@"ack_ip=%x", ack_ip);
        //NSLog(@"dev pin=%@", m_dev_pin);
        //NSLog(@"ack_result=%d", ack_result);
        
        m_result = ack_result;
        [self gen_control_ack_data:flag length:CONTROL_ACK_ACK_LEN];
        [self send_control_ack_data:ack_ip];
        m_mode = MODE_INIT;
        NSLog(@"Finish send control ack data");
    
    return YES;
}
@end
