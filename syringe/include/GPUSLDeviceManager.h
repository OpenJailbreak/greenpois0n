//
//  GPUSLDeviceManager.h
//  greenpois0n UserLand Device Manager
//
//  Created by Kevin Bradley on 6/7/11.
//  Copyright 2011 Chronic-Dev Team. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface GPUSLDeviceManager : NSObject {

	NSWindow	*window;
	NSView		*buttonView;
	NSArray		*deviceArray;
	int			chosenIndex;
	id	delegate;
	NSButton *continueButton;
}

@property (nonatomic, assign) id delegate;
@property (nonatomic, assign) NSWindow *window;
@property (nonatomic, retain) NSWindow *buttonView;
@property (nonatomic, retain) NSButton *continueButton;
@property (nonatomic, retain) NSArray *deviceArray;
@property (readwrite, assign) int chosenIndex;

+ (NSImage *)imageForDevice:(NSString *)deviceType;
- (void)drawButtons;
- (void)setupButton:(NSButton *)deviceButton fromDictionary:(NSDictionary *)deviceDict;

@end
