//
//  DiscoverViewController.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/13.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <CommonCrypto/CommonDigest.h>
#import "DiscoverViewController.h"
#import "util.h"


@interface DiscoverViewController ()

@end

@implementation DiscoverViewController
@synthesize discover_table, dev_array;

#define timeout_discovery   4.0

#define tag_timer           10101

NSTimer *waitTimer;
UIAlertView *waitingAlert;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if([Util IsEnableWIFI])
    {
        m_isLoading = false;
        m_scanner = [[Scanner alloc] init];
        [m_scanner rtk_sc_build_scan_data:SC_USE_ENCRYPTION];
        dev_array = [m_scanner rtk_sc_get_scan_list];
        
        m_updateTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(timerHandler:) userInfo:nil repeats:YES];
        
        // auto refresh
        for (int i = 0; i<20; i++) {
            [m_scanner rtk_sc_start_scan];
        }
        
        [discover_table reloadData];
        
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

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

///*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.

    m_segue = segue;
}
//*/

- (void)dealloc {
#ifdef ARC
    [discover_table release];
    [m_scanner dealloc];
    [super dealloc];
#endif
}

- (void)viewDidDisappear:(BOOL)animated
{
    // Must release simpleConfig, so that its asyncUDPSocket delegate won't receive data
    [m_scanner rtk_sc_close_sock];
    [super viewDidDisappear:animated];
}

- (void)viewWillAppear:(BOOL)animated
{
    //NSLog(@"reopen socket");
    [m_scanner rtk_sc_reopen_sock];
    
    // auto refresh
    [dev_array removeAllObjects];
    for (int i = 0; i<20; i++) {
        [m_scanner rtk_sc_start_scan];
    }
    [discover_table reloadData];
}

- (IBAction)btn_info_click:(id)sender
{
    NSString *version = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"];
    NSString *verMsg = [NSString stringWithFormat:@"Version : %@", version];
    
    NSLog(@"Info_btnClick:%@",verMsg);
    
    //show about
    UIAlertView *aboutShow = [[UIAlertView alloc]
                              initWithTitle:NSLocalizedString(@"About Simple Config Wizard", @"AlertView")
                              message:NSLocalizedString(verMsg, @"AlertView")
                              delegate:self
                              cancelButtonTitle:NSLocalizedString(@"OK", @"AlertView")
                              otherButtonTitles:nil];
    [aboutShow show];
    
    
}

- (IBAction)btn_refresh_click:(id)sender
{
    [m_scanner rtk_sc_close_sock];
    [m_scanner rtk_sc_reopen_sock];
    
    [dev_array removeAllObjects];
    [m_scanner rtk_sc_start_scan];
    [discover_table reloadData];
    
    [self startWaiting:@"Searching Devices":timeout_discovery];
}


/* -------------TableView DataSouce and Delegate-------------- */
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (dev_array!=nil) {
        return [dev_array count];
    }
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    int index = (int)indexPath.row;
    struct dev_info dev;
    NSValue *dev_val;
    ClientListCell *cell = (ClientListCell *)[tableView dequeueReusableCellWithIdentifier:@"DiscoverCell"];
    
    if (dev_array == nil) {
        cell.cell_dev_name.text = @"Device Name";
        cell.cell_dev_mac.text = @"Device MAC";
        return cell;
    }
    
    switch (index) {
        default:
            dev_val = [dev_array objectAtIndex:index];
            [dev_val getValue:&dev];
            
            NSString *dev_name = [NSString stringWithCString:(const char *)dev.extra_info encoding:NSUTF8StringEncoding];
            if ([dev_name isEqualToString:@""] || [dev_name isEqualToString:@"\n"])
                dev_name = @"Untitled";
            
            NSString *dev_mac = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1], dev.mac[2], dev.mac[3], dev.mac[4], dev.mac[5]];
            
            [cell setContent:dev_name mac:dev_mac type:0];
            
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSLog(@"Select at row %ld", (long)indexPath.row);

    ClientViewController *client_vc = m_segue.destinationViewController;
    struct dev_info dev;
    NSValue *dev_val = [dev_array objectAtIndex:indexPath.row];
    [dev_val getValue:&dev];
    
    client_vc.sharedData = [[NSValue alloc] initWithBytes:&dev objCType:@encode(struct dev_info)];

    return;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    [dev_array removeAllObjects];
    //NSLog(@"start to scan, &m_scanner=%p", &m_scanner);
    [m_scanner rtk_sc_start_scan];
    [discover_table reloadData];
    //NSLog(@"scan done");
}

- (void)dumpDeviceInfo
{
    NSValue *dev_val;
    struct dev_info dev;
    int dev_total_num = (int)[dev_array count];
    int i = 0;
    // OR, check if this device info already exist
    for (i=0; i<dev_total_num; i++) {
        dev_val = [dev_array objectAtIndex:i];
        [dev_val getValue:&dev];
        NSLog(@"======dev_info %d======",i+1);
        NSLog(@"MAC: %02x:%02x:%02x:%02x:%02x:%02x", dev.mac[0], dev.mac[1],dev.mac[2],dev.mac[3],dev.mac[4],dev.mac[5]);
        NSLog(@"Status: %d", dev.status);
        NSLog(@"Device type: %d", dev.dev_type);
        NSLog(@"IP:%x", dev.ip);
        NSLog(@"Name:%@", [NSString stringWithCString:(const char *)(dev.extra_info) encoding:NSUTF8StringEncoding]);
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
    if(waitTimer){
        [waitTimer invalidate];
        waitTimer = nil;
    }
    
    if (waitingAlert) {
        [waitingAlert dismissWithClickedButtonIndex:0 animated:YES];
        waitingAlert = nil;
    }
}

//---------------------------------  subAction controllers  -------------------------------------
-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    
    //control: after key in pin code
    if(alertView.tag == tag_timer){
        
        if(buttonIndex == 0) {//Cancel
            NSLog(@"<APP> wait alert show: Cancel");
            [self stopWaiting];
        }
        
    }else{
        // Do something with responses from other alertViews
    }
}

/*-----------------Handler timer-------------------*/
-(void)timerHandler: (id)sender
{
    [discover_table reloadData];
}
@end
