/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BRSingleton.h"

@class NSMutableArray;

@interface BRApplianceManager : BRSingleton {
@private
	NSMutableArray *_applianceList;	// 4 = 0x4
}
+ (void)setSingleton:(id)singleton;	// 0x3159234d
+ (void)showMainMenu;	// 0x31626ccd
+ (id)singleton;	// 0x31592341
- (id)init;	// 0x31626639
- (id)_applianceForInfo:(id)info;	// 0x3159732d
- (id)_controllerForApplianceKey:(id)applianceKey identifier:(id)identifier args:(id)args;	// 0x31626815
- (BOOL)_handlePlay:(id)play userInfo:(id)info;	// 0x316266ad
- (void)_loadApplianceAtPath:(id)path;	// 0x315924f1
- (void)_loadAppliancesInFolder:(id)folder;	// 0x315923b1
- (void)_unloadCurrentAppliances;	// 0x31626685
- (id)applianceForInfo:(id)info;	// 0x31597319
- (id)applianceInfoList;	// 0x315966ad
- (id)controllerForApplianceInfo:(id)applianceInfo identifier:(id)identifier args:(id)args;	// 0x31626c35
- (id)controllerForApplianceKey:(id)applianceKey identifier:(id)identifier args:(id)args;	// 0x31626d1d
- (id)controllerForContentAlias:(id)contentAlias;	// 0x31626ba5
- (void)dealloc;	// 0x31626c5d
- (BOOL)handleObjectSelection:(id)selection userInfo:(id)info;	// 0x31626b21
- (BOOL)handlePlay:(id)play userInfo:(id)info;	// 0x31626a9d
- (void)loadAppliances;	// 0x31592359
@end

