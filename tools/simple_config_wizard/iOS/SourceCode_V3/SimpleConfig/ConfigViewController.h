//
//  ConfigViewController.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/11.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#ifndef SimpleConfig_ConfigViewController_h
#define SimpleConfig_ConfigViewController_h

#import <UIKit/UIKit.h>
#import "SimpleConfig.h"
#import "String.h"
#import "ClientViewController.h"
#import "Lib/ZBarSDK/Headers/ZBarSDK/ZBarSDK.h"


typedef struct rtk_sc_context{
    unsigned int    m_mode;    
    unsigned int    m_recv_len;
    unsigned char   m_recv_buf[MAX_BUF_LEN];
}SC_CONTEXT;

@interface ConfigViewController : UIViewController <ZBarReaderDelegate, UITableViewDelegate, UITableViewDataSource>
{
@private
    BOOL upOrdown;
    int num ;
    
    // SC Related
    SC_CONTEXT  m_context;
    // QRCode Related
    int         m_num ;
    BOOL        m_upOrdown;
    NSTimer     *m_qrcode_timer;
}

@property (retain, nonatomic) IBOutlet UITextField *m_input_ssid;
@property (retain, nonatomic) IBOutlet UITextField *m_input_password;
@property (strong, nonatomic) IBOutlet UITextField *m_input_pin;
@property (retain, nonatomic) IBOutlet UIButton    *m_config_button;

@property (strong, nonatomic) SimpleConfig         *simpleConfig;

@property (strong, nonatomic) UIImageView          *m_qrscan_line;
@property (strong, nonatomic) UIAlertView          *waitingAlert;
@property (strong, nonatomic) UIProgressView       *cfgProgressView;
@property (nonatomic, strong) UIImageView  *line;

@property (strong, nonatomic) NSMutableArray *confirm_list;
@property (strong, nonatomic) IBOutlet UITableView *tableDeviceList;

- (IBAction)rtk_start_listener:(id)sender;
- (IBAction)rtk_scan_listener:(id)sender;

@end

#endif
