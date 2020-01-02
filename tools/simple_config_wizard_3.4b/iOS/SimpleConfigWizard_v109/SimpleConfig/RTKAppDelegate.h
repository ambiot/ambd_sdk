//
//  RTKAppDelegate.h
//  SimpleConfig
//
//  Created by realtek on 6/16/14.
//  Copyright (c) 2014 Realtek. All rights reserved.
//

#import <UIKit/UIKit.h>

#define USE_ORIGIN_VIEW_METHOD 0

@class RTKViewController;

@interface RTKAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) RTKViewController *viewController;

@end
