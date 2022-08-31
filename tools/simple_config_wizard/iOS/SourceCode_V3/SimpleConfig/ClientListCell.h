//
//  ClientListCell.h
//  SimpleConfig
//
//  Created by Realsil on 14/11/17.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ClientListCell : UITableViewCell
@property (retain, nonatomic) IBOutlet UILabel *cell_dev_name;
@property (retain, nonatomic) IBOutlet UILabel *cell_dev_mac;

- (id)initWithContent: (NSString *)name mac:(NSString *)mac type:(unsigned int)type;
- (void)setContent:(NSString *)name mac:(NSString *)mac type:(unsigned int)type;

@end
