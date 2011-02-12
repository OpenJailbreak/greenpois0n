/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BRControlHeightFactory.h"
#import "BRControlFactory.h"


__attribute__((visibility("hidden")))
@interface BRVideoChapterControlFactory : NSObject <BRControlFactory, BRControlHeightFactory> {
}
+ (id)factory;	// 0x315df629
- (id)controlForData:(id)data currentControl:(id)control requestedBy:(id)by;	// 0x315df665
- (float)heightForControlForData:(id)data requestedBy:(id)by;	// 0x315df7d9
@end
