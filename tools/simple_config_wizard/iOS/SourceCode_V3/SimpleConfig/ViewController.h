//
//  ViewController.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/6.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SimpleConfig.h"
#import "String.h"
#import "ConfigViewController.h"

@interface ViewController : UIViewController
{
@private
    SC_CONTEXT  m_context;
}

@property (strong, nonatomic) ConfigViewController *m_configVC;

@end

