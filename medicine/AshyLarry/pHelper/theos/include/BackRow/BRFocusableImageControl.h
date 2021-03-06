/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BRImageControl.h"

@class BRImage;

@interface BRFocusableImageControl : BRImageControl {
@private
	BRImage *_focusedImage;	// 64 = 0x40
	BRImage *_unfocusedImage;	// 68 = 0x44
	BRImage *_disabledImage;	// 72 = 0x48
	BOOL _dimsWhenDisabled;	// 76 = 0x4c
	BOOL _disabled;	// 77 = 0x4d
}
@property(assign) BOOL dimsWhenDisabled;	// G=0x315e6d39; S=0x315e6de5; converted property
@property(assign) BOOL disabled;	// G=0x315e6d19; S=0x315e6e55; converted property
@property(retain) BRImage *disabledImage;	// G=0x315e6d29; S=0x315e6e0d; converted property
@property(retain) BRImage *focusedImage;	// G=0x315b9665; S=0x315b8ce5; converted property
@property(retain) BRImage *unfocusedImage;	// G=0x315b8d2d; S=0x315b8d61; converted property
- (void)_updateDim;	// 0x315e6f0d
- (void)_updateImage;	// 0x315e6d49
- (void)controlWasFocused;	// 0x315b9611
- (void)controlWasUnfocused;	// 0x315b9675
- (void)dealloc;	// 0x315b95a5
// converted property getter: - (BOOL)dimsWhenDisabled;	// 0x315e6d39
// converted property getter: - (BOOL)disabled;	// 0x315e6d19
// converted property getter: - (id)disabledImage;	// 0x315e6d29
// converted property getter: - (id)focusedImage;	// 0x315b9665
- (id)preferredActionForKey:(id)key;	// 0x315e6e85
// converted property setter: - (void)setDimsWhenDisabled:(BOOL)disabled;	// 0x315e6de5
// converted property setter: - (void)setDisabled:(BOOL)disabled;	// 0x315e6e55
// converted property setter: - (void)setDisabledImage:(id)image;	// 0x315e6e0d
// converted property setter: - (void)setFocusedImage:(id)image;	// 0x315b8ce5
// converted property setter: - (void)setUnfocusedImage:(id)image;	// 0x315b8d61
// converted property getter: - (id)unfocusedImage;	// 0x315b8d2d
@end

