/*
 Copyright (c) 2010 Robert Chin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#import "RCSwitchOnOff.h"


@implementation RCSwitchOnOff

- (void)initCommon
{
	[super initCommon];
	onText = [UILabel new];
	onText.text = NSLocalizedString(@"ON", @"Switch localized string");
	onText.textColor = [UIColor whiteColor];
	//onText.font = [UIFont boldSystemFontOfSize:14];
	//onText.shadowColor = [UIColor colorWithRed:104.0/255 green:73.0/255 blue:54.0/255 alpha:1.0];
    //onText.shadowOffset = CGSizeMake(0, 1);
	
	offText = [UILabel new];
	offText.text = NSLocalizedString(@"OFF", @"Switch localized string");
	//offText.textColor = [UIColor colorWithRed:104.0/255 green:73.0/255 blue:54.0/255 alpha:1.0];
	//offText.font = [UIFont boldSystemFontOfSize:14];
	offText.shadowColor = [UIColor grayColor];
    //offText.shadowOffset = CGSizeMake(0, 1);
	
}


- (void)drawUnderlayersInRect:(CGRect)aRect withOffset:(float)offset inTrackWidth:(float)trackWidth
{
	{
		CGRect textRect = [self bounds];
        textRect.size = CGSizeMake(63, 23);
		textRect.origin.x += 14.0 + (offset - trackWidth);
        textRect.origin.y = textRect.origin.y;
		[onText drawTextInRect:textRect];	
	}
	
	{
		CGRect textRect = [self bounds];
        textRect.size = CGSizeMake(63, 23);
        textRect.origin.y = textRect.origin.y;
		textRect.origin.x += (offset + trackWidth) - 21.0;
		[offText drawTextInRect:textRect];
	}	
}

@end
