//
//  RTKAppDelegate.m
//  SimpleConfig
//
//  Created by realtek on 6/16/14.
//  Copyright (c) 2014 Realtek. All rights reserved.
//

#import "RTKAppDelegate.h"
#import "RTKViewController.h"

@implementation RTKAppDelegate



@synthesize window = _window;
@synthesize viewController = _viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.

#if USE_ORIGIN_VIEW_METHOD
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.viewController = [[RTKViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil];
    } else {
        self.viewController = [[RTKViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil];
    }
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
#endif
    
    float sysVersion=[[UIDevice currentDevice]systemVersion].floatValue;
    if (sysVersion>=8.0) {
        UIUserNotificationType type=UIUserNotificationTypeBadge | UIUserNotificationTypeAlert | UIUserNotificationTypeSound;
        UIUserNotificationSettings *setting=[UIUserNotificationSettings settingsForTypes:type categories:nil];
        [[UIApplication sharedApplication]registerUserNotificationSettings:setting];
    }
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.

    
    NSLog(@"enter background!");
    
    __block UIBackgroundTaskIdentifier bgTask = [application beginBackgroundTaskWithExpirationHandler:^{
        [application endBackgroundTask:bgTask];
        bgTask = UIBackgroundTaskInvalid;
    }];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        
        // run something background
        while (YES) {
            [UIApplication sharedApplication].applicationIconBadgeNumber = 0;
            [NSThread sleepForTimeInterval:1.0f];
        }
        
        // when finish, call this method
        [application endBackgroundTask:bgTask];
        bgTask = UIBackgroundTaskInvalid;
    });

    [self.viewController.mySimpleConfig.pattern.udpSocket close];
    
    NSLog(@"enter background! Done");
    //exit(0);
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.

    NSError *err = nil;
    self.viewController.mySimpleConfig.pattern.udpSocket = [[AsyncUdpSocket alloc]initWithDelegate:self];
    [self.viewController.mySimpleConfig.pattern.udpSocket bindToPort:MCAST_PORT_NUM error:&err];
    [self.viewController.mySimpleConfig.pattern.udpSocket enableBroadcast:YES error:&err];

#if USE_AUTO_SSID
    NSDictionary *ifs = [self.viewController.mySimpleConfig.pattern fetchSSIDInfo];
    NSString *auto_ssid = [ifs objectForKey:@"SSID"];
    if (auto_ssid == nil) {
        auto_ssid = @"";
    }
    self.viewController.mySSID.text = auto_ssid;
#endif

}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
