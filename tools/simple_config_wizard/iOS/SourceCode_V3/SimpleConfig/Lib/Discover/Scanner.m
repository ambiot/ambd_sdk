//
//  Scanner.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/14.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import "Scanner.h"
#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonHMAC.h>

#define SC_SCAN_PIN             @"57289961"

@implementation Scanner
@synthesize scan_socket;
@synthesize scan_data;

-(id)init
{
    NSError *err;
    
    /* init udp socket */
    //NSLog(@"Scanner init");
    scan_socket = [[AsyncUdpSocket alloc]initWithDelegate:self];
    [scan_socket bindToPort:(LOCAL_PORT_NUM) error:&err]; //this port is udpSocket's port instead of dport
    [scan_socket enableBroadcast:true error:&err];
    [scan_socket receiveWithTimeout:-1 tag:0];
    
    /* init scan result list */
    m_devlist = [[NSMutableArray alloc] initWithObjects:nil];
    
    return [super init];
}

-(void)dealloc
{
    [scan_socket close];
#ifdef ARC
    [scan_socket dealloc];
#endif
    scan_socket = nil;
#ifdef ARC
    [m_devlist dealloc];
    [scan_data release];
#endif
    NSLog(@"scan socket close and dealloc");
#ifdef ARC
    [super dealloc];
#endif
}

-(void)rtk_sc_close_sock
{
    if (![scan_socket isClosed]) {
        //NSLog(@"m_scanner close");
        [scan_socket close];
    }
}
-(void)rtk_sc_reopen_sock
{
    NSError *err;
    if ([scan_socket isClosed]) {
        NSLog(@"m_scanner reopen");
        scan_socket = [[AsyncUdpSocket alloc]initWithDelegate:self];
        [scan_socket bindToPort:(LOCAL_PORT_NUM) error:&err]; //this port is udpSocket's port instead of dport
        [scan_socket enableBroadcast:true error:&err];
        [scan_socket receiveWithTimeout:-1 tag:0];
    }
}

/* -------------External APIs----------------- */
-(void)rtk_sc_build_scan_data:(unsigned int)security_level
{
    unsigned int len = 0;
    unsigned char scan_buf[MAX_BUF_LEN];
    /* Flag */
    unsigned char flag = REQ_SCAN; // full 0 char means request to report(scan)
    memcpy(scan_buf+len, &flag, 1);
    len += 1;
    
    /* Security Level */
    unsigned char security = security_level;
    memcpy(scan_buf+len, &security, 1);
    len += 1;
    
    /* Length: not included flag and length */
    unsigned char length[2] = {0x0};
    length[1] = SCAN_DATA_LEN-1-1-2; //exclude flag, security level and length
    memcpy(scan_buf+len, length, 2);
    len += 2;
    
    /* Nonce: a random value */
    unsigned char nonce[64] = {0x0};
    int nonce_idx = 0;
    for (nonce_idx=0; nonce_idx<64; nonce_idx++) {
        nonce[nonce_idx] = 65 + rand()%26;
        //NSLog(@"[%d]: %02x", nonce_idx, nonce[nonce_idx]);
    }
    memcpy(scan_buf+len, nonce, 64);
    len += 64;
    
    /* MD5 digest, plain buffer is nonce+default_pin */
    unsigned char md5_result[16] = {0x0};
    const unsigned char *default_pin_char = (const unsigned char *)[SC_SCAN_PIN cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned int default_pin_len = (unsigned int)(strlen((const char *)default_pin_char));
    //NSLog(@"default_pin_char is(%d) %s", default_pin_len, default_pin_char);
    unsigned char md5_buffer[64+64] = {0x0};//note: default pin max length is 64 bytes
    memcpy(md5_buffer, nonce, 64);
    memcpy(md5_buffer+64, default_pin_char, default_pin_len);
    //NSLog(@"md5_plain buffer is(%d) %s", (int)strlen((const char *)md5_buffer), md5_buffer);
    CC_MD5((const void *)md5_buffer, 64+default_pin_len , (unsigned char *)md5_result);
    //NSLog(@"md5_encrypt result: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", md5_result[0],md5_result[1],md5_result[2],md5_result[3],md5_result[4],md5_result[5],md5_result[6],md5_result[7],md5_result[8],md5_result[9],md5_result[10],md5_result[11],md5_result[12],md5_result[13],md5_result[14],md5_result[15]);
    
    memcpy(scan_buf+len, md5_result, 16);
    len += 16;
    
    /* Source MAC Address */
    unsigned char sa[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // full FF means send to all possible devices
    memcpy(scan_buf+len, sa, 6);
    len += 6;
    
    /* Device Type */
    unsigned char deviceType[2] = {0xff, 0xff};
    memcpy(scan_buf+len, deviceType, 2);
    len += 2;
    
    /* save m_scan_buf to m_discover_data */
    NSInteger size = SCAN_DATA_LEN;
    scan_data = [NSData dataWithBytes:(const void*)scan_buf length:size];
#ifdef ARC
    [scan_data retain];
#endif
}

-(int)rtk_sc_start_scan
{
    int ret = RTK_FAILED;
    unsigned int ip=0xFFFFFFFF;
    NSError *err;
    BOOL result;
    NSString *host = [[NSString alloc] initWithString:[NSString stringWithFormat:@"%d.%d.%d.%d", (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>>8)&0xFF, ip&0xFF]];

    [scan_socket joinMulticastGroup:host error:&err];
    [scan_socket receiveWithTimeout:-1 tag:0];
    result = [scan_socket sendData:scan_data toHost:host  port:MCAST_PORT_NUM withTimeout:-1 tag:0];
    if(!result)
        ret = RTK_FAILED;
    else
        ret = RTK_SUCCEED;

    if (ret == RTK_FAILED) {
        NSLog(@"Finish send scan data, ret=%d", ret);
    }
    
#ifdef ARC
    [host release];
#endif
    
    return ret;
}

-(NSMutableArray *)rtk_sc_get_scan_list
{
    return m_devlist;
}

/*-------------------UDP Delegate--------------------*/
- (BOOL)onUdpSocket:(AsyncSocket *)sock didReceiveData:(NSData *)data withTag:(long)tag fromHost:(NSString *)host port:(UInt16)port
{
    if (data==nil || host==nil) {
        return true;
    }
    NSLog(@"==== Scanner: receive from %@:%d ====", host, port);
    
    /* step 1: get the received data */
    unsigned char flag;
    unsigned char *data_p = (unsigned char*)[data bytes];
    if (data_p == nil) {
        NSLog(@"data received is nil!!!");
        return true;
    }
    unsigned int data_length = (unsigned int)(data.length);
    if (data_length<RESP_MIN_LEN) {
        NSLog(@"illegel received data with length %d", data_length);
        return true;
    }
    flag = data_p[0];
    
#if SCANNER_DBG
    // for debug
    NSLog(@"data in udp is %ld bytes: ", (unsigned long)[data length]);
    
    int recv_idx = 0;
    for (recv_idx=0; recv_idx<(data_length+3); recv_idx++) {
        NSLog(@"[%d]: %02x", recv_idx, data_p[recv_idx]);
    }
#endif
    
    /* step 2: parse the data */
    if (flag==RSP_SCAN) {
        [self updateScanList:data_p len:data_length];
    }
    
    return true;
}

-(void) build_dev_info:(struct dev_info *)new_dev data_p: (unsigned char *)data_p len: (unsigned int)len
{
    memcpy(new_dev->mac, data_p+ACK_OFFSET_MAC, MAC_ADDR_LEN);
    new_dev->status = data_p[ACK_OFFSET_STATUS];
    
    unsigned char type_translator[2]={0x0};
    type_translator[1] = *(data_p+ACK_OFFSET_DEV_TYPE);
    type_translator[0] = *(data_p+ACK_OFFSET_DEV_TYPE+1);
    memcpy(&new_dev->dev_type, type_translator, 2);
    
    unsigned char ip_translator[4]={0x0};
    ip_translator[3]=*(data_p+ACK_OFFSET_IP);
    ip_translator[2]=*(data_p+ACK_OFFSET_IP+1);
    ip_translator[1]=*(data_p+ACK_OFFSET_IP+2);
    ip_translator[0]=*(data_p+ACK_OFFSET_IP+3);
    memcpy(&new_dev->ip, ip_translator, 4);
    
    memcpy(&new_dev->extra_info, data_p+ACK_OFFSET_DEV_NAME, len-MAC_ADDR_LEN-1-2-4);

    [self dump_dev_info:new_dev];
}

-(void) dump_dev_info: (struct dev_info *)dev
{
#if SCANNER_DBG
    NSLog(@"======Dump dev_info======");
    NSLog(@"MAC: %02x:%02x:%02x:%02x:%02x:%02x", dev->mac[0], dev->mac[1],dev->mac[2],dev->mac[3],dev->mac[4],dev->mac[5]);
    NSLog(@"Status: %d", dev->status);
    NSLog(@"Device type: %d", dev->dev_type);
    NSLog(@"IP:%x", dev->ip);
    //NSLog(@"Name:%@", [NSString stringWithUTF8String:(const char *)(dev->extra_info)]);
    NSLog(@"Name:%@", [NSString stringWithCString:(const char *)(dev->extra_info) encoding:NSUTF8StringEncoding]);
#else
#endif
}

/* update the received data to m_config_list */
-(void)updateScanList: (unsigned char *)data_p len:(unsigned int)data_length
{
    int exist=0, i=0;
    struct dev_info old_dev;
    NSValue *old_dev_val;
    struct dev_info new_dev;
    int dev_total_num = (int)[m_devlist count];
    
    // no dev_info exist
    if (dev_total_num==0)
        goto AddNewObj;
    
    // OR, check if this device info already exist
    for (i=0; i<dev_total_num; i++) {
        old_dev_val = [m_devlist objectAtIndex:i];
        [old_dev_val getValue:&old_dev];
        
        if(!memcmp(old_dev.mac, data_p+ACK_OFFSET_MAC, MAC_ADDR_LEN)){
            // have the same mac dev in list, index is i.
            exist = 1;
            break;
        }
    }
    
    if (exist) {
        // update device info
        //NSLog(@"exist %d", i);
        [self build_dev_info:&new_dev data_p:data_p len:data_length];
        [m_devlist replaceObjectAtIndex:i withObject:[NSValue valueWithBytes:&new_dev objCType:@encode(struct dev_info)]];
        return;
    }
    
AddNewObj:
    {
        // new dev_info
        NSLog(@"new device");
        [self build_dev_info:&new_dev data_p:data_p len:data_length];
        [m_devlist addObject:[NSValue valueWithBytes:&new_dev objCType:@encode(struct dev_info)]];
        return ;
    }
}

@end
