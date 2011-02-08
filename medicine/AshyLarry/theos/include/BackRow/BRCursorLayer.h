/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BackRow-Structs.h"
#import "BRMultiPartWidgetLayer.h"


__attribute__((visibility("hidden")))
@interface BRCursorLayer : BRMultiPartWidgetLayer {
@private
	float _radius;	// 88 = 0x58
	float _haloPercentage;	// 92 = 0x5c
}
@property(assign) float cornerRadius;	// G=0x3165babd; S=0x3165bad1; converted property
@property(assign) float haloPercentage;	// G=0x3165ba9d; S=0x3165baad; converted property
- (id)init;	// 0x3165bb69
// converted property getter: - (float)cornerRadius;	// 0x3165babd
// converted property getter: - (float)haloPercentage;	// 0x3165ba9d
- (id)imageMapForCornerRadius:(float)cornerRadius;	// 0x3165bacd
// converted property setter: - (void)setCornerRadius:(float)radius;	// 0x3165bad1
// converted property setter: - (void)setHaloPercentage:(float)percentage;	// 0x3165baad
@end

