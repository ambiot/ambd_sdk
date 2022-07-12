//
//  RTKViewController.h
//  SimpleConfig
//
//  Created by realtek on 6/16/14.
//  Copyright (c) 2014 Realtek. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Reachability.h"

#include "SimpleConfig.h"
#include "ZBarSDK.h"
#define NEW_UI_Y_DELTA      (120)
#define ENABLE_QRCODE       1

#ifdef DEBUG
    #define NSLog(...) NSLog(__VA_ARGS__)
#else
    #define NSLog(...) ｛｝
#endif

@interface RTKViewController : UIViewController <UIAlertViewDelegate, UITableViewDelegate, UITableViewDataSource, ZBarReaderDelegate>
{
    int num ;
    BOOL upOrdown;
}
//----------- origin member variables -----------
@property (nonatomic, strong) SimpleConfig *mySimpleConfig;
@property (nonatomic, strong) UITextField  *mySSID;
@property (nonatomic, strong) UITextView   *myAESKey;
@property (nonatomic, strong) NSTimer      *myTimer;
@property (nonatomic, strong) NSString     *myDevType;
@property (nonatomic, strong) UIImageView  *line;


//----------- add member variables -----------
- (void)checkForWIFIConnection;
@property (strong, nonatomic) IBOutlet UIAlertView *waitingAlert;

//table controller
@property (strong, nonatomic) IBOutlet UITableView *tableDeviceList;

//QR Code
//@property (nonatomic, strong) NSString     *m_pin_code;


@end
