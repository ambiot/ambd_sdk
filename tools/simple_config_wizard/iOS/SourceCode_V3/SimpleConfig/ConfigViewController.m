//
//  ConfigViewController.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/11.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConfigViewController.h"
#import <SystemConfiguration/CaptiveNetwork.h>
#import "ClientViewController.h"
#import "RCSwitchOnOff.h"
#import "Util.h"

#define timeout_cfg         120
#define timeout_cfg_step1   50

#define tag_table_confirm   2
#define tag_timer           10101
#define tag_cfg_confirm     10601
#define tag_cfg_setNumber   10602

//#define softAP_SSID_prefix @"LoveRTK"

@implementation ConfigViewController
@synthesize m_input_ssid, m_input_password,m_input_pin, m_config_button;
@synthesize simpleConfig;
@synthesize m_qrscan_line;
@synthesize waitingAlert,cfgProgressView;
@synthesize confirm_list;

NSUserDefaults *targetAP_DataFile = nil;    //SSID
NSUserDefaults *APInfo_DataFile = nil;      //SSID1,password1;SSID,password2;...

NSString *PIN_cfg = nil, *QR_PIN=nil;
NSString *homeAP_SSID = @"";
NSString *homeAP_password = nil;


NSTimer *waitTimer;
NSTimer *m_timer;
unsigned int timerCount = 0;

int g_config_device_num = 0;
int unconfirmIndex = -1;
int g_noBackTargetAP_count = 0;

NSMutableArray *config_deviceList;      //context:  dev_info(struct)
UIAlertController *cfg_alertController;

BOOL isPIN_on;

//soft AP

BOOL isTipSoftAP;
BOOL isSoftAPmode;
BOOL isAlertWiFiSetting;
BOOL isSwithToWiFiSetting;
BOOL isBackToWiFiSetting;
BOOL isCheckHomeAP;

NSString *softAP_SSID = @"";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"config viewDidLoad");
    
    CGRect textfield_pwd = [self.view convertRect:self.m_input_password.frame toView:self.view];
    int x,y,w,h;
    x = textfield_pwd.origin.x;
    y = textfield_pwd.origin.y;
    w = textfield_pwd.size.width;
    h = textfield_pwd.size.height;
    
    RCSwitchOnOff* pinSwitch = [[RCSwitchOnOff alloc] initWithFrame:CGRectMake(x, y+h+22, 70, 70)];
    [pinSwitch setOn:NO];
    [self.view addSubview:pinSwitch];
    
    [pinSwitch addTarget:self action:@selector(isUsePinSwitched:) forControlEvents:UIControlEventValueChanged];
    
    confirm_list = nil;
    
    self.tableDeviceList.tag    = tag_table_confirm;
    self.tableDeviceList.delegate = self;
    self.tableDeviceList.dataSource = self;
    
    // Do any additional setup after loading the view, typically from a nib.
    homeAP_SSID = [Util fetchCurrSSID];
    
    [m_input_ssid setText:homeAP_SSID];
    [m_input_ssid addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [m_input_ssid setEnabled:NO];
    
    if(APInfo_DataFile==nil)
        APInfo_DataFile = [NSUserDefaults standardUserDefaults];
    
    if(targetAP_DataFile==nil)
        targetAP_DataFile = [NSUserDefaults standardUserDefaults];
    
    homeAP_password = [self getWiFipassword:homeAP_SSID];
    [m_input_password addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [m_input_password setText:homeAP_password];
    
    [m_input_pin addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];

    m_context.m_mode = MODE_INIT;
    simpleConfig = [[SimpleConfig alloc] init];
    
    if(isTipSoftAP)
        isTipSoftAP = NO;
    if(isSoftAPmode)
        isSoftAPmode = NO;

    isPIN_on = NO;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidDisappear:(BOOL)animated
{
    // Must release simpleConfig, so that its asyncUDPSocket delegate won't receive data
    NSLog(@"config viewDidDisappear");

    [simpleConfig rtk_sc_close_sock];
    #ifdef ARC
    [simpleConfig dealloc];
    #endif
    simpleConfig = nil;

    if ([waitTimer isValid]) {
        [waitTimer invalidate];
        waitTimer = nil;
    }
    
    [super viewDidDisappear:animated];
}

- (void)viewWillAppear:(BOOL)animated
{
    NSLog(@"config viewWillAppear");
    if (simpleConfig==nil) {
        simpleConfig = [[SimpleConfig alloc] init];
    }

    m_timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(configTimerHandler:) userInfo:nil repeats:YES];
    //NSLog(@"config view will appear");
}

- (void)dealloc {
#ifdef ARC
    [m_input_ssid release];
    [m_input_password release];
    [m_config_button release];
    [config_deviceList release];
    
    [simpleConfig dealloc];
    [m_context.m_timer invalidate];
    [m_context.m_timer release];
    [super dealloc];
#endif
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if([segue.identifier isEqualToString:@"SegueController"])
    {
        ClientViewController *client_vc = segue.destinationViewController;
        struct dev_info dev;
        NSValue *dev_val = [simpleConfig.config_list objectAtIndex:unconfirmIndex];
        [dev_val getValue:&dev];
        
        client_vc.sharedData = [[NSValue alloc] initWithBytes:&dev objCType:@encode(struct dev_info)];
    }
   
    
}

/* Hide the keyboard when pushing "enter" */
- (BOOL)textFieldDoneEditing:(UITextField *)sender
{
    //NSLog(@"textFieldDoneEditing, Sender is %@", sender);
    UITextField *target = sender;
    return [target resignFirstResponder];
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if([text isEqualToString:@"\n"])
    {
        [textView resignFirstResponder];
        return NO;
    }
    return YES;
}

-(void)config_action_directly
{
    PIN_cfg = m_input_pin.text;
    if(PIN_cfg==nil)PIN_cfg = @"";
    
    g_config_device_num = 1;
    [simpleConfig rtk_sc_config_set_devNum:g_config_device_num];
    [self startWaiting_progress:@"Device Configuring":120];
    [self configAction:PIN_cfg];
}

- (BOOL)isNum:(int)num
{
    BOOL ret = NO;
    
    if(num>=0x30 && num<= 0x39){
        ret = YES;
    }
    
    return ret;
}

- (BOOL)isPureNumberCharacters:(NSString*)_text
{
    int i = 0,a = 0;
    for(i=0;i<[_text length];++i){
        a=[_text characterAtIndex:i];
        if(![self isNum:a]){
            return NO;
        }
    }
    return YES;
}

/* action responder */
- (IBAction)rtk_start_listener:(id)sender
{
    NSString *tmp_pin = @"";
    
    isCheckHomeAP = NO;
    isAlertWiFiSetting = NO;
    isSwithToWiFiSetting = NO;
    isBackToWiFiSetting = NO;
    unconfirmIndex = -1;
    g_noBackTargetAP_count = 0;
    
    NSLog(@"SSID/pwd : %@ / %@",homeAP_SSID,m_input_password.text);
    
    [self setWiFipassword : homeAP_SSID : m_input_password.text];
    [self setTargetAP_SSID:homeAP_SSID];
    
    //check PIN Code
    if(isPIN_on){
        tmp_pin = m_input_pin.text;
        if(tmp_pin==nil)tmp_pin = @"";
        if([tmp_pin length]!=8){
            UIAlertView *alertShow = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"Warning", @"AlertView")
                                      message:@"Invalid PIN code. Please input 8 numbrers for PIN code."
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:nil];
            [alertShow show];
            return;
        }else if(![self isPureNumberCharacters:tmp_pin]){
            UIAlertView *alertShow = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"Warning", @"AlertView")
                                      message:@"Invalid PIN code. Please input 8 numbrers for PIN code."
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:nil];
            [alertShow show];
            return;
        }
        
    }
    
    if(isTipSoftAP){

        isTipSoftAP = NO;
        
        NSString *msg = @"";
        
#if defined(softAP_SSID_prefix)
        msg = [NSString stringWithFormat:@"%@-XXXXXXXXXX\nPassword:          12345678\n\nAfter the device connected, you need to back to this APP immediately.",softAP_SSID_prefix];
#else
        msg = @"Name: @RSC-XXXXXXXXXX\nPassword:          12345678\n\nAfter the device connected, you need to back to this APP immediately.";
#endif
        
        UIAlertController *dialog_softAP = [UIAlertController alertControllerWithTitle:@"Please connect your device \non WiFi setting to contiune.\n"
                                                                                     message:msg
                                                                              preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            NSString *nowSSID = [Util fetchCurrSSID];
            NSString *softAP_BSSID = @"";
            softAP_BSSID= [Util fetchCurrBSSID];
            
            [self setTargetAP_SSID:homeAP_SSID];

            [simpleConfig rtk_sc_softAP_init:softAP_BSSID :(int )[softAP_BSSID length]];
            
            isSoftAPmode = YES;
            
            [NSTimer scheduledTimerWithTimeInterval:5 target:self selector:@selector(checkSoftAPmode:) userInfo:nowSSID repeats:NO];
            [NSTimer scheduledTimerWithTimeInterval:0.3 target:self selector:@selector(gotoSysWiFiSetting) userInfo:nil repeats:NO];
            

        }];
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            isSoftAPmode = NO;
        }];
        
        [dialog_softAP addAction:cancelAction];
        [dialog_softAP addAction:okAction];
        
        [self presentViewController:dialog_softAP animated:YES completion:nil];

    }else if(isSoftAPmode==YES){
        
        NSString *softAP_BSSID = @"";
        softAP_SSID = [Util fetchCurrSSID];
        softAP_BSSID= [Util fetchCurrBSSID];
        NSLog(@"isSoftAPmode:%@(%@)",softAP_SSID,softAP_BSSID);
        
        [simpleConfig rtk_sc_set_sc_model:SC_MODEL_1 duration:-1]; //R3
        if([simpleConfig rtk_sc_isMyDevice:softAP_SSID :(int)[softAP_SSID length]]){
            
            [self config_action_directly];
        }else{
            NSLog(@"The SSID of Soft AP is not my device");
            
            m_context.m_mode = MODE_INIT;
            if(isTipSoftAP)
                isTipSoftAP = NO;
            if(isSoftAPmode)
                isSoftAPmode = NO;
            
            //show about
            UIAlertView *aboutShow = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"Error", @"AlertView")
                                      message:@"The name of AP is not my device."
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:nil];
            [aboutShow show];
        }

    }else{
        
        cfgProgressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
        [cfgProgressView setTrackTintColor:[UIColor lightGrayColor]];
        [cfgProgressView setProgressTintColor:[UIColor blueColor]];
        cfgProgressView.frame = CGRectMake(20, 20, 200, 15);
        cfgProgressView.progress = 0;
        
        isSoftAPmode = NO;
        isTipSoftAP = NO;
        [self config_action_directly];
    }
    
    
}

-(int)configAction: (NSString *)m_PIN
{
    
    timerCount = 0;
    int ret = RTK_FAILED;
    if (m_context.m_mode == MODE_INIT || m_context.m_mode == MODE_WAIT_FOR_IP) {
        
        if(isSoftAPmode){
            [simpleConfig rtk_sc_set_sc_model:SC_MODEL_1 duration:-1]; //R3
        }else{
            [simpleConfig rtk_sc_set_sc_model:SC_MODEL_2 duration:-1];//R1
        }
        
        NSString *ssid = m_input_ssid.text;
        NSString *pass = m_input_password.text;
        NSString *pin = m_PIN;
        
        timerCount = 0;
        
        ret = [simpleConfig rtk_sc_config_start:ssid psw:pass pin:pin];
        if (ret==RTK_FAILED) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_ERROR message:SC_UI_ALERT_WITHOUT_IP delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
            [alert show];
            return RTK_FAILED;
        }
        m_context.m_mode = MODE_CONFIG;
        
        [m_config_button setTitle:SC_UI_STOP_BUTTON forState:UIControlStateNormal];
        
        return RTK_SUCCEED;
    }else if(m_context.m_mode == MODE_CONFIG){
        // stop sending profile
        m_context.m_mode = MODE_INIT;
        [m_config_button setTitle:SC_UI_START_BUTTON forState:UIControlStateNormal];
        [simpleConfig rtk_sc_config_stop];

        return RTK_FAILED;
    }
    return RTK_FAILED;
}

- (IBAction)rtk_scan_listener:(id)sender
{
    if (m_context.m_mode == MODE_INIT) {
        // do action
        [self showQRScanner];
    }else{
        // don't listen
    }
}

/******* private functions *******/
-(void)configTimerHandler: (NSTimer *)sender
{    
    if (simpleConfig==nil || m_timer==nil) {
        //NSLog(@"Timer error in config vc");
        return;
    }

    unsigned int sc_mode = [simpleConfig rtk_sc_get_mode];
    //NSLog(@"sc_mode = %d", sc_mode);
    
    switch (sc_mode) {
        case MODE_INIT:
            if (![m_config_button.titleLabel.text isEqualToString:SC_UI_START_BUTTON]) {
                [m_config_button setTitle:SC_UI_START_BUTTON forState:UIControlStateNormal];
            }
            if ([self isWithIPNoName]) {
                [self showControlButton];
            }
            
            if(isCheckHomeAP){
                [self check_homeAP];
            }
            
            break;
        
        case MODE_CONFIG:
    
            break;
    
        case MODE_WAIT_FOR_IP:
            //NSLog(@"<APP> MODE_WAIT_FOR_IP\n");
            [m_config_button setTitle:SC_UI_START_BUTTON forState:UIControlStateNormal];
            
            int sc_pattern = [simpleConfig rtk_sc_get_pattern];
            
            if(sc_pattern==PATTERN_FOUR){
                
                if(isSoftAPmode){
                    
                    NSString *previous_homeAPSSID = [self getTargetAP_SSID];
                    NSString *current_SSID = @"";
                    current_SSID = [Util fetchCurrSSID];
                    
                    if(current_SSID!=nil){
                        if( [current_SSID length]>0 && ![current_SSID isEqualToString:softAP_SSID]){
                            
                            if(![current_SSID isEqualToString:previous_homeAPSSID]){
                                
                                NSLog(@"%d to check %@ => %@",__LINE__,current_SSID,previous_homeAPSSID);
                                /*if (waitingAlert) {
                                    [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
                                    waitingAlert = nil;
                                }*/
                                [self stopWaiting_progress];
                                
                                isSwithToWiFiSetting = YES;
                                
                                m_context.m_mode = MODE_WAIT_FOR_IP;
                                NSLog(@"!!! alertmsg_connectback !!!");
                                if(isAlertWiFiSetting==NO)
                                    [self alertmsg_connectback];
                                
                                isAlertWiFiSetting = YES;
                            }
                        }else{
                            NSLog(@"%d to check %@ vs %@ (%d)",__LINE__,current_SSID,previous_homeAPSSID,g_noBackTargetAP_count);
                            g_noBackTargetAP_count++;
                            if(g_noBackTargetAP_count>=20){
                                [self stopWaiting_progress];
                                
                                isSwithToWiFiSetting = YES;
                                
                                m_context.m_mode = MODE_WAIT_FOR_IP;
                                NSLog(@"!!! alertmsg_connectback !!!");
                                if(isAlertWiFiSetting==NO)
                                    [self alertmsg_connectback];
                                
                                isAlertWiFiSetting = YES;
                            }
                        }
                    }
  
                    
                }else{
                    if(isBackToWiFiSetting){
                        NSLog(@"(%d)isBackToWiFiSetting CHECK DEVICE :%lu",__LINE__,(unsigned long)[simpleConfig.config_list count]);
                        if([simpleConfig.config_list count]>=g_config_device_num){
                            NSLog(@"!!!!! FINISH !!!!!!");
                            m_context.m_mode = MODE_INIT;
                            [simpleConfig rtk_sc_config_stop];
                            
                            [self showConfigList];
                            
                            return;
                        }
                    }
                }
                
                
                
            }
            
            //[waitingAlert setTitle:[NSString stringWithFormat:@"Waiting for the device (%lu/%d)", (unsigned long)[simpleConfig.config_list count], g_config_device_num]];
            [waitingAlert setTitle:[NSString stringWithFormat:@"Waiting for the device"]];
            
            
            break;
            
        default:
            break;
    }
}

-(BOOL)isWithIPNoName
{
    BOOL ret = NO;
    struct dev_info dev;
    NSValue *dev_val;
    NSMutableArray *list = simpleConfig.config_list;
    
    if (list==nil || [list count]==0) {
        return NO;
    }
    
    //NSLog(@"current list count=%d", [list count]);
    dev_val = [list objectAtIndex:0];   // the earliest dev_info added
    [dev_val getValue:&dev];
    // check have ip
    //NSLog(@"ip of obj0: %x", dev.ip);
    ret |= (dev.ip==0)?NO:YES;
    
    if (ret==NO)
        return ret;
    
    // check have no name
    NSString *curr_name = [NSString stringWithUTF8String:(const char *)(dev.extra_info)];
    ret |= ([curr_name isEqualToString:@""] || [curr_name isEqualToString:@"\n"]);
    //NSLog(@"name of obj0: %@", curr_name);
    
    return ret;
}

-(void)alertmsg_connectback
{

    NSString *previous_SSID = [self getTargetAP_SSID];
    
    NSString *msg = [NSString stringWithFormat:@"Name: %@\n\nAfter the device connected, you need to back to this APP immediately.",previous_SSID ];
    
    UIAlertController *dialog_softAP = [UIAlertController alertControllerWithTitle:@"Please connect target AP \non WiFi setting to contiune.\n"
                                                                           message:msg
                                                                    preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        
        isBackToWiFiSetting = YES;
        isSwithToWiFiSetting = YES;
        isSoftAPmode = NO;
        m_context.m_mode = MODE_WAIT_FOR_IP;
        
        [NSTimer scheduledTimerWithTimeInterval:0.3 target:self selector:@selector(gotoSysWiFiSetting) userInfo:nil repeats:NO];
        
    }];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        isBackToWiFiSetting = NO;
        isSwithToWiFiSetting = NO;
        isSoftAPmode = NO;
        m_context.m_mode = MODE_INIT;
    }];
    
    [dialog_softAP addAction:cancelAction];
    [dialog_softAP addAction:okAction];
    
    [self presentViewController:dialog_softAP animated:YES completion:nil];
}

-(void)check_homeAP
{
    NSString *previous_homeAPSSID = [self getTargetAP_SSID];
    NSString *current_SSID = @"";
    current_SSID = [Util fetchCurrSSID];
    
    if(current_SSID!=nil){
        if( [current_SSID length]>0 && ![current_SSID isEqualToString:previous_homeAPSSID]){
            isCheckHomeAP = NO;
            if(![current_SSID isEqualToString:previous_homeAPSSID]){
                NSString *msg = [NSString stringWithFormat:@"Now home AP is %@ !\nDo you connect to %@ as home AP?",current_SSID, previous_homeAPSSID];
                
                UIAlertController *dialog_softAP = [UIAlertController alertControllerWithTitle:@"Warning\n"
                                                                                       message:msg
                                                                                preferredStyle:UIAlertControllerStyleAlert];
                UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"YES" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {

                    [NSTimer scheduledTimerWithTimeInterval:0.3 target:self selector:@selector(gotoSysWiFiSetting) userInfo:nil repeats:NO];
                    
                }];
                UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"NO" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                }];
                
                [dialog_softAP addAction:okAction];
                [dialog_softAP addAction:cancelAction];
                
                [self presentViewController:dialog_softAP animated:YES completion:nil];

            }
        }
    }
}

-(void)gotoSysWiFiSetting
{
    NSLog(@"!!! prefs:root=WIFI !!!");
    NSURL *url = [NSURL URLWithString:@"prefs:root=WIFI"];
    
    if([[UIApplication sharedApplication] canOpenURL:url]){
        [[UIApplication sharedApplication] openURL:url];
    }else{
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"App-Prefs:root=WIFI"]];
    }
    
}

-(void)showConfigList
{
    NSLog(@"!!!!! showConfigList !!!!!!");
    
    struct dev_info dev;
    NSValue *dev_val;
    
    isBackToWiFiSetting = NO;
    
    confirm_list = [[NSMutableArray alloc] initWithArray:simpleConfig.config_list copyItems:YES];
    //NSMutableArray *list = simpleConfig.config_list;

    [self stopWaiting_progress];

    for (int i=0; i<[confirm_list count]; i++) {
        dev_val = [confirm_list objectAtIndex:i];
        [dev_val getValue:&dev];
        
        NSLog(@"======<APP> Dump dev_info %d======",i);
        NSLog(@"MAC: %02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
        NSLog(@"Status: %d", dev.status);
        NSLog(@"Device type: %d", dev.dev_type);
        NSLog(@"IP:%x", dev.ip);
        NSLog(@"Name:%@", [NSString stringWithUTF8String:(const char *)(dev.extra_info)]);
    }
    
    UIAlertView* confirm_alert = [[UIAlertView alloc] initWithTitle:@"Configured Device"
                                                            message:@"uncheck device if any unwanted!"
                                                           delegate:self
                                                  cancelButtonTitle:@"Confirm"
                                                  otherButtonTitles: nil];
    
    confirm_alert.tag = tag_cfg_confirm;
    int table_height = 210;
    NSInteger focusValue = [confirm_list count];//[confirm_list count]%2==0 ? ((NSInteger)[confirm_list count]/2) : ((NSInteger)[confirm_list count]/2+1);
    NSIndexPath *focusIndex = [NSIndexPath indexPathForRow:focusValue inSection:0];
    if ([confirm_list count]>0) {
        table_height = 75 * (int)[confirm_list count];
        
        if(table_height>400)
            table_height = 400;
        if (table_height<90) {
            table_height = 90;
        }
        
    }
    
    UITableView* myView = [[UITableView alloc] initWithFrame:CGRectMake(10, 45, 264, table_height)
                                                       style:UITableViewStyleGrouped];
    myView.tag = tag_table_confirm;

    [myView selectRowAtIndexPath:focusIndex
                               animated:NO
                         scrollPosition:UITableViewScrollPositionNone];
    [myView setAllowsSelection:NO];
    myView.delegate = self;
    myView.dataSource = self;
    myView.backgroundColor = [UIColor clearColor];
    [confirm_alert setValue:myView forKey:@"accessoryView"];
    [confirm_alert show];

    m_context.m_mode = MODE_INIT;
}

-(void)showControlButton
{
    if (m_context.m_mode!=MODE_WAIT_FOR_IP && m_context.m_mode!=MODE_CONFIG)
        return;
    
    m_context.m_mode = MODE_INIT;
}

/* ------QRCode Related------*/
-(void)showQRScanner
{
    int maxScreen_height = [[UIScreen mainScreen] bounds].size.height;
    int maxScreen_width = [[UIScreen mainScreen] bounds].size.width;
    
    NSLog(@"screen: %d %d",maxScreen_width,maxScreen_height);
    
    upOrdown = NO;
    num = 0;
    if(m_qrcode_timer!=nil){
        [m_qrcode_timer invalidate];
        m_qrcode_timer = nil;
    }
    
    //init ZBar
    ZBarReaderViewController * reader = [ZBarReaderViewController new];
    //set Delegate
    reader.readerDelegate = self;
    
    reader.supportedOrientationsMask = ZBarOrientationMaskAll;
    reader.showsHelpOnFail = NO;
    reader.scanCrop = CGRectMake(0, 0, 1, 1);
    ZBarImageScanner * scanner = reader.scanner;
    [scanner setSymbology:ZBAR_I25
                   config:ZBAR_CFG_ENABLE
                       to:0];
    UIView * view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, maxScreen_width, maxScreen_height)];
    view.backgroundColor = [UIColor clearColor];
    reader.cameraOverlayView = view;
    
    //UILabel * label = [[UILabel alloc] initWithFrame:CGRectMake(20, 20, 280, 40)];
    UILabel * label = [[UILabel alloc] initWithFrame:CGRectMake(20, 20, maxScreen_width/2, 40)];
    label.text = @"Scan your QR code！";
    
    label.textColor = [UIColor whiteColor];
    label.textAlignment = 1;
    label.lineBreakMode = 0;
    label.numberOfLines = 2;
    label.backgroundColor = [UIColor clearColor];
    [view addSubview:label];
    
    UIImageView * image = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"pick_bg.png"]];
    //image.frame = CGRectMake(20, 80, 280, 280);
    image.frame = CGRectMake(20, 80, maxScreen_width-20*2, maxScreen_width-20*2);
    [view addSubview:image];
    
    _line = [[UIImageView alloc] initWithFrame:CGRectMake(20, 80, maxScreen_width-40*2, 1)];
    _line.image = [UIImage imageNamed:@"line.png"];
    [image addSubview:_line];
    
    //set: after 1.5 s
    m_qrcode_timer = [NSTimer scheduledTimerWithTimeInterval:.02 target:self selector:@selector(qrcode_animation) userInfo:nil repeats:YES];
    
    [self presentViewController:reader animated:YES completion:^{
    }];
    
    //[self presentViewController:reader animated:YES completion:nil];
    
    NSLog(@"<APP> scan button finished");
    //[text_pincode setText:m_pin_code];
}

-(void)qrcode_animation
{
    int maxScreen_width = [[UIScreen mainScreen] bounds].size.width;
    
    if (upOrdown == NO) {
        num ++;
        _line.frame = CGRectMake(20, 20+2*num, maxScreen_width-40*2, 1);
        if (2*num >= (maxScreen_width-30*2)) {
            upOrdown = YES;
        }
    }
    else {
        num --;
        _line.frame = CGRectMake(20, 20+2*num, maxScreen_width-40*2, 1);
        if (num <= 0) {
            upOrdown = NO;
        }
    }
}

/* Parse QRCode */
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    id<NSFastEnumeration> results = [info objectForKey:ZBarReaderControllerResults];
    ZBarSymbol *symbol = nil;
    for(symbol in results)
        break;
    
    NSLog(@"Got QRCode: %@", symbol.data);
    
    QR_PIN = symbol.data;
    
    //self.imageView.image = [info objectForKey:UIImagePickerControllerOriginalImage];
    [picker dismissViewControllerAnimated:YES completion:nil];
    
    [self rtk_start_listener:nil];
}

-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{

    //wait alert show
    if(alertView.tag == tag_timer){
    
        if(buttonIndex == 0) {//Cancel
            NSLog(@"<APP> wait alert show: Cancel");
            timerCount = 0;
            [self stopWaiting_progress];
            
            // stop sending profile
            if(isSwithToWiFiSetting)
                NSLog(@"SwithToWiFiSetting");
            else{
                m_context.m_mode = MODE_INIT;
                [simpleConfig rtk_sc_config_stop];
            }
            [m_config_button setTitle:SC_UI_START_BUTTON forState:UIControlStateNormal];
            
        }
    
    }else if(alertView.tag == tag_cfg_confirm){
        NSLog(@"<APP> Confirm!");
        
        struct dev_info dev;
        NSValue *dev_val;
        NSMutableArray *list = confirm_list;

        isTipSoftAP = NO;
        isSoftAPmode= NO;
        isBackToWiFiSetting = NO;
        isCheckHomeAP = YES;
        int i = 0;
        
        for (i=0; i<[list count]; i++) {
            
            dev_val = [list objectAtIndex:i];
            [dev_val getValue:&dev];
            
            NSLog(@"======Confirm dev_info %d======",i);
            NSLog(@"Name:%@", [NSString stringWithUTF8String:(const char *)(dev.extra_info)]);
            NSLog(@"IP:%x", dev.ip);
            NSLog(@"MAC: %02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
            NSLog(@"Status: %d", dev.status);
            NSLog(@"Device type: %d", dev.dev_type);
            
            //user unwanted the device => delete profile
            if (dev.status==BIT(2))//unconfirm status
            {
                unconfirmIndex = i;
                
                if ([self isDeviceConnected:dev.mac[0] m1:dev.mac[1] m2:dev.mac[2] m3:dev.mac[3] m4:dev.mac[4] m5:dev.mac[5] ]) {
                    NSLog(@"get device ip");
                    [self performSegueWithIdentifier:@"SegueController" sender:self];
                }else{
                    UIAlertView *wifialertView = [[UIAlertView alloc]
                                                  initWithTitle:NSLocalizedString(@"Error", @"AlertView")
                                                  message:NSLocalizedString(@"Check fail!!!!", @"AlertView")
                                                  delegate:self
                                                  cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                                  otherButtonTitles:nil];
                    [wifialertView show];
                }
                
            }
            
        }
        NSLog(@"<APP> Confirm! Done");
    }
}

//---------------------------------  UI table controllers  -------------------------------------
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    struct dev_info dev;
    static NSString *simpleTableIdentifier = @"Cell";
    
    NSString *devName = @"";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:simpleTableIdentifier];
    NSMutableArray *list = nil;
    NSValue *dev_val;
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:simpleTableIdentifier];
    }
    
    //NSMutableArray *list = simpleConfig.config_list;
    
    switch ([tableView tag]) {
        case tag_table_confirm:{
            
            list = confirm_list;
            
            //get the element(rowIndex) device
            dev_val = [list objectAtIndex:indexPath.row];
            [dev_val getValue:&dev];
            
            //cell.textLabel.text = [NSString stringWithFormat:@"Option %d", [indexPath row] + 1];
            if(strlen((const char *)(dev.extra_info))==0){
                char tmp[32] = {0};
                sprintf(tmp, "%02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
                devName = [NSString stringWithUTF8String:(const char *)tmp];
                
                
            }else{
                devName = [NSString stringWithUTF8String:(const char *)(dev.extra_info)];
            }
            
            NSLog(@"tag_table_confirm:%@",devName);
            
            cell.textLabel.text = devName;
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
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [simpleConfig.config_list count];
}

-(void)cfgConfirmSwitched:(id) sender
{
    int rowIndex = (int)[sender tag];
    UISwitch* switchControl = sender;

    struct dev_info selected_dev;
    NSValue *dev_val;
    NSMutableArray *list = confirm_list;

    //get the element(rowIndex) device
    dev_val = [list objectAtIndex:rowIndex];
    [dev_val getValue:&selected_dev];
    
    if (switchControl.on) {
        selected_dev.status = BIT(0); //connected status
    }else{
        selected_dev.status = BIT(2); //unconfirm status
    }
    
    //delete the element(rowIndex) device
    [confirm_list removeObjectAtIndex:rowIndex];
    
    
    //insert the new element(rowIndex) device
    NSValue *deviceItem = [NSValue value:&selected_dev withObjCType:@encode(struct dev_info)];
    [confirm_list insertObject:deviceItem atIndex: rowIndex];
    
    NSLog( @"switch(%d) %@ status:%d %@",rowIndex, switchControl.on ? @"ON" : @"OFF" , selected_dev.status,
          [NSString stringWithUTF8String:(const char *)(selected_dev.extra_info)]);
    
#if 0
    struct dev_info dev;
    for (int i=0; i<[list count]; i++) {
        dev_val = [list objectAtIndex:i];
        [dev_val getValue:&dev];
        
        NSLog(@"<APP> [after changed] Name:%@", [NSString stringWithUTF8String:(const char *)(dev.extra_info)]);
        NSLog(@"<APP> [after changed] IP:%x", dev.ip);
        NSLog(@"<APP> [after changed] MAC: %02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
        NSLog(@"<APP> [after changed] Device type: %d", dev.dev_type);
        NSLog(@"<APP> [after changed] Status: %d", dev.status);

    }
#endif
    
    
}
//---------------------------------  UI table controllers  -------------------------------------

- (BOOL)isDeviceConnected:(unsigned char)m0 m1:(unsigned char)m1 m2:(unsigned char)m2 m3:(unsigned char)m3 m4:(unsigned char)m4 m5:(unsigned char)m5
{
    struct dev_info dev;
    NSValue *dev_val;
    
    for (int i=0; i<[simpleConfig.config_list count]; i++) {
        dev_val = [simpleConfig.config_list objectAtIndex:i];
        [dev_val getValue:&dev];
        
        if( (dev.mac[0]==m0) &&
           (dev.mac[1]==m1) &&
           (dev.mac[2]==m2) &&
           (dev.mac[3]==m3) &&
           (dev.mac[4]==m4) &&
           (dev.mac[5]==m5)){
            
            if (dev.ip==0) {
                return NO;
            }else
                return YES;
            
        }

    }
    return NO;
}

- (void)alertTextFieldDidChange:(NSNotification *)notification{
    UIAlertController *alertController = (UIAlertController *)self.presentedViewController;
    if (alertController) {
        UITextField *login = alertController.textFields.firstObject;
        UIAlertAction *okAction = alertController.actions.firstObject;
        
        BOOL enable = login.text.length == 8;
        
        okAction.enabled = enable;
    }
}

- (void)checkSoftAPmode:(NSTimer *)arg
{
    int count=0;
    int maxTimeout = 90;
    NSString *nowSSID = [arg userInfo];
    //NSString *softAP_BSSID = @"";
    NSString *msg=@"";
    UIAlertController *dialog_softAP = nil;
    UIAlertAction *okAction = nil;
    UIAlertAction *CancelAction = nil;
    
    if(isSoftAPmode==NO)return;

    NSLog(@"!!! checkSoftAPmode !!!");
    
    do{
        sleep(1);
        
        softAP_SSID = [Util fetchCurrSSID];
        NSLog(@"%d)checkSoftAPmode isSoftAPmode:%@",count,softAP_SSID);
        
        if(![nowSSID isEqualToString:softAP_SSID] ){
            break;
        }
        
    }while(count++<maxTimeout);
    
    if(![simpleConfig rtk_sc_isMyDevice:softAP_SSID :(int)[softAP_SSID length]]){
        isSoftAPmode = NO;
        isTipSoftAP = NO;
        cfgProgressView.progress = 0;
        [self stopWaiting_progress];
        
        msg = [NSString stringWithFormat:@"The current AP is %@ now.\n This is not my device",softAP_SSID ];
        
        dialog_softAP = [UIAlertController alertControllerWithTitle:@""
                                                            message:msg
                                                     preferredStyle:UIAlertControllerStyleAlert];
        okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            
        }];
        
        [dialog_softAP addAction:okAction];
        [self presentViewController:dialog_softAP animated:YES completion:nil];
        
    }else{
        if(count<maxTimeout){
            
            msg = [NSString stringWithFormat:@"%@ connected successfully.\n Do you connected 2.4G WiFi?",softAP_SSID ];
            
            dialog_softAP = [UIAlertController alertControllerWithTitle:@""
                                                                message:msg
                                                         preferredStyle:UIAlertControllerStyleAlert];
            okAction = [UIAlertAction actionWithTitle:@"YES" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                [simpleConfig rtk_sc_setTargetAPis5GBand:FALSE];
                [self rtk_start_listener:nil];
            }];
            
            CancelAction = [UIAlertAction actionWithTitle:@"NO" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                [simpleConfig rtk_sc_setTargetAPis5GBand:TRUE];
                [self rtk_start_listener:nil];
            }];
            
            [dialog_softAP addAction:okAction];
            [dialog_softAP addAction:CancelAction];
            [self presentViewController:dialog_softAP animated:YES completion:nil];
            /*
            msg = [NSString stringWithFormat:@"%@ connected successfully",softAP_SSID ];
            
            dialog_softAP = [UIAlertController alertControllerWithTitle:@""
                                                                message:msg
                                                         preferredStyle:UIAlertControllerStyleAlert];
            okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                
                cfgProgressView.progress = 0.5;
                [self rtk_start_listener:nil];
            }];
             */
        }else{
            
            msg = [NSString stringWithFormat:@"The current AP is %@ now.\n This is not my device",softAP_SSID ];
            
            dialog_softAP = [UIAlertController alertControllerWithTitle:@"ERROR\n"
                                                                message:msg
                                                         preferredStyle:UIAlertControllerStyleAlert];
            okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                
                isSoftAPmode = NO;
                isTipSoftAP = NO;
                cfgProgressView.progress = 0;
                [self stopWaiting_progress];
                
            }];
            
            [dialog_softAP addAction:okAction];
            [self presentViewController:dialog_softAP animated:YES completion:nil];
        }
    }

    
    
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
        
        UIActivityIndicatorView *actview = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        actview.color=[UIColor blackColor];
        //actview.center=CGPointMake(www/2, hhh/2);
        [actview startAnimating];
        
        [waitingAlert setValue:actview forKey:@"accessoryView"];
        [waitingAlert show];
        
        if (timeout>0) {
            waitTimer = [NSTimer scheduledTimerWithTimeInterval: timeout
                                                         target: self
                                                       selector:@selector(stopWaiting)
                                                       userInfo: nil repeats:NO];
        }
        
        
    }
}

-(void)stopWaiting
{
    if(waitTimer){
        [waitTimer invalidate];
        waitTimer = nil;
    }
    
    if (waitingAlert) {
        [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
        waitingAlert = nil;
    }
}

- (void)startWaiting_progress:(NSString *) wait_title :(float)timeout
{
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
    
    int version = floor(NSFoundationVersionNumber);
    if(version >= 1200 ){ //iOS9
        [waitingAlert setValue:cfgProgressView forKey:@"accessoryView"];
    }

    [waitingAlert show];
    
    if (timeout>0) {
        
        if ([waitTimer isValid]) {
            [waitTimer invalidate];
            waitTimer = nil;
        }
        
        waitTimer = [NSTimer scheduledTimerWithTimeInterval:1.2 target:self selector:@selector(update_progress) userInfo:nil repeats:YES];
        //[[NSRunLoop currentRunLoop]addTimer:waitTimer forMode:NSDefaultRunLoopMode];
    }
}
- (void)stopWaiting_progress
{
    if(waitTimer){
        [waitTimer invalidate];
        waitTimer = nil;
    }
    
    if (waitingAlert) {
        [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
        waitingAlert = nil;
    }
    m_context.m_mode = MODE_INIT;
}

- (void)update_progress
{
    int i_persent = 0;
    
    if([simpleConfig.config_list count]>=g_config_device_num){
        NSLog(@"!!!!! FINISH !!!!!!");
        [self showConfigList];
        
        return;
    }

#if 1
    cfgProgressView.progress +=0.01;
#else
    double diffTime = NSDate.date.timeIntervalSince1970 - configTimerStart;
    cfgProgressView.progress = (diffTime/120);
#endif
    
    i_persent = 100 * cfgProgressView.progress;
    
    NSLog(@"Wait %d %%",i_persent);
    [waitingAlert setMessage:[NSString stringWithFormat:@"Please wait... %d %%", i_persent]];
    
    if(i_persent == timeout_cfg_step1){//when 50%
        
        if (waitingAlert) {
            [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
            waitingAlert = nil;
        }
        
        isTipSoftAP = YES;
        [self rtk_start_listener:nil];
        
    }else if(i_persent==timeout_cfg_step1+1){
        //[self rtk_start_listener:nil];
    }
    else if (i_persent == 100)//when 100%
    {

        [self stopWaiting_progress];
        
        cfgProgressView.progress = 0;
        
        if([simpleConfig.config_list count]>0){
            [self showConfigList];
            return;
        }else{
            UIAlertView *wifialertView = [[UIAlertView alloc]
                                          initWithTitle:NSLocalizedString(@"Configuration", @"AlertView")
                                          message:NSLocalizedString(@"Time Out", @"AlertView")
                                          delegate:self
                                          cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                          otherButtonTitles:/*NSLocalizedString(@"Open settings", @"AlertView"),*/ nil];
            [wifialertView show];
        }
    }
}

-(void)update_DeviceInfo
{
    NSLog(@"start_checkDeviceConfigured: %lu / %d",(unsigned long)[simpleConfig.config_list count],g_config_device_num);
    if([simpleConfig.config_list count]>=g_config_device_num){
        NSLog(@"!!!!! FINISH !!!!!!");
        [self showConfigList];
        
        return;
    }
}

-(NSString*)getTargetAP_SSID
{
    NSString *uuid = @"";
    
    uuid = [targetAP_DataFile objectForKey:@"TARGETAP"];
    return uuid;
}
-(void)setTargetAP_SSID : (NSString *)SSID
{
    [targetAP_DataFile setValue:SSID forKey:@"TARGETAP"];
    [targetAP_DataFile synchronize];
}

-(NSString*)getWiFipassword : (NSString *)APname
{
    int ap_num = 0;
    NSString *passwordAllData = @"";
    NSString *password = @"";
    
    if(APname==nil || [APname length]==0){
        NSLog(@"getWiFipassword: APname is emply");
        return @"";
    }
    
    passwordAllData = [APInfo_DataFile objectForKey:@"APINFO"];
    
    NSLog(@"passwordAllData:%@",passwordAllData);
    
    NSArray *APData = [passwordAllData componentsSeparatedByString:@";"];
    NSArray *APItemInfo = nil;
    
    ap_num = (int)[APData count]-1;
    for (int i = 0; i < ap_num; i++) {
        NSLog(@"<APP> get AP(%d/%d) :%@\n", i+1, ap_num, [APData objectAtIndex:i]);
        
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
        //NSLog(@"<APP> set AP-%d:%@\n", i+1, [APData objectAtIndex:i]);
        
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

-(void) isUsePinSwitched:(id) sender
{
    UISwitch* switchControl = sender;
    NSLog( @"isUsePinSwitched status:%@",switchControl.on ? @"ON" : @"OFF");
    
    if(switchControl.on){
        isPIN_on = YES;
        m_input_pin.hidden = NO;
        m_input_pin.placeholder = @"PIN Code";
    }else{
        isPIN_on = NO;
        m_input_pin.hidden = YES;
        m_input_pin.text = @"";
    }
    
}

@end
