//
//  PatternBase.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/6.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#ifndef SimpleConfig_PatternBase_h
#define SimpleConfig_PatternBase_h
#import "Defines.h"
#import "AsyncUdpSocket.h"
#import "AsyncSocket.h"

@interface PatternBase : NSObject <AsyncUdpSocketDelegate>
{
@public
    NSString            *m_pattern_name;                        //pattern name
    NSNumber            *m_pattern_flag;                        //pattern flag, indicating using encrpytion and else
    
    unsigned int        g_lib_device_num;
    
    unsigned int        m_key_len;                              //length of AES Key
    unsigned int        m_crypt_len;                            //length of crypted profile
    unsigned int        m_plain_len;                            //length of plain profile
    unsigned char       m_aes_key_buf[MAX_AES_KEY_LEN];         //store Key for AES
    unsigned char       m_crypt_buf[MAX_BUF_LEN];               //store crytped profile
    unsigned char       m_plain_buf[MAX_BUF_LEN];               //store plain profile
    
    unsigned char       m_security_level;                       //security level for control
    
    unsigned char       m_send_buf[MAX_BUF_LEN];                //data to send
    
    unsigned int        m_mode;                                 //current mode
    NSString            *m_pin;                                 //PIN code if needed
    NSMutableArray      *m_config_list;                         //clients list that sent config ack
    AsyncUdpSocket      *m_configSocket;                        //socket
    AsyncUdpSocket      *m_controlSocket;                       //socket(for ack)
}

// External APIs
// initial
- (id)      init: (unsigned int)pattern_flag;
- (unsigned int)rtk_sc_get_mode;
// simple config
- (void)    rtk_pattern_set_dev_num: (int)device_num;
- (int)     rtk_pattern_build_profile: (NSString *)ssid psw:(NSString *)password pin:(NSString *)pin;
- (int)     rtk_pattern_send: (NSNumber *)times;
- (int)     rtk_pattern_send_ack_packets;
- (int)     rtk_pattern_send_ack_packets: (unsigned int) ip;
- (void)    rtk_pattern_stop;
- (void)    rtk_sc_close_sock;
- (void)    rtk_sc_reopen_sock;
- (NSMutableArray *)rtk_pattern_get_config_list;

-(BOOL) rtk_pattern_isMyDevice: (NSString*)name :(int)nameLen;
-(BOOL) rtk_pattern_softAP_init:(NSString*)bssid :(int)bssidLen;
-(void) setTargetAPis5GBand:(BOOL)is5G;
@end
#endif
