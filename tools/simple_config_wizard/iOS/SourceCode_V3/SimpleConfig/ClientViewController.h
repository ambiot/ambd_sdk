//
//  ClientViewController.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/13.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Controller.h"
#import "String.h"
#import "Lib/ZBarSDK/Headers/ZBarSDK/ZBarSDK.h"

@interface ClientViewController : UIViewController<ZBarReaderDelegate>
{
@private
    Controller *m_controller;
    NSTimer    *m_timer;
    unsigned int m_mode;
    // QRCode Related
    int         m_num ;
    BOOL        m_upOrdown;
    NSTimer     *m_qrcode_timer;
}

@property (retain, nonatomic) IBOutlet UITextField  *name_label;
@property (retain, nonatomic) IBOutlet UILabel      *ip_label;
@property (retain, nonatomic) IBOutlet UILabel      *mac_label;
@property (retain, nonatomic) IBOutlet UILabel      *pinLabel;
@property (retain, nonatomic) IBOutlet UITextField  *pin_label;

@property (retain, nonatomic) IBOutlet UIButton     *qrcode_btn;
@property (retain, nonatomic) UIImageView           *m_qrscan_line;
@property (retain, nonatomic) IBOutlet UIButton     *delete_btn;
@property (retain, nonatomic) IBOutlet UIButton     *rename_btn;
@property (retain, nonatomic) IBOutlet UIButton     *connectNewAP_btn;

@property (strong, nonatomic) NSValue               *sharedData;
@property (strong, nonatomic) NSString              *control_pin;

-(IBAction)delete_profile:(id)sender;
-(IBAction)rename_device:(id)sender;
-(IBAction)switch_to_other_AP:(id)sender;
-(IBAction)scan_QRCode:(id)sender;

@end
