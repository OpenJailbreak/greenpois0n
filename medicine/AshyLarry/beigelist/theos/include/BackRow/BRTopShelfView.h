/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BackRow-Structs.h"
#import "BRControl.h"

@class BRMainMenuShelfErrorControl, BRImageControl, BRMediaShelfView;

@interface BRTopShelfView : BRControl {
@private
	int _state;	// 40 = 0x28
	BRMediaShelfView *_shelf;	// 44 = 0x2c
	BRMainMenuShelfErrorControl *_error;	// 48 = 0x30
	BRImageControl *_productImage;	// 52 = 0x34
}
@property(readonly, assign) BRMainMenuShelfErrorControl *error;	// G=0x31688791; @synthesize=_error
@property(readonly, assign) BRMediaShelfView *shelf;	// G=0x316887a1; @synthesize=_shelf
@property(assign) int state;	// G=0x316887b1; S=0x31688ba5; @synthesize=_state
- (id)init;	// 0x316889c9
- (void)dealloc;	// 0x3168895d
// declared property getter: - (id)error;	// 0x31688791
- (void)layoutSubcontrols;	// 0x31688af9
- (id)preferredActionForKey:(id)key;	// 0x316887c1
- (void)setAcceptsFocus:(BOOL)focus;	// 0x316888e5
// declared property setter: - (void)setState:(int)state;	// 0x31688ba5
// declared property getter: - (id)shelf;	// 0x316887a1
// declared property getter: - (int)state;	// 0x316887b1
@end

