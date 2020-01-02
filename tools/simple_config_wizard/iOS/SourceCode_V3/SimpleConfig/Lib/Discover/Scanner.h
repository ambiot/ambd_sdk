//
//  Scanner.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/14.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AsyncSocket.h"
#import "AsyncUdpSocket.h"
#import "Defines.h"
#define SCANNER_DBG 0

@interface Scanner : NSObject <AsyncUdpSocketDelegate>
{
@private
    NSMutableArray *m_devlist;                              // scanned device list
}

@property (strong, nonatomic) AsyncUdpSocket *scan_socket; 
@property (strong, nonatomic) NSData         *scan_data;    // scan data

-(id)init;
-(void)rtk_sc_build_scan_data: (unsigned int)security_level;
-(int)rtk_sc_start_scan;
-(NSMutableArray *)rtk_sc_get_scan_list;

-(void)rtk_sc_close_sock;
-(void)rtk_sc_reopen_sock;

@end
