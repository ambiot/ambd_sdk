//
//  SimpleConfig.h
//  test3
//
//  Created by patrick_cai on 12-1-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonHMAC.h>
#import <UIKit/UIKit.h>
#import <SystemConfiguration/CaptiveNetwork.h>

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <net/if_dl.h>
#include <net/if.h>
#include <unistd.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#import <CocoaAsyncSocket/AsyncUdpSocket.h>


#define USE_AUTO_SSID               1

#define SC_NAME_LEN                 (32)
#define MCAST_ADDR_PREFIX           (239)
#define MCAST_PORT_NUM              (18864)
#define UNICAST_PORT_NUM            (8864)
#define LOCAL_PORT_NUM              (8864)
#define MAX_AES_KEY_BUF_LEN         (32)
#define MAX_PROFILE_BUF_LEN         (256)
#define MAX_PIN_LEN                 (64)
#define MIN_PIN_LEN                 (8)

#define PATTERN_TWO_SYNC_PKT_NUM    9
#define PATTERN_TWO_SEQ_IDX         3
#define PATTERN_TWO_ID_IDX          5
#define PATTERN_TWO_DATA_IDX        5
#define PATTERN_TWO_RANDOM_IDX      5
#define PATTERN_TWO_CKSUM_IDX       4
#define PATTERN_TWO_MAGIC_IDX0      3
#define PATTERN_TWO_MAGIC_IDX1      4
#define PATTERN_TWO_MAGIC_IDX2      5
#define PATTERN_TWO_MAGIC_IDX3      5
#define PATTERN_TWO_SEND_TIME       10
#define PATTERN_TWO_RECEIVE_TIMEOUT 120

#define BIT(x)                      (1<<(x))
#define PATTERN_VALID               BIT(1)
#define PATTERN_HAS_END             BIT(2)
#define PATTERN_USING_UDP_SOCKET    BIT(3)
#define PATTERN_USING_PLAIN         BIT(4)

#define TLV_T_BYTES                 (1)
#define TLV_L_BYTES                 (1)
#define TLV_T_L_BYTES               (TLV_T_BYTES + TLV_L_BYTES)
#define TAG_SSID                    1
#define TAG_PSW                     2
#define TAG_IP                      3

#define SCAN_DATA_LEN               (1+1+2+64+16+6+2)
#define CONTROL_DATA_LEN            (1+1+2+64+16+16)
#define ACK_TO_CONTROL_DATA_LEN     (1+1+2+64+16+16+1)

#define REQ_SCAN                    (0)
#define REQ_DEL_PROFILE             (BIT(1))
#define REQ_RENAME_DEV              (BIT(0) | BIT(1))
#define REQ_ACK                     (BIT(2));

#define RSP_CONFIG                  (BIT(5))
#define RSP_SCAN                    (BIT(5) | BIT(0))
#define RSP_DEL_PROFILE             (BIT(5) | BIT(1) | BIT(0))
#define RSP_RENAME_DEV              (BIT(5) | BIT(2))

#define BLKSIZE8                    (8)
#define BLKSIZE                     (16)
#define AES_WRAP_TIME               (6)

#define ENCRYPT_TEST                0
typedef union _block{
    unsigned int x[BLKSIZE/4];
    unsigned char b[BLKSIZE];
}block;

typedef struct _dev
{
    __unsafe_unretained NSString *macAddress;
    unsigned char type[2];
    unsigned int ip;
    __unsafe_unretained NSString *dev_name;
}dev_info;

typedef enum{
    PATTERN_ZERO= 0,
    PATTERN_ONE = 1,
    PATTERN_TWO = 2,
    PATTERN_THREE=3,
}PATTERN_LIST;

typedef enum{
    SC_DELETE_PROFILE=1,
    SC_RENAME_DEV=2,
}SC_CONTROL_TYPE;

@class ViewController;

@interface PatternFactory : AsyncUdpSocket {
@public
    unsigned int m_index;   //index number of Pattern
    unsigned int m_flag;    //flag of this Pattern
    NSString *m_name;       //name of Pattern
    
    unsigned int m_key_len; //length of AES Key
    unsigned int m_crypt_len;//length of crypted profile
    unsigned int m_plain_len;//length of plain profile
    unsigned char m_aes_key_buf[MAX_AES_KEY_BUF_LEN];   //store Key for AES
    unsigned char m_crypt_buf[MAX_PROFILE_BUF_LEN];     //store crytped profile
    unsigned char m_plain_buf[MAX_PROFILE_BUF_LEN];     //store plain profile
    unsigned char m_scan_buf[MAX_PROFILE_BUF_LEN];      //store udp data for device discovery
    
    unsigned char m_security_level;
}

@property (nonatomic,strong) AsyncUdpSocket *udpSocket;
@property (nonatomic,strong) AsyncUdpSocket *controlSocket;
@property (nonatomic) unsigned int have_pin;
@property (nonatomic,strong) NSString *m_pin;
@property (nonatomic,strong) NSString *m_ssid;
@property (nonatomic,strong) NSString *m_psw;
@property (nonatomic) int send_times;
@property (nonatomic,strong) NSMutableArray *ack_host;
@property (nonatomic,strong) NSMutableArray *dev_connected_list;
@property (atomic,strong) NSMutableArray *extend_ack_host;
@property (nonatomic, strong) NSData *m_control_data;
@property (nonatomic, strong) NSData *m_discover_data;
@property (nonatomic, strong) NSString *default_pin;
@property (nonatomic, strong) NSData *m_ack_data;
@property (nonatomic, strong) NSString *m_control_pin;

- (id)init: (unsigned int)index flag:(unsigned int)flag name:(NSString *)name;
- (void)dealloc;
- (void)init_buffer;
- (void)get_random_pattern_2;
- (unsigned char)CKSUM:(unsigned char *)data len:(int)len;
- (int)CKSUM_OK:(unsigned char *)data len:(int)len;
//- (unsigned int)get_index;
- (void)set_index: (unsigned int)index;
- (NSString *)localIPAddress;
#if USE_AUTO_SSID
- (id)fetchSSIDInfo;
#endif
- (NSString *)getMACAddress: (char *)if_name;
- (int)add_tlv_string: (unsigned int)offset tag:(unsigned char)tag len:(int)len value:(const char *)value;
- (int)add_tlv_int: (unsigned int)offset tag:(unsigned char)tag value:(unsigned int)value;

- (void)get_len: (unsigned int *)plain_len key_len:(unsigned int*)key_len crypt_len:(unsigned int *)crypt_len;
- (unsigned char *)get_plain_buf;
- (unsigned char *)get_key_buf;
- (unsigned char *)get_crypt_buf;
- (int)encrypt_profile;

- (int)key_gen_pattern_2;

- (int)gen_scan_data: (NSString *)key;
- (int)send_scan_data: (NSData *)data ip:(unsigned int)ip;
- (NSData *)gen_control_data: (unsigned char)flag length: (unsigned int)length psw: (NSString *)psw dev_pin:(NSString *)dev_pin;
//- (void)gen_save_profile_data: (NSString *)psw pin:(NSString *)pin;
- (void)gen_delete_profile_data: (NSString *)psw pin:(NSString *)pin;
- (void)gen_rename_dev_data: (NSString *)psw pin:(NSString *)pin name: (NSString *)name;
- (int)send_control_data: (NSData *)data ip:(unsigned int)ip;
- (NSData *)gen_ack_data;

// security level
- (void) rtk_sc_set_security_level: (unsigned char)level;
- (unsigned char) rtk_sc_get_security_level;
@end




@interface SimpleConfig : PatternFactory
{
@private
    unsigned int m_profile_total_len;   //total profile length BEFORE encryption
    //NSString *m_control_pin;
}
@property (nonatomic, strong) PatternFactory    *pattern;

/* Externel API for simple config */
// init
- (id)initWithPattern: (unsigned int)index flag:(unsigned int)flag name:(NSString *)name;
- (void)dealloc;
// simple config
- (void)rtk_sc_set_pin: (NSString *)pin;
- (void)rtk_sc_set_ssid: (NSString *)ssid;
- (void)rtk_sc_set_password: (NSString *)psw;
- (void)rtk_sc_set_ip: (unsigned int)ip;
- (void)rtk_sc_gen_random;
- (void)rtk_sc_build_profile;
- (void)rtk_sc_send;
- (void)rtk_sc_start;
- (Boolean)rtk_sc_get_cfgACK_state;
- (int) rtk_get_connected_sta_num;
- (NSMutableArray *) rtk_get_connected_sta_mac;
- (void)rtk_sc_stop;
- (void)rtk_sc_exit;

- (void)rtk_sc_set_profileSendInterval:(unsigned int)msTime;
- (void)rtk_sc_set_packetSendInterval:(unsigned int)msTime;
- (void)rtk_sc_set_eachPacketCounts:(unsigned int)counts;

// device control
- (void)    rtk_sc_clear_device_list;
- (NSData *)rtk_sc_gen_discover_packet;
- (void)    rtk_sc_send_discover_packet: (NSData *)data ip:(unsigned int)ip;
- (NSMutableArray *)rtk_sc_get_discovered_devices;
- (NSData *)rtk_sc_gen_control_packet: (unsigned int)control_type;
- (void)    rtk_sc_send_control_packet: (NSData *)data ip:(unsigned int)ip;
- (NSData *)rtk_sc_gen_rename_dev_packet: (NSString *)dev_name;
- (void)    rtk_sc_send_rename_dev_packet: (NSData *)data ip:(unsigned int)ip;
- (void)    rtk_sc_set_control_pin: (NSString *)pin;
- (void) rtk_sc_reset_control_pin;
- (int)     rtk_sc_get_control_result;
- (void)    rtk_sc_reset_control_result;

// default pin
- (NSString *) rtk_sc_get_default_pin;
- (void)       rtk_sc_set_default_pin:(NSString *)pin;
#if 0
// ack to ack
- (NSData *)rtk_sc_gen_ack_packets;
- (void)rtk_sc_send_ack_packets: (NSData *)data ip:(unsigned int)ip;
#endif
@end
