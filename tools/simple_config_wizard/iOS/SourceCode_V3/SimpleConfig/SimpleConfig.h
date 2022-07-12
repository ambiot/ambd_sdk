//
//  SimpleConfig.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/6.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#ifndef SimpleConfig_SimpleConfig_h
#define SimpleConfig_SimpleConfig_h
#import <UIKit/UIKit.h>
#import "Defines.h"
#import "PatternTwo.h"
#import "PatternThree.h"
#import "PatternFour.h"

#define SC_SEND_ROUND_PER_SEC       10                      // send round per second
#define SC_MAX_PATTERN_NUM          4                       // currently only supports at most 4 patterns

#define SC_SUPPORT_2X2              1                       // support 2x2 wifi

#if SC_SUPPORT_2X2
#define SC_PATTERN_DEF_SWITCH_THRESHOLD 20                  // time(in seconds) to switch configuring mode
#define SC_CONFIG_QC_TEST           1                       // for QC testing
#endif

#if SC_CONFIG_QC_TEST
enum {
    SC_MODEL_1=0,       // only use pattern 4
    SC_MODEL_2,         // only use pattern 2/3
    SC_MODEL_3,         // use pattern 2/3/4 alternatively
};
#endif

@interface SimpleConfig : NSObject{
@private
    BOOL            m_shouldStop;
    unsigned int    m_mode;                                 // simple config state machine
    int             m_current_pattern;                      // pattern in use
#if SC_SUPPORT_2X2
    int             m_config_duration;                      // duration of MODE_CONFIG
    NSString        *m_ssid;                                // must record to rebuild profile
    NSString        *m_password;
    NSString        *m_pin;
    NSString        *m_idev_model;                          // iDevice model
#endif
#if SC_CONFIG_QC_TEST
    unsigned int    m_model;                                // simple config operation model
    unsigned int    m_mix_model_max_duration;               // max duration for using pattern 2/3 in SC_MODEL_3
#endif
    NSTimer         *m_timer;
    NSThread        *myThread;
    NSString        *m_error;
    PatternBase     *m_pattern[SC_MAX_PATTERN_NUM];
}

@property (strong, nonatomic) NSMutableArray *config_list;    // clients list that sent config ack
@property (strong, nonatomic) NSMutableArray *discover_list;  // clients list that send discover ack

-(id)  init;
-(void)rtk_sc_config_set_devNum: (int)device_num;
-(int) rtk_sc_config_start:(NSString *)ssid psw:(NSString *)password pin:(NSString *)pin;
-(void)rtk_sc_config_stop;
-(int) rtk_sc_discover_start:(unsigned int)scan_time;
-(int) rtk_sc_control_start:(NSString *)client_mac type:(unsigned char)control_type;

-(unsigned int)rtk_sc_get_pattern;
-(unsigned int)rtk_sc_get_mode;
-(void)rtk_sc_close_sock;
-(void)rtk_sc_reopen_sock;

- (NSMutableArray *)getList_forConfirm;

#if SC_CONFIG_QC_TEST
-(void)rtk_sc_set_sc_model: (unsigned int) model duration: (unsigned int) duration;
#endif

//soft AP mode
-(void) rtk_sc_setTargetAPis5GBand:(BOOL)is5G;
-(BOOL) rtk_sc_isMyDevice: (NSString*)name :(int)nameLen;
-(void)rtk_sc_softAP_init:(NSString*)bssid :(int)bssidLen;
@end

#endif
