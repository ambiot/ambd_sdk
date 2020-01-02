//
//  Controller.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/18.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AsyncUdpSocket.h"
#import "AsyncSocket.h"
#import "Defines.h"

@interface Controller : NSObject <AsyncUdpSocketDelegate>
{
@private
    unsigned int m_mode;
    unsigned int m_result;
    NSString     *m_dev_pin;
}

@property (nonatomic, strong) AsyncUdpSocket *control_sock;
@property (nonatomic, strong) NSData         *control_data;
@property (nonatomic, strong) NSData         *ack_data;

-(id)init;
-(void)rtk_sc_close_sock;
-(void)rtk_sc_reopen_sock;
-(int) rtk_sc_get_mode;
-(int) rtk_sc_get_control_result;

-(void)rtk_sc_gen_control_data: (unsigned int)type pin: (NSString *)pin name: (NSString *)name;
-(void)rtk_sc_gen_control_new_AP_data:(NSString*)pin ssid:(NSString*)AP_ssid password:(NSString*)AP_pwd;
-(int) rtk_sc_send_control_data: (unsigned int)ip;

- (unsigned int)rtk_sc_convert_host_to_ip: (NSString *)host;

@end
