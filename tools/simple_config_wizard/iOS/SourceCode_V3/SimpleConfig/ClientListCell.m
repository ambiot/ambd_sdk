//
//  ClientListCell.m
//  SimpleConfig
//
//  Created by Realsil on 14/11/17.
//  Copyright (c) 2014年 Realtek. All rights reserved.
//

#import "ClientListCell.h"

@implementation ClientListCell
@synthesize cell_dev_name, cell_dev_mac;

- (id)initWithContent: (NSString *)name mac:(NSString *)mac type:(unsigned int)type
{
    cell_dev_name.text = name;
    cell_dev_mac.text = mac;
    return [super initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"DiscoverCell"];
}

- (void)dealloc {
#ifdef ARC
    [cell_dev_name release];
    [cell_dev_mac release];
    [super dealloc];
#endif
}

- (void)setContent:(NSString *)name mac:(NSString *)mac type:(unsigned int)type
{
    cell_dev_name.text = name;
    cell_dev_mac.text = mac;
}
@end
