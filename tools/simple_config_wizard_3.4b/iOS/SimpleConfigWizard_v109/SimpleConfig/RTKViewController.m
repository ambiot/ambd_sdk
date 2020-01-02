//
//  RTKViewController.m
//  SimpleConfig
//
//  Created by realtek on 6/16/14.
//  Copyright (c) 2014 Realtek. All rights reserved.
//
#import <SystemConfiguration/CaptiveNetwork.h>
#import "RTKViewController.h"
#import <QuartzCore/QuartzCore.h>
#import "Reachability.h"

@interface RTKViewController ()

@end

@implementation RTKViewController
{
    NSMutableArray *t_devicelist;   //device name
}

//define tag number
#define tag_table_main      1
#define tag_table_confirm   2

#define tag_timer           10101

#define tag_ctl_TEXTpincode 10201
#define tag_ctl_VIEWshow    10301
#define tag_ctl_VIEWaction  10302

#define tag_cfg_TEXTpincode 10501
#define tag_cfg_VIEWshow    10601
#define tag_cfg_VIEWwifi    10602
#define tag_cfg_confirm     10603
#define tag_ctl_rename      10604
#define tag_ctl_renameEND   10605
#define tag_ctl_remove      10606
#define tag_ctl_removeEND   10607

//define timout
#define timeout_cfg         PATTERN_TWO_RECEIVE_TIMEOUT //120.0
#define timeout_discovery   4.0
#define timeout_control     20.0

typedef enum {
    NONE_STATE, SCAN_STATE, CONFIGURE_STATE, CONTROL_STATE
} EventType;

@synthesize mySimpleConfig;
@synthesize myAESKey;
@synthesize myTimer;
@synthesize myDevType;

//@synthesize m_pin_code;

@synthesize waitingAlert;

UITextField *text_pincode;

Boolean isShowDiscoveryDevice = false;
Boolean isShowCtlRename       = false;
Boolean isShowCtlRemove       = false;
Boolean isQRcodeAction        = false;
Boolean isCfgPIN              = false;
Boolean isCtlPIN              = false;

NSMutableArray *discovery_deviceList;   //context:  dev_info(struct)
NSMutableArray *config_deviceList;      //context:  dev_info(struct)

NSString *newDeviceName = nil;
NSString *SSID = nil;
NSString *AP_password = nil;
NSString *PIN_cfg = nil, *PIN_ctl = nil;
NSString *PIN_backdoor = @"00000000";

NSString *dev_Iphone = @"iPhone";
NSString *dev_Ipad   = @"iPad";

NSTimer *waitTimer,*discoveryTimer;
NSTimer *cfgTimer;
NSData *bcastdata;

UIAlertView *ctlPINAlert;
UIAlertView *cfgPINAlert;

UILabel *lblDownloadPercent;

UIProgressView *cfgProgressView;

NSUserDefaults *APInfo_DataFile = nil;      //SSID1,password1;SSID,password2;...
NSUserDefaults *PINCode_DataFile = nil;     //mac1,PIN1;mac2,PIN2;...

//int checkFinishWait_cfg = 20;
int checkFinishWait_control = 20;

unsigned int bcastip = 0;
unsigned int timerCount = 0;
static int curr_control_type = 0;
EventType curr_event;
dev_info  curDevInfo;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self initUIlayout];        //NSLog(@"initUIlayout ================== finish");
    [self initData];            //NSLog(@"initData ====================== finish");
    [self initComponent];       //NSLog(@"initComponent ================= finish");
    [self initComponentAction]; //NSLog(@"initComponentAction =========== finish");
    
    
    if([t_devicelist count]> 0 )
        NSLog(@"<APP> There are %lu devices",(unsigned long)[t_devicelist count]);
}
- (BOOL)shouldAutorotate
{
    return NO;
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
/*- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
 {
 // Return YES for supported orientations
 return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
 }*/


//#pragma mark - Table view data source
//TO DO myself
-(void)initUIlayout
{
    NSString *deviceType = [UIDevice currentDevice].model;
    
    //NSLog(@"<APP> current device type:%@",deviceType);
    
    /*if (IS_IPHONE4) {
     NSLog(@"IS_IPHONE4");
     }else if(IS_IPHONE5){
     NSLog(@"IS_IPHONE5");
     }else if(IS_IPHONE_6){
     NSLog(@"IS_IPHONE_6");
     }else if(IS_IPHONE_6_PLUS){
     NSLog(@"IS_IPHONE_6_PLUS");
     }*/
    
    
    if([deviceType isEqualToString:@"iPhone"]) //iphone
    {
        self.myDevType = dev_Iphone;
        
        //float iPhoneVersion = NSFoundationVersionNumber;
        //NSLog(@"iphone version:%f",iPhoneVersion);
        
        if ([[UIScreen mainScreen] scale] == 2.0)//retina display
        {
            int mheight = [UIScreen mainScreen].bounds.size.height;
            if( mheight == 568){ // iPhone retina-4 inch //IS_IPHONE5
                
                //NSLog(@"<APP> retina-4 inch");
                CGRect frame = self.tableDeviceList.frame;
                //frame.size.height = 418;
                self.tableDeviceList.frame  = frame;
                self.tableDeviceList.tag    = tag_table_main;
                
                
                
            }else if( mheight == 480){ //IS_IPHONE4
                
                if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_7_1) {
                    // do stuff for iOS 8 and newer
                    
                }else if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_6_1) {
                    // do stuff for iOS 7 and newer
                    /*CGRect frame = self.view.frame;
                     frame.origin.y = 20;
                     
                     if (self.view.frame.size.height == 1024 ||
                     self.view.frame.size.height == 768)
                     {
                     frame.size.height -= 20;
                     }
                     
                     self.view.frame = frame;*/
                }else{
                    // do stuff for iOS 6 and older
                }
                
                
            }else{
                //NSLog(@"<APP> retina-3.5 inch");
                self.tableDeviceList.frame = CGRectMake(0, 40, 320, 300);
                self.tableDeviceList.tag    = tag_table_main;
            }
            
        }
        else
        {
            // not retina display
        }
    }else{//ipad
        //NSLog(@"<APP> [TO DO IPAD SHOW]");
        self.myDevType = dev_Ipad;
        
        self.tableDeviceList.frame = CGRectMake(0, 40, 320, 300);
        self.tableDeviceList.tag    = tag_table_main;
    }
}

-(void)initData
{
    // Initialize table data
    t_devicelist = [[NSMutableArray alloc] init];
    t_devicelist = [NSMutableArray arrayWithObjects: nil];
    
    [self.tableDeviceList reloadData];
    
    discovery_deviceList = [[NSMutableArray alloc] init];
    discovery_deviceList = nil;
    
    config_deviceList = [[NSMutableArray alloc] init];
    config_deviceList = nil;
    
    //init timer
    waitTimer = nil;
    
    /* init the simpleConfig with Pattern 2*/
    NSString *pattern_name = @"sc_mcast_udp";
    self.mySimpleConfig = [[SimpleConfig alloc] initWithPattern:PATTERN_TWO flag:(PATTERN_USING_UDP_SOCKET | PATTERN_VALID ) name:pattern_name];
}

-(void)initComponent
{
    APInfo_DataFile = [NSUserDefaults standardUserDefaults];
    PINCode_DataFile = [NSUserDefaults standardUserDefaults];
    
}

-(void)initComponentAction
{
    /* init the timer, update timer every 1s */
    self.myTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(handleTimer:) userInfo:nil repeats:YES];
    
    if([discovery_deviceList count]==0 && [self IsEnableWIFI])
    {
        [self Discovery_triger];
    }else{
        UIAlertView *wifialertView = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"No WIFI available!", @"AlertView")
                                      message:NSLocalizedString(@"You have no wifi connection available. Please connect to a WIFI network.", @"AlertView")
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:/*NSLocalizedString(@"Open settings", @"AlertView"),*/ nil];
        [wifialertView show];
    }
}



//---------------------------------  UI table controllers  -------------------------------------
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *simpleTableIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:simpleTableIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:simpleTableIdentifier];
    }
    
    switch ([tableView tag]) {
        case tag_table_main:{
            cell.textLabel.text = [t_devicelist objectAtIndex:indexPath.row];
            cell.imageView.image = [UIImage imageNamed:@"ic_dialog_icon.png"];
            cell.imageView.frame = CGRectMake(cell.imageView.frame.origin.x, cell.imageView.frame.origin.y, 0, 0);
            cell.imageView.contentMode =UIViewContentModeScaleAspectFit;
            
            break;
        }
        case tag_table_confirm:{
            //cell.textLabel.text = [NSString stringWithFormat:@"Option %d", [indexPath row] + 1];
            cell.textLabel.text = [t_devicelist objectAtIndex:indexPath.row];
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            UISwitch *switchView = [[UISwitch alloc] initWithFrame:CGRectZero];
            cell.accessoryView = switchView;
            switchView.tag= indexPath.row;
            [switchView setOn:YES animated:NO];
            [switchView addTarget:self action:@selector(cfgConfirmSwitched:) forControlEvents:UIControlEventValueChanged];
            break;
        }
        default:
            break;
    }
    
    return cell;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [t_devicelist count];
}
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
/*-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *str = [t_devicelist objectAtIndex:indexPath.row];
    if(str. length > 50) {
        return  85;
    }
    else {
        return 60;
    }
}*/
//list item selected action
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int i = 0;
    int currDevNum = (int)[discovery_deviceList count];
    
    PIN_ctl  = nil;
    isCtlPIN = true;
    
    NSString *selectedDeviceRow = [t_devicelist objectAtIndex:indexPath.row];
    NSLog(@"<APP> You select the device:%@\n",selectedDeviceRow);

    for (i=0; i<currDevNum; i++)
    {
        [[discovery_deviceList objectAtIndex:i] getValue:&curDevInfo];
        if ([selectedDeviceRow isEqualToString:curDevInfo.dev_name])
        {
            NSLog(@"<APP> You select the device Mac:%@\n",curDevInfo.macAddress);
            break;
        }
        if (i == (currDevNum-1) ){

            curDevInfo.dev_name = @"";
            curDevInfo.ip = 0 ;
            curDevInfo.macAddress = @"";
            curDevInfo.type[0] = 0;
            curDevInfo.type[1] = 0;
        }
    }
    
    //NSString *alertTitle =[NSString stringWithFormat:@"Key in %@ PIN code", selectedDeviceRow];
    NSString *alertTitle = @"Key in device PIN code";
    
    if( floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1){
        // do stuff for iOS 8 and newer
        
        UIAlertController *alertController = [UIAlertController
                                              alertControllerWithTitle:alertTitle
                                              message:@"The PIN code will be display on device if the PIN code is exist.\nOtherwise, choose the skip option."
                                              preferredStyle:UIAlertControllerStyleAlert];
        
        [alertController addTextFieldWithConfigurationHandler:^(UITextField *textField){
            textField.placeholder = @"PIN Code";
            textField.keyboardType = UIKeyboardTypeNumberPad;
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(alertTextFieldDidChange:) name:UITextFieldTextDidChangeNotification object:textField];
        }];
        [self presentViewController:alertController animated:YES completion:nil];
        
        UIAlertAction *qrcodeAction = [UIAlertAction actionWithTitle:@"QR Code Scanner" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            //[self QRScanAction:nil event:nil];
        }];
        [alertController addAction:qrcodeAction];
        
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action){
            NSLog(@"<APP> control: after key in pin code");
            
            UITextField *pincode = alertController.textFields.firstObject;
            PIN_ctl = pincode.text;
            
            if ([PIN_ctl length]>0) {
                NSLog(@"<APP> input PIN is:%@", PIN_ctl);
                [self.mySimpleConfig rtk_sc_set_control_pin:PIN_ctl];
                
                UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                initWithTitle:@"Setting Action"
                                                message:@""
                                                delegate:self
                                                cancelButtonTitle:@"Exit"
                                                otherButtonTitles:@"Rename Device", @"Remove Device", nil];
                ctlaction_alert.tag = tag_ctl_VIEWaction;
                [ctlaction_alert show];
            }else{
                UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                initWithTitle:@"Warning"
                                                message:@"The PIN code is empty!"
                                                delegate:self
                                                cancelButtonTitle:@"OK"
                                                otherButtonTitles: nil];
                [ctlaction_alert show];
            }
            
            isCtlPIN = false;
        }];
        okAction.enabled = NO;
        
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:nil];
        
        [alertController addAction:cancelAction];
        [alertController addAction:okAction];
        
    }else if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_6_1) {
        // do stuff for iOS 7 and newer
        ctlPINAlert=[[UIAlertView alloc]
                     initWithTitle:alertTitle
                     message:@"The PIN code will be display on device if the PIN code is exist.\n\n\n"
                     delegate:self
                     cancelButtonTitle:@"OK"
                     otherButtonTitles:@"Cancel", nil];
        ctlPINAlert.tag = tag_ctl_VIEWshow;
        ctlPINAlert.alertViewStyle = UIAlertViewStylePlainTextInput;
	    
	    //add qrcode button
	    UIButton *btn_qrcode=[UIButton buttonWithType:UIButtonTypeRoundedRect];
	    [btn_qrcode setFrame:CGRectMake(12.0, 95, 40, 40)];
	    [btn_qrcode addTarget:self action:@selector(QRScanAction:event:) forControlEvents:UIControlEventTouchUpInside];
	    [btn_qrcode setBackgroundImage:[UIImage imageNamed:@"qrcode_img.png"] forState:UIControlStateNormal];
	    [ctlPINAlert setValue:btn_qrcode forKey:@"accessoryView"];
    
	    //add pin code text
	    //UITextField *text_pincode1 = [ctlPINAlert textFieldAtIndex:0];
	    text_pincode = [ctlPINAlert textFieldAtIndex:0];
	    CGRect frameRect = CGRectMake(56.0, 98.0, 215.0, 34.0);
	    text_pincode.frame = frameRect;
	    [text_pincode setBackgroundColor:[UIColor whiteColor]];
    
	    PIN_ctl = [self getPINcode : curDevInfo.macAddress];
	    if ([PIN_ctl length]>0) {
	        [text_pincode setText:PIN_ctl];
	    }else
	        [text_pincode setPlaceholder:@"XXXXXXXX"];

	    [text_pincode setKeyboardType:UIKeyboardTypeNumberPad];
	    [text_pincode setTag:tag_ctl_TEXTpincode];
	    UIFont *textFont = [UIFont fontWithName:@"Helvetica-Bold" size:26.0];
	    [text_pincode setFont:textFont];
	    //[ctlPINAlert addSubview:text_pincode];
    }else {
      // do stuff for older versions than iOS 7
        //add qrcode button
	    UIButton *btn_qrcode=[UIButton buttonWithType:UIButtonTypeRoundedRect];
	    [btn_qrcode setFrame:CGRectMake(12.0, 95, 40, 40)];
	    [btn_qrcode addTarget:self action:@selector(QRScanAction:event:) forControlEvents:UIControlEventTouchUpInside];
	    UIImage *btnImage = [UIImage imageNamed:@"qrcode_img.png"];
	    [btn_qrcode setImage:btnImage forState:UIControlStateNormal];
    
	    [ctlPINAlert addSubview:btn_qrcode];
    
	    //add pin code text
	    text_pincode = [[UITextField alloc] initWithFrame:CGRectMake(56.0, 98.0, 215.0, 34.0)];
	    [text_pincode setBackgroundColor:[UIColor whiteColor]];
    
	    PIN_ctl = [self getPINcode : curDevInfo.macAddress];
	    if ([PIN_ctl length]>0) {
	        [text_pincode setText:PIN_ctl];
	    }else
	        [text_pincode setPlaceholder:@"XXXXXXXX"];

	    [text_pincode setKeyboardType:UIKeyboardTypeNumberPad];
	    [text_pincode setTag:tag_ctl_TEXTpincode];
	    UIFont *textFont = [UIFont fontWithName:@"Helvetica-Bold" size:26.0];
	    [text_pincode setFont:textFont];
	    [ctlPINAlert addSubview:text_pincode];
    }

    [ctlPINAlert show];
}
//---------------------------------  UI table controllers  -------------------------------------

//---------------------------------  Button Action controllers  -------------------------------------
-(void)Discovery_triger
{
    [self Discovery_btnClik:nil];
}

- (IBAction)Discovery_btnClik:(id)sender
{
    if([self IsEnableWIFI])
    {
        
        [self.mySimpleConfig rtk_sc_stop];
        [self.mySimpleConfig rtk_sc_exit];
        
        t_devicelist = [NSMutableArray arrayWithObjects:nil];
        [self.tableDeviceList reloadData];
        
        isShowDiscoveryDevice = true;
        
        NSLog(@"<APP> Start to scan device!");
        
        /*step 1: clear previous dev list */
        [self.mySimpleConfig.pattern.dev_connected_list removeAllObjects];
        [self.mySimpleConfig rtk_sc_clear_device_list];
        
        /*step 2: gen and send scan data */
        NSString *str_bcastip = [self getIP_bcast];
        NSArray *subip = [str_bcastip componentsSeparatedByString:@"."];
        bcastip = ([subip[0] intValue]<<24) + ([subip[1] intValue]<<16) + ([subip[2] intValue]<<8) + ([subip[3] intValue]);
        NSLog(@"<APP> bcast ip : %x",bcastip);
        
        //[self.mySimpleConfig rtk_sc_set_control_password:nil];
        bcastdata = [self.mySimpleConfig rtk_sc_gen_discover_packet];
        
        [self startWaiting:@"Searching Devices":timeout_discovery];
        
        [self.mySimpleConfig rtk_sc_send_discover_packet:bcastdata ip:bcastip];
        discoveryTimer = [NSTimer scheduledTimerWithTimeInterval:0.3 target:self selector:@selector(sendDiscoveryCommand) userInfo:nil repeats:YES];
        
        [NSTimer scheduledTimerWithTimeInterval: timeout_discovery
                                         target: self
                                       selector:@selector(showDiscoveryDevice)
                                       userInfo: nil repeats:NO];

    }else{
        UIAlertView *wifialertView = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"No WIFI available!", @"AlertView")
                                      message:NSLocalizedString(@"You have no wifi connection available. Please connect to a WIFI network.", @"AlertView")
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:/*NSLocalizedString(@"Open settings", @"AlertView"),*/ nil];
        [wifialertView show];
    }
    
    
    
}
- (IBAction)ConfigDevice_btnClik:(id)sender
{
    if([self IsEnableWIFI])
    {
        SSID = nil;
        
#if USE_AUTO_SSID
        NSDictionary *ifs = [self.mySimpleConfig.pattern fetchSSIDInfo];
        NSString *alertMsg = @"";
        
        SSID = [ifs objectForKey:@"SSID"];
        //SSID = [self currentWifiSSID];
        if(SSID==nil)
        {
            SSID = @"";
        }
        NSLog(@"<APP> SSID == %@",SSID);
        //[self fetchSSIDInfo];
#endif
        
        alertMsg = [[NSString alloc]
                      initWithString:[NSString stringWithFormat:@"Home AP : %@",SSID]];
        
        
        UIAlertView *wifialertView = [[UIAlertView alloc]
                                      initWithTitle:alertMsg
                                      message:@"Please enter the AP password"
                                      delegate:self
                                      cancelButtonTitle:@"OK"
                                      otherButtonTitles:@"Cancel", nil];
        wifialertView.alertViewStyle = UIAlertViewStyleSecureTextInput;
        
        AP_password = [self getWiFipassword:SSID];
        
        UITextField *passwordField = [wifialertView textFieldAtIndex:0];
        passwordField.text = AP_password;
        
        wifialertView.tag = tag_cfg_VIEWwifi;
        [wifialertView show];
        
        
    }else{
        UIAlertView *wifialertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"No WIFI available!", @"AlertView")
                                  message:NSLocalizedString(@"You have no wifi connection available. Please connect to a WIFI network.", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                  otherButtonTitles:/*NSLocalizedString(@"Open settings", @"AlertView"),*/ nil];
        [wifialertView show];
    }

}


//---------------------------------  Button Action controllers  -------------------------------------


//---------------------------------  subAction controllers  -------------------------------------
-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    
    //control: after key in pin code
    if (alertView.tag == tag_ctl_VIEWshow) {
        if (buttonIndex == 0) {//OK
            
            NSLog(@"<APP> control: after key in pin code");
            if (isQRcodeAction) {
                NSLog(@"<APP> use qr coed!\n");
            }else{
                
                if ([PIN_ctl length]>0) {
                    NSLog(@"<APP> input PIN is:%@", PIN_ctl);
                    [self.mySimpleConfig rtk_sc_set_control_pin:PIN_ctl];
                    
                    UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                    initWithTitle:@"Setting Action"
                                                    message:@""
                                                    delegate:self
                                                    cancelButtonTitle:@"Exit"
                                                    otherButtonTitles:@"Rename Device", @"Remove Device", nil];
                    ctlaction_alert.tag = tag_ctl_VIEWaction;
                    [ctlaction_alert show];
                }else{
                    UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                    initWithTitle:@"Warning"
                                                    message:@"The PIN code is empty!"
                                                    delegate:self
                                                    cancelButtonTitle:@"OK"
                                                    otherButtonTitles: nil];
                    [ctlaction_alert show];
                }
                
                isCtlPIN = false;
            }
            
            
        } else {
            // Do something for cancel
            NSLog(@"<APP> input PIN code => cancel");
        }
        
    //control: after cotrol action selection
    }else if (alertView.tag == tag_ctl_VIEWaction) {
        if (buttonIndex == 0) {//Exit selection
            NSLog(@"<APP> Exit selected");
            
        }else if(buttonIndex == 1) {//Rename Device selection
            NSLog(@"<APP> Rename Device selected");
            
            UIAlertView * ctlRaname_alert = [[UIAlertView alloc] initWithTitle:@"Enter the Device Name:" message:@"" delegate:self cancelButtonTitle:@"Save" otherButtonTitles:@"Cancel",nil];
            ctlRaname_alert.alertViewStyle = UIAlertViewStylePlainTextInput;
            ctlRaname_alert.tag = tag_ctl_rename;
            [ctlRaname_alert show];
            
        }else if(buttonIndex == 2){//Remove Device selection
            NSLog(@"<APP> Remove Device selected");
            [self.mySimpleConfig rtk_sc_set_control_pin:PIN_ctl];
            
            curr_control_type = SC_DELETE_PROFILE;
            
            NSData *remove_data = [self.mySimpleConfig rtk_sc_gen_control_packet:curr_control_type];
            [self.mySimpleConfig rtk_sc_reset_control_result];
            [self.mySimpleConfig rtk_sc_send_control_packet:remove_data ip:curDevInfo.ip];
            isShowCtlRemove = true;
            [self startWaiting:@"Device Removing":-1];
            curr_event = CONTROL_STATE;
            
            NSLog(@"<APP> Remove action %d to device ip %x", curr_control_type, curDevInfo.ip);
        }
        
    //control: after cotrol action selection for rename
    }else if(alertView.tag == tag_ctl_rename){
        if (buttonIndex == 0) {//OK
            [self.mySimpleConfig rtk_sc_set_control_pin:PIN_ctl];
            
            curr_control_type = SC_RENAME_DEV;
            
            NSData *rename_data = [self.mySimpleConfig rtk_sc_gen_rename_dev_packet:newDeviceName];
            [self.mySimpleConfig rtk_sc_reset_control_result];
            [self.mySimpleConfig rtk_sc_send_rename_dev_packet:rename_data ip:curDevInfo.ip];
            isShowCtlRename = true;
            [self startWaiting:@"Device Renaming":-1];
            
            curr_event = CONTROL_STATE;
            
            NSLog(@"<APP> Rename action %d to device ip %x", curr_control_type, curDevInfo.ip);
        }
        
    //configure: after key in wifi password
    }else if(alertView.tag == tag_cfg_VIEWwifi){
        if (buttonIndex == 0) {//OK on key in wifi password
            
            [self setWiFipassword : SSID : AP_password];
            
            PIN_cfg  = nil;
            isCfgPIN = true;
            
            if( floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1){
                // do stuff for iOS 8 and newer

                UIAlertController *alertController = [UIAlertController
                                                      alertControllerWithTitle:@"Input Device PIN code"
                                                      message:@"The PIN code will be display on device if the PIN code is exist.\nOtherwise, choose the skip option."
                                                      preferredStyle:UIAlertControllerStyleAlert];
                
                UIAlertAction *qrcodeAction = [UIAlertAction actionWithTitle:@"QR Code Scanner" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                    //[self QRScanAction:nil event:nil];
                }];
                
                [alertController addAction:qrcodeAction];
                
                [alertController addTextFieldWithConfigurationHandler:^(UITextField *textField){
                    textField.placeholder = @"PIN Code";
                    textField.keyboardType = UIKeyboardTypeNumberPad;
                    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(alertTextFieldDidChange:) name:UITextFieldTextDidChangeNotification object:textField];
                }];
                
                [self presentViewController:alertController animated:YES completion:nil];
                
                
                UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                    [[NSNotificationCenter defaultCenter] removeObserver:self name:UITextFieldTextDidChangeNotification object:nil];
                    
                    UITextField *pincode = alertController.textFields.firstObject;
                    //UITextField *password = alertController.textFields.lastObject;
                    //NSLog(@"pincode:%@",pincode.text);
                    PIN_cfg = pincode.text;
                    
                    NSLog(@"<APP> Configure start");
                    
                    /* Step 1: check necessary items: SSID, PSW and key if necessary, and lock these input textfield */
                    int chk_result = [self check_cfgData];
                    if(chk_result==1)
                    {
                        [self.mySimpleConfig.pattern set_index:3];
                        [self startWaiting_progress:@"Device Configuring":120];
                        
                        /* Step 2: clear the buffer and set items to mib */
                        //NSString *user_pin = myAESKey.text;
                        [self.mySimpleConfig rtk_sc_set_pin:PIN_cfg];
                        self.mySimpleConfig.pattern.have_pin = 1;
                        [self.mySimpleConfig rtk_sc_set_ssid: SSID];
                        [self.mySimpleConfig rtk_sc_set_password: AP_password];
                        
                        NSLog(@"<APP> SSID: %@", self.mySimpleConfig.pattern.m_ssid);
                        NSLog(@"<APP> PSW: %@", self.mySimpleConfig.pattern.m_psw);
                        NSLog(@"<APP> PIN: %@", self.mySimpleConfig.pattern.m_pin);
                        
                        /* Step 3: do simple config */
                        [self.mySimpleConfig rtk_sc_gen_random];
                        [self.mySimpleConfig rtk_sc_build_profile];
                        //[self.mySimpleConfig rtk_sc_set_profileSendInterval:150000]; //150ms
                        //[self.mySimpleConfig rtk_sc_set_packetSendInterval:2];      //2ms
                        //[self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
                        [self setTimePacketPrarmeter];
                        
                        //cfgTimer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(handleCfgTimer:) userInfo:nil repeats:YES];
                        [NSThread detachNewThreadSelector:@selector(handleConfigThread:) toTarget:self withObject:nil];
                        
                        curr_event = CONFIGURE_STATE;
                        isCfgPIN = false;
                        
                    }else{
                        NSLog(@"<APP> Config error:%d",chk_result);
                        curr_event = NONE_STATE;
                        isCfgPIN = false;
                        
                        UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                        initWithTitle:@"Warning"
                                                        message:@"configure error!"
                                                        delegate:self
                                                        cancelButtonTitle:@"OK"
                                                        otherButtonTitles: nil];
                        [ctlaction_alert show];
                    }
                    
                }];
                
                okAction.enabled = NO;
                
                UIAlertAction *skipAction = [UIAlertAction actionWithTitle:@"Skip" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                
                    NSLog(@"<APP> configure condition:key in pin code - skip");
                    [self.mySimpleConfig.pattern set_index:2];
                    
                    //[self startWaiting:@"Device Configuring":-1];
                    [self startWaiting_progress:@"Device Configuring":120];
                    
                    NSLog(@"<APP> Configure start");
                    
                    /* Step 1: check necessary items: SSID, PSW and key if necessary, and lock these input textfield */
                    int chk_result = [self check_cfgData];
                    if(chk_result>=0)
                    {
                        /* Step 2: clear the buffer and set items to mib */
                        //NSString *user_pin = myAESKey.text;
                        [self.mySimpleConfig rtk_sc_set_pin: [self.mySimpleConfig rtk_sc_get_default_pin] ];
                        //self.mySimpleConfig.pattern.have_pin = 1;
                        [self.mySimpleConfig rtk_sc_set_ssid: SSID];
                        [self.mySimpleConfig rtk_sc_set_password: AP_password];
                        
                        NSLog(@"<APP> SSID: %@", self.mySimpleConfig.pattern.m_ssid);
                        NSLog(@"<APP> PSW: %@", self.mySimpleConfig.pattern.m_psw);
                        NSLog(@"<APP> PIN: %@", self.mySimpleConfig.pattern.m_pin);
                        
                        /* Step 3: do simple config */
                        [self.mySimpleConfig rtk_sc_gen_random];
                        [self.mySimpleConfig rtk_sc_build_profile];
                        //[self.mySimpleConfig rtk_sc_set_profileSendInterval:150000]; //150ms
                        //[self.mySimpleConfig rtk_sc_set_packetSendInterval:2];      //2ms
                        //[self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
                        [self setTimePacketPrarmeter];
                        
                        curr_event = CONFIGURE_STATE;
                        isCfgPIN = false;
                        //[self startTheBackground_cfg];
                        //cfgTimer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(handleCfgTimer:) userInfo:nil repeats:YES];
                        
                        [NSThread detachNewThreadSelector:@selector(handleConfigThread:) toTarget:self withObject:nil];
                        
                        NSLog(@"<APP> send config packet");
                        
                    }else{
                        NSLog(@"<APP> Config error:%d",chk_result);
                        curr_event = NONE_STATE;
                        isCfgPIN = false;
                    }
                }];
                [alertController addAction:skipAction];
                
                [alertController addAction:okAction];
                
            }else if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_6_1) {
    		// do stuff for iOS 7 and newer
                
                cfgPINAlert=[[UIAlertView alloc]
                             initWithTitle:@"Key in device PIN code"
                             message:@"The PIN code will be display on device if the PIN code is exist.\n\n\n"
                             delegate:self
                             cancelButtonTitle:@"OK"
                             otherButtonTitles:@"Skip", nil];
                cfgPINAlert.tag = tag_cfg_VIEWshow;
                
                cfgPINAlert.alertViewStyle = UIAlertViewStylePlainTextInput;
                //add qrcode button
	            UIButton *btn_qrcode=[UIButton buttonWithType:UIButtonTypeRoundedRect];
	            [btn_qrcode setFrame:CGRectMake(12.0, 95, 40, 40)];
	            [btn_qrcode addTarget:self action:@selector(QRScanAction:event:) forControlEvents:UIControlEventTouchUpInside];
	            [btn_qrcode setBackgroundImage:[UIImage imageNamed:@"qrcode_img.png"] forState:UIControlStateNormal];
	            [cfgPINAlert setValue:btn_qrcode forKey:@"accessoryView"];
            
	            //add pin code text
	            //UITextField *text_pincode1 = [ctlPINAlert textFieldAtIndex:0];
	            text_pincode = [cfgPINAlert textFieldAtIndex:0];
	            CGRect frameRect = CGRectMake(56.0, 98.0, 215.0, 34.0);
	            text_pincode.frame = frameRect;
	            [text_pincode setBackgroundColor:[UIColor whiteColor]];
	            [text_pincode setPlaceholder:@"XXXXXXXX"];
	            [text_pincode setKeyboardType:UIKeyboardTypeNumberPad];
	            [text_pincode setTag:tag_cfg_TEXTpincode];
	            UIFont *textFont = [UIFont fontWithName:@"Helvetica-Bold" size:26.0];
	            [text_pincode setFont:textFont];
	            //[ctlPINAlert addSubview:text_pincode];
                
                [cfgPINAlert show];
                
            }else {
                // do stuff for older versions than iOS 7
                
                cfgPINAlert=[[UIAlertView alloc]
                             initWithTitle:@"Key in device PIN code"
                             message:@"The PIN code will be display on device if the PIN code is exist.\n\n\n"
                             delegate:self
                             cancelButtonTitle:@"OK"
                             otherButtonTitles:@"Skip", nil];
                cfgPINAlert.tag = tag_cfg_VIEWshow;
                
                //add qrcode button
	            UIButton *btn_qrcode=[UIButton buttonWithType:UIButtonTypeRoundedRect];
	            [btn_qrcode setFrame:CGRectMake(12.0, 95, 40, 40)];
	            [btn_qrcode addTarget:self action:@selector(QRScanAction:event:) forControlEvents:UIControlEventTouchUpInside];
	            UIImage *btnImage = [UIImage imageNamed:@"qrcode_img.png"];
	            [btn_qrcode setImage:btnImage forState:UIControlStateNormal];
            
	            [cfgPINAlert addSubview:btn_qrcode];
            
	            //add pin code text
	            text_pincode = [[UITextField alloc] initWithFrame:CGRectMake(56.0, 98.0, 215.0, 34.0)];
	            [text_pincode setBackgroundColor:[UIColor whiteColor]];
	            [text_pincode setPlaceholder:@"XXXXXXXX"];
	            [text_pincode setKeyboardType:UIKeyboardTypeNumberPad];
	            [text_pincode setTag:tag_cfg_TEXTpincode];
	            UIFont *textFont = [UIFont fontWithName:@"Helvetica-Bold" size:26.0];
	            [text_pincode setFont:textFont];
	            [cfgPINAlert addSubview:text_pincode];
                
                [cfgPINAlert show];
            }
            
        }
        
    //configure: after key in pin code
    }else if(alertView.tag == tag_cfg_VIEWshow){
        if (buttonIndex == 0) {//OK or QR code
            NSLog(@"<APP> configure condition:key in pin code - OK or QR code");
            NSLog(@"<APP> Configure start");
            
            /* Step 1: check necessary items: SSID, PSW and key if necessary, and lock these input textfield */
            int chk_result = [self check_cfgData];
            if(chk_result==1)
            {
                [self.mySimpleConfig.pattern set_index:3];
                [self startWaiting:@"Device Configuring":-1];
                
                /* Step 2: clear the buffer and set items to mib */
                //NSString *user_pin = myAESKey.text;
                [self.mySimpleConfig rtk_sc_set_pin:PIN_cfg];
                self.mySimpleConfig.pattern.have_pin = 1;
                [self.mySimpleConfig rtk_sc_set_ssid: SSID];
                [self.mySimpleConfig rtk_sc_set_password: AP_password];

                NSLog(@"<APP> SSID: %@", self.mySimpleConfig.pattern.m_ssid);
                NSLog(@"<APP> PSW: %@", self.mySimpleConfig.pattern.m_psw);
                NSLog(@"<APP> PIN: %@", self.mySimpleConfig.pattern.m_pin);
                
                /* Step 3: do simple config */
                [self.mySimpleConfig rtk_sc_gen_random];
                [self.mySimpleConfig rtk_sc_build_profile];
                //[self.mySimpleConfig rtk_sc_set_profileSendInterval:150000]; //150ms
                //[self.mySimpleConfig rtk_sc_set_packetSendInterval:2];      //2ms
                //[self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
                [self setTimePacketPrarmeter];
                
                //cfgTimer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(handleCfgTimer:) userInfo:nil repeats:YES];
                [NSThread detachNewThreadSelector:@selector(handleConfigThread:) toTarget:self withObject:nil];

                curr_event = CONFIGURE_STATE;
                isCfgPIN = false;
                
            }else{
                
                if (isQRcodeAction)
                {
                    isQRcodeAction = false;
                    NSLog(@"<APP> using qr code!!\n");
                    
                }else{
                    NSLog(@"<APP> Config error:%d",chk_result);
                    curr_event = NONE_STATE;
                    isCfgPIN = false;
                    
                    if(chk_result==0)
                    {
                        UIAlertView *ctlaction_alert = [[UIAlertView alloc]
                                                        initWithTitle:@"Warning"
                                                        message:@"The PIN code is empty!"
                                                        delegate:self
                                                        cancelButtonTitle:@"OK"
                                                        otherButtonTitles: nil];
                        [ctlaction_alert show];
                    }
                }
            }
            
        }else if(buttonIndex == 1) {//SKIP
            NSLog(@"<APP> configure condition:key in pin code - skip");
            [self.mySimpleConfig.pattern set_index:2];
            
            //[self startWaiting:@"Device Configuring":-1];
            [self startWaiting_progress:@"Device Configuring":120];
            
            NSLog(@"<APP> Configure start");
            
            /* Step 1: check necessary items: SSID, PSW and key if necessary, and lock these input textfield */
            int chk_result = [self check_cfgData];
            if(chk_result>=0)
            {
                /* Step 2: clear the buffer and set items to mib */
                //NSString *user_pin = myAESKey.text;
                //[self.mySimpleConfig rtk_sc_set_pin:pinskip];
                //self.mySimpleConfig.pattern.have_pin = 1;
                [self.mySimpleConfig rtk_sc_set_ssid: SSID];
                [self.mySimpleConfig rtk_sc_set_password: AP_password];
                
                NSLog(@"<APP> SSID: %@", self.mySimpleConfig.pattern.m_ssid);
                NSLog(@"<APP> PSW: %@", self.mySimpleConfig.pattern.m_psw);
                NSLog(@"<APP> PIN: %@", self.mySimpleConfig.pattern.m_pin);
                
                /* Step 3: do simple config */
                [self.mySimpleConfig rtk_sc_gen_random];
                [self.mySimpleConfig rtk_sc_build_profile];
                //[self.mySimpleConfig rtk_sc_set_profileSendInterval:150000]; //150ms
                //[self.mySimpleConfig rtk_sc_set_packetSendInterval:2];      //2ms
                //[self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
                [self setTimePacketPrarmeter];
                
                curr_event = CONFIGURE_STATE;
                isCfgPIN = false;
                //[self startTheBackground_cfg];
                //cfgTimer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(handleCfgTimer:) userInfo:nil repeats:YES];
                
                [NSThread detachNewThreadSelector:@selector(handleConfigThread:) toTarget:self withObject:nil];
                
                NSLog(@"<APP> send config packet");
                
            }else{
                NSLog(@"<APP> Config error:%d",chk_result);
                curr_event = NONE_STATE;
                isCfgPIN = false;
            }
            
        }
        
    //configure: show list
    }else if(alertView.tag == tag_cfg_confirm){
        NSLog(@"<APP> Confirm!");
        
        dev_info pDevInfo;
        int i = 0;
        Boolean delaySearch = false;
        
        for (i=0; i<[config_deviceList count]; i++) {
            [[config_deviceList objectAtIndex:i] getValue:&pDevInfo];
            NSLog(@"<APP> [after changed] name : %@\n",pDevInfo.dev_name);
            NSLog(@"<APP> [after changed] ip   : %x\n",pDevInfo.ip);
            NSLog(@"<APP> [after changed] mac  : %@\n",pDevInfo.macAddress);
            NSLog(@"<APP> [after changed] type : %d\n",pDevInfo.type[0]);
            
            //user unwanted the device => delete profile
            if (pDevInfo.type[0]==0)
            {
               
                [self.mySimpleConfig rtk_sc_set_control_pin:PIN_backdoor];
                
                curr_control_type = SC_DELETE_PROFILE;
                
                NSData *remove_data = [self.mySimpleConfig rtk_sc_gen_control_packet:curr_control_type];
                [self.mySimpleConfig rtk_sc_reset_control_result];
                //for (j=0; j<5; j++) {*
                    [self.mySimpleConfig rtk_sc_send_control_packet:remove_data ip:pDevInfo.ip];
                //}
                
                [t_devicelist removeObject:pDevInfo.dev_name];
                [self.tableDeviceList reloadData];
                
                curr_event = CONTROL_STATE;
                
                NSLog(@"<APP> confirm:Remove action %d to device ip %x", curr_control_type, pDevInfo.ip);
                delaySearch = true;
                
            }else{
                //save pin code
                if ([PIN_cfg length]>0 && PIN_cfg!=nil) {
                    [self setPINcode : pDevInfo.macAddress : PIN_cfg];
                }
            }
            
        }
        
        
        if (delaySearch) {
            isShowCtlRemove = true;
            [self startWaiting:@"Device Removing":-1];
            curr_event = CONTROL_STATE;
            /*[NSTimer scheduledTimerWithTimeInterval: timeout_control
                                             target: self
                                           selector:@selector(showRemoveResult)
                                           userInfo: nil repeats:NO]
            [NSTimer scheduledTimerWithTimeInterval: timeout_control
                                             target: self
                                           selector:@selector(Discovery_triger)
                                           userInfo: nil repeats:NO];*/
        }else{
            [self Discovery_triger];
        }
        
    //after remove action
    }else if(alertView.tag == tag_ctl_removeEND){
        [self Discovery_triger];
        
    //after rename action
    }else if(alertView.tag == tag_ctl_renameEND){
        [self Discovery_triger];
        
    //wait alert show
    }else if(alertView.tag == tag_timer){
        
        if(buttonIndex == 0) {//Cancel
            NSLog(@"<APP> wait alert show: Cancel");
            timerCount = 0;
            [self stopTimerAction];
        }
        
    }else{
        // Do something with responses from other alertViews
    }
}
- (void) alertView:(UIAlertView *) actionAlert clickedButtonAtIndex:(NSInteger)buttonIndex
{
    // Get the field you added to the alert view earlier (you should also
    // probably validate that this field is there and that it is a UITextField but...)
    
    //UITextField* DeviceName_Field = nil;
    UITextField* PINcode_Field = nil;
    //UITextField* PassWord_Field = nil;
    NSString *str_password = nil;
    NSString *str_rename = nil;
	
    if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_6_1) {
    	// do stuff for iOS 7 and newer
	    if (actionAlert.tag==tag_ctl_VIEWshow) {
	        //PINcode_Field = (UITextField*)[actionAlert viewWithTag:tag_ctl_TEXTpincode];
	        PINcode_Field = [actionAlert textFieldAtIndex:0];
	        //PIN_ctl = [[text_pincode viewWithTag:tag_ctl_TEXTpincode] text];
	        //if([PINcode_Field text].length>0){
	            NSLog(@"<APP> tag_ctl_TEXTpincode text: %@", [PINcode_Field text]);
	            PIN_ctl = [PINcode_Field text];
	            return;
	        //}
	    }
    
	    if (actionAlert.tag==tag_cfg_VIEWshow) {
	        //PINcode_Field = (UITextField*)[actionAlert viewWithTag:tag_cfg_TEXTpincode];
	        PINcode_Field = [actionAlert textFieldAtIndex:0];
	        //if([PINcode_Field text].length>0){
	            NSLog(@"<APP> tag_cfg_TEXTpincode text: %@", [PINcode_Field text]);
	            PIN_cfg = [PINcode_Field text];
	            return;
	        //}
	    }
    }else {
        // do stuff for older versions than iOS 7
	    PINcode_Field = (UITextField*)[actionAlert viewWithTag:tag_ctl_TEXTpincode];
	    if([PINcode_Field text].length>0){
	        NSLog(@"<APP> tag_ctl_TEXTpincode text: %@", [PINcode_Field text]);
	        PIN_ctl = [PINcode_Field text];
	        return;
	    }

	    PINcode_Field = (UITextField*)[actionAlert viewWithTag:tag_cfg_TEXTpincode];
	    if([PINcode_Field text].length>0){
	        NSLog(@"<APP> tag_cfg_TEXTpincode text: %@", [PINcode_Field text]);
	        PIN_cfg = [PINcode_Field text];
	        return;
	    }
    }
    
   
    
    if([actionAlert alertViewStyle] == UIAlertViewStyleSecureTextInput){
    //PassWord_Field = (UITextField*)[actionAlert viewWithTag:tag_cfg_VIEWwifi];
    //if([PassWord_Field text].length>0){
        str_password = [[actionAlert textFieldAtIndex:0] text];
        NSLog(@"<APP> Password Text: %@", str_password);
        AP_password = str_password;
        return;
    }
    
    if([actionAlert alertViewStyle] == UIAlertViewStylePlainTextInput){
        str_rename = [[actionAlert textFieldAtIndex:0] text];
        if(str_rename.length>0){
            NSLog(@"<APP> rename Text: %@", str_rename);
            newDeviceName = str_rename;
            return;
        }
    }
}

-(void) showConfirmConfigDevice
{
    [self stopWaiting];
    
    if (NSFoundationVersionNumber > NSFoundationVersionNumber_iOS_6_1) {
    	// do stuff for iOS 7 and newer
	    UIAlertView* confirm_alert = [[UIAlertView alloc] initWithTitle:@"Configured Device"
                                  //message:@"\n\n\n\n\n\n\n\n\n\n"
                                  message:@"uncheck device if any unwanted!"
                                                           delegate:self
                                                  cancelButtonTitle:@"Confirm"
                                                  otherButtonTitles: nil];
    
	    confirm_alert.tag = tag_cfg_confirm;
            int table_height = 210;
	    if ([config_deviceList count]>0) {
	        table_height = 75 * (int)[t_devicelist count];
        
	        if(table_height>400)
	            table_height = 400;
	        if (table_height<90) {
	            table_height = 90;
	        }
	    }
    
	    UITableView* myView = [[UITableView alloc] initWithFrame:CGRectMake(10, 45, 264, table_height)
	                                                       style:UITableViewStyleGrouped];
	    myView.tag = tag_table_confirm;
	    [myView setAllowsSelection:NO];
	    myView.delegate = self;
	    myView.dataSource = self;
	    myView.backgroundColor = [UIColor clearColor];
	    [confirm_alert setValue:myView forKey:@"accessoryView"];
        [confirm_alert show];
    }else {
    	// do stuff for older versions than iOS 7
	    UIAlertView* confirm_alert = [[UIAlertView alloc] initWithTitle:@"Configured Device"
                                  //message:@"\n\n\n\n\n\n\n"
                                                            message:@"\n\n\n\n\n\n\n\n\n\n"
                                                           delegate:self
                                                  cancelButtonTitle:@"Confirm"
                                                  otherButtonTitles: nil];
    
	    confirm_alert.tag = tag_cfg_confirm;
    
	    UITableView* myView = [[UITableView alloc] initWithFrame:CGRectMake(10, 45, 264, 210)
	                                                       style:UITableViewStyleGrouped];
	    myView.tag = tag_table_confirm;
	    [myView setAllowsSelection:NO];
	    myView.delegate = self;
	    myView.dataSource = self;
	    myView.backgroundColor = [UIColor clearColor];
	    [confirm_alert addSubview:myView];
        [confirm_alert show];
    }

    
    
}
-(void)showDiscoveryDevice
{
    discovery_deviceList = [NSMutableArray arrayWithObjects:nil];
    
    int size = (int)[self.mySimpleConfig.pattern.dev_connected_list count];
    
    //NSMutableArray *dev_list = [self.mySimpleConfig rtk_sc_get_discovered_devices];
    //size = (int)[dev_list count];
    
    if(size>0)
    {
        int i = 0;
        //int j = 0;
        //dev_info pDevInfo;
        BOOL isInsert = true;
        dev_info d;
        NSValue *dev    = [[NSValue  alloc]init];
        
        for (i=0; i<size; i++) {
            dev = [self.mySimpleConfig.pattern.dev_connected_list objectAtIndex:i];
            [dev getValue:&d];
            NSLog(@"<APP> ===[row %d]=== \nname:%@\nip:%x\nmac:%@\ntype:%s\n", i+1, d.dev_name,d.ip,d.macAddress,d.type);
            
            isInsert = true;
            
            /*//check that it is new value
             for(j=0;j<i+1;j++)
             {
             if ([discovery_deviceList count]>0) {
             [[discovery_deviceList objectAtIndex:j] getValue:&pDevInfo];
             
             if ([d.macAddress isEqualToString:pDevInfo.macAddress]) {
             NSLog(@"<APP> the device(%@) is duplicate.\n",d.macAddress);
             isInsert = false;
             }
             }
             
             }*/
            
            if (isInsert)
            {
                NSValue *deviceItem = [NSValue value:&d withObjCType:@encode(dev_info)];
                [discovery_deviceList addObject:deviceItem];
                
                if ((d.dev_name==nil) || ([d.dev_name isEqualToString:@""])) {
                    
                    [t_devicelist addObject:d.macAddress];
                    
                }else{
                    [t_devicelist addObject:d.dev_name];
                }
            }
            
        }
        //t_devicelist = [[NSMutableArray alloc] initWithObjects:self.mySimpleConfig.pattern.dev_connected_list,nil];
        //[t_devicelist addObject:[NSString stringWithFormat:tmp]];
        //[t_devicelist addObject:[NSString stringWithFormat:d.dev_name]];
        
        
        [self.tableDeviceList reloadData];
    }
}

-(void)showRenameResult
{
    int control_result = [self.mySimpleConfig rtk_sc_get_control_result];
    if (control_result==1) {
        
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"Rename device successfully", @"AlertView")
                                  message:NSLocalizedString(@"", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                  otherButtonTitles:nil];
        alertView.tag = tag_ctl_renameEND;
        [alertView show];
    }else if(control_result==0){
        
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"Rename device failed", @"AlertView")
                                  message:NSLocalizedString(@"", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                  otherButtonTitles:nil];
        [alertView show];
    }
}

-(void)showRemoveResult
{
    int control_result = [self.mySimpleConfig rtk_sc_get_control_result];
    if (control_result==1) {
        
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"Delete device successfully", @"AlertView")
                                  message:NSLocalizedString(@"", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                  otherButtonTitles:nil];
        alertView.tag = tag_ctl_removeEND;
        [alertView show];
    }else if(control_result==0){
        
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"Delete device failed", @"AlertView")
                                  message:NSLocalizedString(@"", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                  otherButtonTitles:nil];
        [alertView show];
    }
}

//---------------------------------  subAction controllers  -------------------------------------

//--------------------------------- network utility ---------------------------------
-(void)sendDiscoveryCommand
{
    [self.mySimpleConfig rtk_sc_send_discover_packet:bcastdata ip:bcastip];
}
//--------------------------------- network utility ---------------------------------


//--------------------------------- sub utility ---------------------------------
-(int) check_cfgData
{
    
    if ( PIN_cfg==nil ) {
        return 0;
    }else if (SSID==nil){
        return -1;
    }else if (AP_password==nil){
        return -2;
    }
    
    return 1;
}
// 是否wifi
- (BOOL) IsEnableWIFI {
    return ([[Reachability reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable);
}
// 是否3G
- (BOOL) IsEnable3G {
    return ([[Reachability reachabilityForInternetConnection] currentReachabilityStatus] != NotReachable);
}
-(void)cfgConfirmSwitched:(id) sender
{
    int rowIndex = (int)[sender tag];
    UISwitch* switchControl = sender;
    NSLog( @"switch(%d) is %@", rowIndex, switchControl.on ? @"ON" : @"OFF" );
    
    dev_info pDevInfo;
    int i = 0;
    
    //get the element(rowIndex) device
    [[config_deviceList objectAtIndex:rowIndex] getValue:&pDevInfo];
    if (switchControl.on) {
        pDevInfo.type[0] = 1;
        pDevInfo.type[1] = 1;
    }else{
        pDevInfo.type[0] = 0;
        pDevInfo.type[1] = 0;
    }
    
    //delete the element(rowIndex) device
    [config_deviceList removeObjectAtIndex:rowIndex];
    //insert the new element(rowIndex) device
    NSValue *deviceItem = [NSValue value:&pDevInfo withObjCType:@encode(dev_info)];
    [config_deviceList insertObject:deviceItem atIndex: rowIndex];
    
    for (i=0; i<[config_deviceList count]; i++) {
        [[config_deviceList objectAtIndex:i] getValue:&pDevInfo];
        NSLog(@"<APP> [after changed] name : %@\n",pDevInfo.dev_name);
        NSLog(@"<APP> [after changed] ip   : %x\n",pDevInfo.ip);
        NSLog(@"<APP> [after changed] mac  : %@\n",pDevInfo.macAddress);
        NSLog(@"<APP> [after changed] type : %d\n",pDevInfo.type[0]);
    }

    
}

- (void)update{
    
    cfgProgressView.progress +=0.01;

    //when 100%
    if (cfgProgressView.progress == 1)
    {
        [self stopWaiting_progress];
        
        cfgProgressView.progress = 0;
    }
}

- (void)startWaiting_progress:(NSString *) wait_title :(float)timeout {
    if(waitTimer){
        [self stopWaiting_progress];
    }

    //  Purchasing Spinner.
    waitingAlert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(wait_title,@"")
                                              message:@"  Please wait...\n"
                                             delegate:self
                                    cancelButtonTitle:@"Cancel"
                                    otherButtonTitles:nil];
    waitingAlert.tag = tag_timer;
    
    waitingAlert.alertViewStyle = UIAlertViewStyleDefault;
    
    cfgProgressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
    [cfgProgressView setTrackTintColor:[UIColor lightGrayColor]];
    [cfgProgressView setProgressTintColor:[UIColor blueColor]];
    cfgProgressView.frame = CGRectMake(20, 20, 200, 15);
    cfgProgressView.progress = 0;
    [waitingAlert setValue:cfgProgressView forKey:@"accessoryView"];
    
    CGRect lblDownloadPercentFrame = CGRectMake(self.tableDeviceList.frame.size.width-50
                                                , self.tableDeviceList.frame.size.height-35, 60, 20);
    //lblDownloadPercent = [waitingAlert textFieldAtIndex:0];
    lblDownloadPercent = [[UILabel alloc]initWithFrame:lblDownloadPercentFrame];
    lblDownloadPercent.textColor = [UIColor whiteColor];
    lblDownloadPercent.backgroundColor = [UIColor clearColor];
    //[waitingAlert setValue:lblDownloadPercent forKey:@"accessoryView"];
    
    [waitingAlert show];
    
    if (timeout>0) {
        waitTimer = [NSTimer scheduledTimerWithTimeInterval:1.2 target:self selector:@selector(update) userInfo:nil repeats:true];
    }
    
    
}
- (void)stopWaiting_progress{
    [self.mySimpleConfig rtk_sc_stop];
    if(waitTimer){
        [waitTimer invalidate];
        waitTimer = nil;
    }
    
    if (waitingAlert) {
        [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
        waitingAlert = nil;
    }
    curr_event = NONE_STATE;
}

//show loading activity.
- (void)startWaiting:(NSString *) wait_title :(float)timeout {
    
    if(waitTimer){
        [self stopWaiting];
    }
    
    //  Purchasing Spinner.
    if (!waitingAlert) {
        waitingAlert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(wait_title,@"")
                                                     message:@"  Please wait...\n"
                                                    delegate:self
                                           cancelButtonTitle:@"Cancel"
                                           otherButtonTitles:nil];
        waitingAlert.tag = tag_timer;
	
        if( floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1){
            // do stuff for iOS 8 and newer
            //float version = floor(NSFoundationVersionNumber);
            
            //int www = waitingAlert.frame.size.width;
            //int hhh = waitingAlert.frame.size.height;
            
            UIActivityIndicatorView *actview = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
            actview.color=[UIColor blackColor];
            //actview.center=CGPointMake(www/2, hhh/2);
            [actview startAnimating];
            
            [waitingAlert setValue:actview forKey:@"accessoryView"];
            
            
            
        }else if ( floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_6_1) {
    	    // do stuff for iOS 7 and newer
	        UIView *v=[[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
	        v.backgroundColor=[UIColor whiteColor];
	        v.layer.masksToBounds = YES;
	        v.layer.cornerRadius = 6.0;
	        v.layer.borderWidth = 1;
	        v.layer.borderColor = [[UIColor lightGrayColor] CGColor];
	        [self.view addSubview:v];
        
	        UIActivityIndicatorView *actview = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	        actview.color=[UIColor blackColor];
	        actview.center=CGPointMake(v.frame.size.width/2, v.frame.size.height/2);
	        [actview startAnimating];
	        [v addSubview:actview];
        
	        [waitingAlert setValue:v forKey:@"accessoryView"];
	}else {
            // do stuff for older versions than iOS 7
	        [waitingAlert show];
        

	        UIActivityIndicatorView *waitingIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	        //connectingIndicator.frame = CGRectMake(139.0f-18.0f,50.0f,37.0f,37.0f);
	        waitingIndicator.frame = CGRectMake(20.0f,40.0f,37.0f,37.0f);
	        [waitingAlert addSubview:waitingIndicator];
	        [waitingIndicator startAnimating];
	}

        
        [waitingAlert show];
        
        if (timeout>0) {
            waitTimer = [NSTimer scheduledTimerWithTimeInterval: timeout
                                                         target: self
                                                       selector:@selector(stopWaiting)
                                                       userInfo: nil repeats:NO];
        }
        
        
    }
}
//hide loading activity.
- (void)stopWaiting
{
    
    [self stopTimerAction];
    
    /*if (isShowDiscoveryDevice) {
        [self showDiscoveryDevice];
        isShowDiscoveryDevice = false;
    }
    
    if (isShowCtlRename) {
        [self showRenameResult];
        isShowCtlRename = false;
    }*/
    
    /*if (isShowCtlRemove) {
        [self showRemoveResult];
        isShowCtlRemove = false;
    }*/
}

-(void)stopTimerAction
{
    [self.mySimpleConfig rtk_sc_stop];
    if(waitTimer){
        [waitTimer invalidate];
        waitTimer = nil;
    }
    if (discoveryTimer){
        [discoveryTimer invalidate];
        discoveryTimer = nil;
    }
    
    if (waitingAlert) {
        [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
        waitingAlert = nil;
    }
    curr_event = NONE_STATE;
}

/*- (void)fetchSSIDInfo {
    NSArray *ifs = (__bridge_transfer id)CNCopySupportedInterfaces();
    NSLog(@"<APP> Supported interfaces: %@", ifs);
    id info = nil;
    for (NSString *ifnam in ifs) {
        info = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)ifnam);
        NSLog(@"<APP> %@ => %@", ifnam, info);  //sigal data: info[@"SSID"]; info[@"BSSID"];
        if (info && [info count]) {
            break;
        }
    }
    //return info;
}*/
- (NSString *)currentWifiSSID {
    // Does not work on the simulator.
    NSString *ssid = nil;
    NSArray *ifs = (__bridge_transfer id)CNCopySupportedInterfaces();
    for (NSString *ifnam in ifs) {
        NSDictionary *info = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)ifnam);
        if (info[@"SSID"]) {
            ssid = info[@"SSID"];
        }
    }
    return ssid;
}
-(NSString *)getIPAddress
{
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    freeifaddrs(interfaces);
    return address;
}
-(NSString *)getIP_bcast
{
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_dstaddr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    freeifaddrs(interfaces);
    return address;
}

- (void)checkForWIFIConnection {
    Reachability* wifiReach = [Reachability reachabilityForLocalWiFi];
    NetworkStatus netStatus = [wifiReach currentReachabilityStatus];
    if (netStatus!=ReachableViaWiFi)
    {
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"No WIFI available!", @"AlertView")
                                  message:NSLocalizedString(@"You have no wifi connection available. Please connect to a WIFI network.", @"AlertView")
                                  delegate:self
                                  cancelButtonTitle:NSLocalizedString(@"Cancel", @"AlertView")
                                  otherButtonTitles:NSLocalizedString(@"Open settings", @"AlertView"), nil];
        [alertView show];
    }
}
- (CGSize)getScreenSize
{
    CGRect screenBound = [[UIScreen mainScreen] bounds];
    CGFloat orig_width = CGRectGetWidth(screenBound);
    CGFloat orig_height = CGRectGetHeight(screenBound);
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    if(UIInterfaceOrientationIsPortrait(orientation))
        screenBound.size = CGSizeMake(orig_width, orig_height);
    else if(UIInterfaceOrientationIsLandscape(orientation))
        screenBound.size = CGSizeMake(orig_height, orig_width);
    return screenBound.size;
}

-(NSString*)getWiFipassword : (NSString *)APname
{
    NSString *passwordAllData = @"";
    NSString *password = @"";
    
    passwordAllData = [APInfo_DataFile objectForKey:@"APINFO"];
    NSArray *APData = [passwordAllData componentsSeparatedByString:@";"];
    NSArray *APItemInfo = nil;
    
    for (int i = 0; i < [APData count]; i++) {
        NSLog(@"<APP> get AP-%d:%@\n", i+1, [APData objectAtIndex:i]);
        
        APItemInfo = [ [APData objectAtIndex:i] componentsSeparatedByString:@","];
        if( [APname isEqualToString: [APItemInfo objectAtIndex:0] ] )
        {
            password = [APItemInfo objectAtIndex:1];
            return password;
        }
    }
    
    
    return password;
}
-(Boolean)setWiFipassword : (NSString *)APname : (NSString *)password
{
    Boolean ret = false;
    Boolean isNewAP = true;
    //check previous data
    NSString *preWiFiAllData = @"";
    NSString *storeWiFiData = @"";
    NSString *storeWiFiAllData = @"";
    
    preWiFiAllData = [APInfo_DataFile objectForKey:@"APINFO"];
    
    NSArray *APData = [preWiFiAllData componentsSeparatedByString:@";"];
    NSArray *APItemInfo = nil;
    int APNum = (int)[APData count]-1;
    for (int i = 0; i < APNum; i++)
    {
        NSLog(@"<APP> set AP-%d:%@\n", i+1, [APData objectAtIndex:i]);
        
        APItemInfo = [ [APData objectAtIndex:i] componentsSeparatedByString:@","];
        if( [APname isEqualToString: [APItemInfo objectAtIndex:0] ] )
        {
            isNewAP = false;
            break;
        }

    }
    
    if (isNewAP) {//new
        
        if(preWiFiAllData==nil)
            preWiFiAllData = @"";
        
        storeWiFiAllData = [preWiFiAllData stringByAppendingString:APname];
        storeWiFiAllData = [storeWiFiAllData stringByAppendingString:@","];
        storeWiFiAllData = [storeWiFiAllData stringByAppendingString:password];
        storeWiFiAllData = [storeWiFiAllData stringByAppendingString:@";"];
    }else{//update
        for (int i = 0; i < APNum; i++)
        {
            
            APItemInfo = [ [APData objectAtIndex:i] componentsSeparatedByString:@","];
            if( [APname isEqualToString: [APItemInfo objectAtIndex:0] ] )
            {
                storeWiFiData = [NSString stringWithFormat:@"%@,%@;", [APItemInfo objectAtIndex:0], password];
            }else{
                storeWiFiData = [NSString stringWithFormat:@"%@,%@;", [APItemInfo objectAtIndex:0], [APItemInfo objectAtIndex:1]];
            }
            storeWiFiAllData = [storeWiFiAllData stringByAppendingString:storeWiFiData];
        }
    }

    
    [APInfo_DataFile setValue:storeWiFiAllData forKey:@"APINFO"];
    [APInfo_DataFile synchronize];
    
    ret = true;
    
    return ret;
}

-(NSString*)getPINcode : (NSString *)macaddress
{
    NSString *PINAllData = @"";
    NSString *pin = @"";
    
    PINAllData = [PINCode_DataFile objectForKey:@"PININFO"];
    NSArray *pinData = [PINAllData componentsSeparatedByString:@";"];
    NSArray *pinItemInfo = nil;
    
    for (int i = 0; i < [pinData count]; i++) {
        NSLog(@"<APP> AP-%d getPINcode %@\n", i+1, [pinData objectAtIndex:i]);
        
        pinItemInfo = [ [pinData objectAtIndex:i] componentsSeparatedByString:@","];
        if( [macaddress isEqualToString: [pinItemInfo objectAtIndex:0] ] )
        {
            pin = [pinItemInfo objectAtIndex:1];
            return pin;
        }
    }

    return pin;
}
-(Boolean)setPINcode : (NSString *)macaddress : (NSString *)pin
{
    Boolean ret = false;
    Boolean isNewPIN = true;
    //check previous data
    NSString *prePINAllData = @"";
    NSString *storePINData = @"";
    NSString *storePINAllData = @"";
    
    prePINAllData = [PINCode_DataFile objectForKey:@"PININFO"];
    
    NSArray *PINData = [prePINAllData componentsSeparatedByString:@";"];
    NSArray *PINItemInfo = nil;
    int PINNum = (int)[PINData count]-1;
    for (int i = 0; i < PINNum; i++)
    {
        NSLog(@"<APP> AP-%d get origin PINcode %@\n", i+1, [PINData objectAtIndex:i]);
        
        PINItemInfo = [ [PINData objectAtIndex:i] componentsSeparatedByString:@","];
        if( [macaddress isEqualToString: [PINItemInfo objectAtIndex:0] ] )
        {
            isNewPIN = false;
        }
        
    }
    
    if (isNewPIN) {
        
        if(prePINAllData==nil)
            prePINAllData = @"";
        
        storePINAllData = [prePINAllData stringByAppendingString:macaddress];
        storePINAllData = [storePINAllData stringByAppendingString:@","];
        storePINAllData = [storePINAllData stringByAppendingString:pin];
        storePINAllData = [storePINAllData stringByAppendingString:@";"];
    }else{
        for (int i = 0; i < PINNum; i++)
        {
            NSLog(@"<APP> AP-%d setPINcode %@\n", i+1, [PINData objectAtIndex:i]);
            
            PINItemInfo = [ [PINData objectAtIndex:i] componentsSeparatedByString:@","];
            if( [macaddress isEqualToString: [PINItemInfo objectAtIndex:0] ] )
            {
                storePINAllData = [NSString stringWithFormat:@"%@,%@;", [PINItemInfo objectAtIndex:0], pin];
            }else{
                storePINAllData = [NSString stringWithFormat:@"%@,%@;", [PINItemInfo objectAtIndex:0], [PINItemInfo objectAtIndex:0]];
            }
            storePINAllData = [storePINAllData stringByAppendingString:storePINData];
        }
    }
    
    [APInfo_DataFile setValue:storePINAllData forKey:@"PININFO"];
    [APInfo_DataFile synchronize];
    
    ret = true;
    
    return ret;
}


-(void)animation1
{
    if (upOrdown == NO) {
        num ++;
        _line.frame = CGRectMake(40, 20+2*num, 220, 2);
        if (2*num == 280) {
            upOrdown = YES;
        }
    }
    else {
        num --;
        _line.frame = CGRectMake(40, 20+2*num, 220, 2);
        if (num == 0) {
            upOrdown = NO;
        }
    }
    
}

/* configure Send Timer*/
- (void)handleConfigThread: (NSTimer *)sender
{
    [self.mySimpleConfig rtk_sc_start];
}

/* Timer Handler */
- (void)handleTimer: (NSTimer *)sender
{
    int ret = -1;
    int indexItem = 0;
    switch (curr_event) {
        case NONE_STATE:
            break;
        case SCAN_STATE:
            curr_event = NONE_STATE;
            break;
        case CONFIGURE_STATE:
            
            if (timerCount++ < timeout_cfg)
            {
                NSLog(@"<APP> wait %d for config ack!!!!!!!!!!!!\n",timerCount);
                
                if ([self.mySimpleConfig rtk_sc_get_cfgACK_state] && timerCount%3==0) { //check cfg ACK state
                    if (timerCount>30)
                    {
                        //NSLog(@"<APP> Config phase two");
                        [self.mySimpleConfig rtk_sc_set_profileSendInterval:500000]; //500ms
                        [self.mySimpleConfig rtk_sc_set_packetSendInterval:5000];    //5ms
                        [self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
                    }
                }
                
                /*if (timerCount>30) {
                    if (cfgTimer){
                        [cfgTimer invalidate];
                        cfgTimer = nil;
                    }
                }*/
                
                
                /* 4. update result, and check configure timeout */
                //if ([self.mySimpleConfig.pattern.ack_host count]==0)
                if ([self.mySimpleConfig rtk_get_connected_sta_num]==0) {
                    return ;
                }
                
                //after ack and then wait 5s for all device config finish
                //if( (checkFinishWait_cfg--) >0)
                //    return;

                //checkFinishWait_cfg = 20;
                
                timerCount = 0;
                [self stopWaiting];
                
                int ackHostNum = [self.mySimpleConfig rtk_get_connected_sta_num];
                //int connectedNum = 0;
                
                //if ([self.mySimpleConfig.pattern.ack_host count]>0 || [self.mySimpleConfig rtk_get_connected_sta_num]>0){
                if (ackHostNum>0){
                    
                    //connectedNum = [self.mySimpleConfig rtk_get_connected_sta_num];
                    
                    NSValue *dev = nil;//[self.mySimpleConfig.pattern.extend_ack_host objectAtIndex:0];
                    dev_info curr_dev;
                    
                    config_deviceList = [NSMutableArray arrayWithObjects:nil];
                    t_devicelist = [NSMutableArray arrayWithObjects:nil];
                    
                    for (indexItem=0; indexItem< ackHostNum; indexItem++)
                    {
                        //mac = [[NSString alloc]initWithString:[self.mySimpleConfig.pattern.ack_host objectAtIndex:indexItem]];
                        //[t_devicelist addObject:mac];
                        
                        dev = [self.mySimpleConfig.pattern.extend_ack_host objectAtIndex:indexItem];
                        [dev getValue:&curr_dev];
                        
                        if(curr_dev.dev_name==nil)curr_dev.dev_name=curr_dev.macAddress;
                        
                        NSLog(@"<APP> curr_dev name is %@\nip is %x\nmac is %@\ntype is %s\n"
                              , curr_dev.dev_name
                              , curr_dev.ip
                              , curr_dev.macAddress
                              , curr_dev.type);
                        [t_devicelist addObject:curr_dev.dev_name];
                        
                        curr_dev.type[0] = 1;
                        curr_dev.type[1] = 1;
                        
                        NSValue *deviceItem = [NSValue value:&curr_dev withObjCType:@encode(dev_info)];
                        [config_deviceList addObject:deviceItem];
                        
                    }
                    
                    discovery_deviceList = nil;
                    [discovery_deviceList addObject:config_deviceList];
                    
                    [self.mySimpleConfig rtk_sc_stop];
                    [self.tableDeviceList reloadData];
                    
                    [self showConfirmConfigDevice];
                    curr_event = NONE_STATE;
                    
                }
            }else{
                [self.mySimpleConfig rtk_sc_stop];
                
                //if ([self.mySimpleConfig.pattern.ack_host count]==0)
                {
                    UIAlertView* confirm_alert = [[UIAlertView alloc] initWithTitle:@"Configure Timeout"
                                                                            message:@""
                                                                           delegate:self
                                                                  cancelButtonTitle:@"OK"
                                                                  otherButtonTitles: nil];
                    
                    [confirm_alert show];
                }/*else{
                    [self showConfirmConfigDevice];
                }*/
                curr_event = NONE_STATE;
                [self stopWaiting];
                timerCount = 0;
                
            }
            
            break;
        case CONTROL_STATE:
            
            if (timerCount++ < timeout_control)
            {
                ret = [self.mySimpleConfig rtk_sc_get_control_result];
                if (ret!=1) { //status:1 success
                    NSLog(@"<APP> wait control ack");
                    if (curr_control_type == SC_RENAME_DEV) {
                        NSData *rename_data = [self.mySimpleConfig rtk_sc_gen_rename_dev_packet:newDeviceName];
                        [self.mySimpleConfig rtk_sc_send_rename_dev_packet:rename_data ip:curDevInfo.ip];
                    }else if(curr_control_type == SC_DELETE_PROFILE){
                        NSData *remove_data = [self.mySimpleConfig rtk_sc_gen_control_packet:curr_control_type];
                        [self.mySimpleConfig rtk_sc_send_control_packet:remove_data ip:curDevInfo.ip];
                    }
                    
                    return;
                }
                
                if(timerCount!=timeout_control)
                {
                    if (curr_control_type == SC_RENAME_DEV) {
                        checkFinishWait_control-=2;
                        NSLog(@"wait rename finish: %d",checkFinishWait_control);
                    }else if (curr_control_type == SC_DELETE_PROFILE){
                        NSLog(@"wait remove finish: %d",checkFinishWait_control--);
                    }
                    
                    //after ack and then wait 8s for all device config finish
                    if( checkFinishWait_control >0)
                        return;
                }
                checkFinishWait_control = 20;
                
                if (curr_control_type == SC_RENAME_DEV) {
                    isShowCtlRename = false;
                    [self showRenameResult];
                    
                }else if (curr_control_type == SC_DELETE_PROFILE){
                    isShowCtlRemove = false;
                    [self showRemoveResult];
                    
                }else
                    return;
                
                [self stopTimerAction];
                curr_event = NONE_STATE;
                timerCount = 0;
                
            }else{
                NSString *alerttitle = nil;
                [self stopTimerAction];
                curr_event = NONE_STATE;
                timerCount = 0;
                
                if (curr_control_type == SC_RENAME_DEV) {
                    alerttitle = @"Rename Timeout";
                }else if (curr_control_type == SC_DELETE_PROFILE){
                    alerttitle = @"Remove Timeout";
                }
                
                UIAlertView* ret_alert = [[UIAlertView alloc] initWithTitle:alerttitle
                                                                        message:@""
                                                                       delegate:self
                                                              cancelButtonTitle:@"OK"
                                                              otherButtonTitles: nil];
                
                [ret_alert show];
            }
            
            break;
            
        default:
            break;

    }
}

- (void)setTimePacketPrarmeter
{
    [self.mySimpleConfig rtk_sc_set_profileSendInterval:200000]; //200ms
    [self.mySimpleConfig rtk_sc_set_packetSendInterval:10];      //10ms
    [self.mySimpleConfig rtk_sc_set_eachPacketCounts:1];
}

- (void)alertTextFieldDidChange:(NSNotification *)notification{
    UIAlertController *alertController = (UIAlertController *)self.presentedViewController;
    if (alertController) {
        UITextField *login = alertController.textFields.firstObject;
        UIAlertAction *okAction = alertController.actions.lastObject;
        
        BOOL enable = login.text.length == 8;
        
        okAction.enabled = enable;
    }
}
/*- (void)performBlockInBackground_cfg:(void (^)())block {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        block();
    });
}
- (void)startTheBackground_cfg {
	[NSThread detachNewThreadSelector:@selector(startTheBackgroundJob_cfg) toTarget:self withObject:nil];
}

- (void) startTheBackgroundJob_cfg {
    
    while (curr_event == CONFIGURE_STATE) {
        [self.mySimpleConfig rtk_sc_start];
    }
    NSLog(@"<APP> startTheBackgroundJob_cfg Stop");
	
}*/
//--------------------------------- sub utility ---------------------------------
@end
