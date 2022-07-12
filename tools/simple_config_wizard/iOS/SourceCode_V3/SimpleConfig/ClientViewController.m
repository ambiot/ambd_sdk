//
//  ClientViewController.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/13.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import "ClientViewController.h"

@interface ClientViewController ()

@end

#define tag_timer           10101

NSTimer *waitTimer;
UIAlertView          *waitingAlert;

@implementation ClientViewController
@synthesize sharedData;
@synthesize pin_label, pinLabel, qrcode_btn, m_qrscan_line;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    m_controller = [[Controller alloc] init];
    
    if (sharedData!=nil) {
        struct dev_info dev;
        [sharedData getValue:&dev];
        
        NSLog(@"dev->ip=%x",dev.ip);
        NSLog(@"dev->mac=%02x:%02x:%02x:%02x:%02x:%02x",dev.mac[0],dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
        NSLog(@"dev->require_pin=%@", (dev.require_pin==1)?@"YES":@"NO");
        NSLog(@"dev->type=%u", dev.dev_type);
        
        if(dev.dev_type==16889){
            _connectNewAP_btn.enabled = YES;
            [_connectNewAP_btn setHidden:false];
        }else{
            _connectNewAP_btn.enabled = NO;
            [_connectNewAP_btn setHidden:true];
        }
        
        if(0x0a==dev.extra_info[0])
            [_name_label setText:@"Untitled"];
        else
            [_name_label setText:[NSString stringWithUTF8String:(const char *)dev.extra_info]];
        _ip_label.text = [NSString stringWithFormat:@"%d.%d.%d.%d", 0xFF&(dev.ip>>24), 0xFF&(dev.ip>>16), 0xFF&(dev.ip>>8), 0xFF&dev.ip];
        _mac_label.text = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1], dev.mac[2], dev.mac[3], dev.mac[4], dev.mac[5]];
        
        if(!dev.require_pin){
            [pinLabel setHidden:true];
            [pin_label setHidden:true];
            [qrcode_btn setHidden:true];
        }else{
            [pinLabel setHidden:false];
            [pin_label setHidden:false];
            [qrcode_btn setHidden:false];
            pin_label.text = @"";
            [pin_label addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];
        }
    }
    
    pin_label.text = @"";
    [pin_label addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [_name_label addTarget:self action:@selector(textFieldDoneEditing:) forControlEvents:UIControlEventEditingDidEndOnExit];
    m_timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(timerHandler:) userInfo:nil repeats:YES];
    m_mode = MODE_INIT;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)dealloc {
#ifdef ARC
    [_name_label release];
    [_ip_label release];
    [_mac_label release];
    [_delete_btn release];
    [_rename_btn release];
    [_connectNewAP_btn release];
    [pin_label release];
    [_name_label release];
    [pin_label release];
    [pinLabel release];
    [qrcode_btn release];
    [super dealloc];
#endif
}

- (void)startWaiting:(NSString *) wait_title :(NSString *) wait_msg :(float)timeout
{
    
    //  Purchasing Spinner.
    waitingAlert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(wait_title,@"")
                                              message:wait_msg
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
    
    
    //}else{
    //    NSLog(@"no startWaiting");
    
    //}
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

/* Hide the keyboard when pushing "enter" */
- (BOOL)textFieldDoneEditing:(UITextField *)sender
{
    NSLog(@"textFieldDoneEditing, Sender is %@", sender);
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

- (void)viewDidDisappear:(BOOL)animated
{
    // Must release simpleConfig, so that its asyncUDPSocket delegate won't receive data
    NSLog(@"close control socket");
    [m_controller rtk_sc_close_sock];
    [super viewDidDisappear:animated];
}

- (void)viewWillAppear:(BOOL)animated
{
    NSLog(@"reopen control socket");
    [m_controller rtk_sc_reopen_sock];
}

/* Button Delegate */
-(IBAction)delete_profile:(id)sender
{
    // generate data
    NSString *pin = pin_label.text;
    unsigned int ip = [m_controller rtk_sc_convert_host_to_ip:_ip_label.text];
    
    if (pin_label.isHidden==false && [pin isEqualToString:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_ERROR message:SC_UI_ALERT_INPUT_PIN delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
        [alert show];
        return;
    }else if(pin_label.isHidden==true)
        pin = PATTERN_DEF_PIN;

    NSLog(@"pin=%@, ip=%x", pin, ip);
    [m_controller rtk_sc_gen_control_data:RTK_SC_CONTROL_DELETE pin:pin name:nil];
    m_mode = MODE_CONTROL;
    
    // send data
    for (int i=0; i<30; i++) {
        NSLog(@"send delete profile data %d", i);
        if(i%3==0)
            usleep(200000);
        [m_controller rtk_sc_send_control_data:ip];
    }
}

-(IBAction)rename_device:(id)sender
{
    // generate data
    NSString *pin = pin_label.text;
    NSString *name = _name_label.text;
    unsigned int ip = [m_controller rtk_sc_convert_host_to_ip:_ip_label.text];
    
    if (pin_label.isHidden==false && [pin isEqualToString:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_ERROR message:SC_UI_ALERT_INPUT_PIN delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
        [alert show];
        return;
    }else if(pin_label.isHidden==true)
        pin = PATTERN_DEF_PIN;
    
    NSLog(@"pin=%@, ip=%x", pin, ip);
    
    if([name isEqualToString:@""])
        name = @"Untitled";	
    [m_controller rtk_sc_gen_control_data:RTK_SC_CONTROL_RENAME pin:pin name:name];
    m_mode = MODE_CONTROL;
    
    // send data
    for (int i=0; i<3; i++) {
        NSLog(@"send rename profile data %d", i);
        [m_controller rtk_sc_send_control_data:ip];
        usleep(50000);
    }
}

-(IBAction)switch_to_other_AP:(id)sender
{
    NSString *msg = @"";
    
    msg = [NSString stringWithFormat:@"New AP Configuration"];
    
    UIAlertController *alertController_newAP = [UIAlertController alertControllerWithTitle:@""//@"Configure New Device"
                                                                                 message:msg
                                                                          preferredStyle:UIAlertControllerStyleAlert];
    [alertController_newAP addTextFieldWithConfigurationHandler:^(UITextField *textField) {
        //NSString *storedPassword = [self getWiFipassword:targetAP_SSID];
        
        textField.placeholder = @"SSID";

    }];
    [alertController_newAP addTextFieldWithConfigurationHandler:^(UITextField *textField) {
        //NSString *storedPassword = [self getWiFipassword:targetAP_SSID];
        
        textField.placeholder = @"Password";
        
        textField.secureTextEntry = YES;
    }];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"Config" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        
        // generate data
        NSString *pin = pin_label.text;
        unsigned int ip = [m_controller rtk_sc_convert_host_to_ip:_ip_label.text];
        
        BOOL isNotASCII = NO;
        UITextField *ap_ssid = alertController_newAP.textFields.firstObject;
        NSString *targetAP_SSID = ap_ssid.text;
        UITextField *ap_password = alertController_newAP.textFields.lastObject;
        NSString *targetAP_PWD = ap_password.text;
        
        for (NSUInteger c = 0; c < targetAP_SSID.length; c++) {
            unichar char_c = [targetAP_SSID characterAtIndex:c];
            //NSLog(@"char = %x", (int)char_c); // Log the hex value of the Unicode character
            if( ((int)char_c > 0x7f) || ((int)char_c < 0x20)){
                isNotASCII = YES;
                break;
            }
        }
        
        NSLog(@"new AP configuration:%@/%@",targetAP_SSID,targetAP_PWD);
        
        if(isNotASCII){
            UIAlertView *aboutShow = [[UIAlertView alloc]
                                      initWithTitle:NSLocalizedString(@"Error", @"AlertView")
                                      message:NSLocalizedString(@"Please check the SSID!", @"AlertView")
                                      delegate:self
                                      cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                                      otherButtonTitles:nil];
            [aboutShow show];
            return;
        }
        
        if (pin_label.isHidden==false && [pin isEqualToString:@""]) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_ERROR message:SC_UI_ALERT_INPUT_PIN delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
            [alert show];
            return;
        }else if(pin_label.isHidden==true)
            pin = PATTERN_DEF_PIN;
        
        [self stopWaiting];
        [self startWaiting:@"Connecting":@"Please wait...":0];
        
        [m_controller rtk_sc_gen_control_new_AP_data:pin ssid:targetAP_SSID password:targetAP_PWD];
        
        m_mode = MODE_CONTROL;
        
        for (int i=0; i<6; i++) {
            [m_controller rtk_sc_send_control_data:ip];
        }
        
    }];
    
    [alertController_newAP addAction:cancelAction];
    [alertController_newAP addAction:okAction];
    
    [self presentViewController:alertController_newAP animated:YES completion:nil];
}

-(IBAction)scan_QRCode:(id)sender
{
    [self showQRScanner];
}

/* Timer Delegate */
-(void)timerHandler: (NSTimer *)sender
{
    unsigned int controller_mode = [m_controller rtk_sc_get_mode];
    switch (controller_mode) {
        case MODE_INIT:
            if (m_mode == MODE_CONTROL) {
                int result = [m_controller rtk_sc_get_control_result];
                if (result==RTK_SUCCEED) {
                    [self stopWaiting];
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_INFO message:SC_UI_ALERT_CONTROL_DONE delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
                    [alert show];
                }else{
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:SC_UI_ALERT_TITLE_ERROR message:SC_UI_ALERT_CONTROL_FAILED delegate:self cancelButtonTitle:SC_UI_ALERT_OK otherButtonTitles:nil, nil];
                    [alert show];
                }
                m_mode = MODE_INIT;
            }
            break;
           
        default:
            break;
    }
}

/* ------QRCode Related------*/
-(void)showQRScanner
{
    int maxScreen_height = [[UIScreen mainScreen] bounds].size.height;
    int maxScreen_width = [[UIScreen mainScreen] bounds].size.width;
    
    NSLog(@"screen: %d %d",maxScreen_width,maxScreen_height);
    
    m_upOrdown = NO;
    m_num = 0;

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
    
    m_qrscan_line = [[UIImageView alloc] initWithFrame:CGRectMake(20, 80, maxScreen_width-40*2, 1)];
    m_qrscan_line.image = [UIImage imageNamed:@"line.png"];
    [image addSubview:m_qrscan_line];
    
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
    
    if (m_upOrdown == NO) {
        m_num ++;
        m_qrscan_line.frame = CGRectMake(20, 20+2*m_num, maxScreen_width-40*2, 1);
        if (2*m_num >= (maxScreen_width-30*2)) {
            m_upOrdown = YES;
        }
    }
    else {
        m_num --;
        m_qrscan_line.frame = CGRectMake(20, 20+2*m_num, maxScreen_width-40*2, 1);
        if (m_num <= 0) {
            m_upOrdown = NO;
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
    [pin_label setText:symbol.data];
    //self.imageView.image = [info objectForKey:UIImagePickerControllerOriginalImage];
    [picker dismissViewControllerAnimated:YES completion:nil];
}

@end
