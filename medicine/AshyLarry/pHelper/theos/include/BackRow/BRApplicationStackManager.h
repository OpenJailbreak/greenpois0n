/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BRSingleton.h"

@class BRWindow, BRControllerStack;

@interface BRApplicationStackManager : BRSingleton {
@private
	BRControllerStack *_stack;	// 4 = 0x4
	BRWindow *_window;	// 8 = 0x8
}
@property(readonly, retain) BRControllerStack *stack;	// G=0x3158d8a5; converted property
@property(readonly, retain) BRWindow *window;	// G=0x31626ead; converted property
+ (void)setSingleton:(id)singleton;	// 0x3158d899
+ (id)singleton;	// 0x3158d445
- (id)init;	// 0x3158d451
- (void)show;	// 0x3158d8b5
// converted property getter: - (id)stack;	// 0x3158d8a5
// converted property getter: - (id)window;	// 0x31626ead
@end

