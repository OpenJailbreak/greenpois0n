//
//  GPUSLDeviceManager.m
//  greenpois0n UserLand Device Manager
//
//  Created by Kevin Bradley on 6/7/11.
//  Copyright 2011 Chronic-Dev Team. All rights reserved.
//

#import "GPUSLDeviceManager.h"


	//string versions of the GP device defines- yeh im that lazy!

#define DEVICES_IPHONE2G     @"iPhone1,1"
#define DEVICES_IPHONE3G     @"iPhone1,2"
#define DEVICES_IPHONE3GS    @"iPhone2,1"
#define DEVICES_IPHONE4      @"iPhone3,1"
#define DEVICES_IPHONE42	 @"iPhone3,3"
#define DEVICES_IPOD1G       @"iPod1,1"
#define DEVICES_IPOD2G       @"iPod2,1"
#define DEVICES_IPOD3G       @"iPod3,1"
#define DEVICES_IPOD4G       @"iPod4,1"
#define DEVICES_IPAD1G       @"iPad1,1"
#define DEVICES_APPLETV2     @"AppleTV2,1"

#define IMAGE_IPHONE2G		@"com.apple.iphone"
#define IMAGE_IPHONE3G		@"com.apple.iphone-3g"
#define IMAGE_IPHONE3GS		@"com.apple.iphone-3g"
#define IMAGE_IPHONE4		@"com.apple.iphone-4-black" //10.6.7 only
#define IMAGE_IPHONE42		@"com.apple.iphone-4-black" //10.6.7 only
#define IMAGE_IPOD1G        @"com.apple.ipod-touch"
#define IMAGE_IPOD2G        @"com.apple.ipod-touch-2"
#define IMAGE_IPOD3G        @"com.apple.ipod-touch-2" //10.6.7 only
#define IMAGE_IPOD4G        @"com.apple.ipod-touch-4" //10.6.7 only
#define IMAGE_IPAD1G        @"com.apple.ipad"
#define IMAGE_APPLETV2      [[NSBundle mainBundle] pathForResource:@"atvIcon" ofType:@"icns"]

#define BUTTON_BUFFER 8




@implementation GPUSLDeviceManager

@synthesize deviceArray, chosenIndex, delegate;
@dynamic window, buttonView, continueButton;

- (void)setButtonProps:(NSButton *)theButton
{
	[theButton setBordered:FALSE];
	[theButton setBezelStyle:NSTexturedSquareBezelStyle];
	[theButton setImagePosition:NSImageAbove];
	[theButton setImageScaling:NSImageScaleProportionallyDown];
	[theButton setAutoresizesSubviews:YES];
	
}

void mylabelIfy(NSTextField *textField) { // renamed
	[textField setBezeled:NO];
	[textField setBordered:NO];
	[textField setDrawsBackground:NO];
	[textField setEditable:NO];
	[textField setSelectable:NO];
	[textField setAlignment:NSCenterTextAlignment];
}

- (void)closeWindow
{
	
		[window close];
}

- (id)initWithDevices:(NSArray *)devices
{
	
	self = [super init];
    if (self) {
		
		deviceArray = devices;
		window = [[NSWindow alloc] initWithContentRect:NSMakeRect(250, 312, 480, 270) styleMask:NSClosableWindowMask|NSTitledWindowMask|NSMiniaturizableWindowMask backing:NSBackingStoreBuffered defer:NO];
		NSView *deviceView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 420, 270)];
		buttonView = [[NSView alloc] initWithFrame:NSMakeRect(0, 48, 480, 193)];
		
	
		
		NSTextField *instructionField = [[NSTextField alloc] initWithFrame:NSMakeRect(63, 242, 326, 17)];
		[instructionField setStringValue:@"Please select you device below and press continue."];
		mylabelIfy(instructionField);
		
		[self drawButtons];

		 
		continueButton = [[NSButton alloc] initWithFrame:NSMakeRect(179, 15, 111, 25)];
		[continueButton setBezelStyle:NSRoundedBezelStyle];
		[continueButton setTitle:@"Continue"];
		[continueButton setTarget:self];
		[continueButton setAction:@selector(start)];
		[continueButton setKeyEquivalent:@"\r"];
		[continueButton setEnabled:FALSE];

		
		[deviceView addSubview:instructionField];
		[deviceView addSubview:buttonView];
		[deviceView addSubview:continueButton];
		
		[instructionField release];
		[continueButton release];
		
		[window setContentView:deviceView];
		[window makeKeyAndOrderFront:self];
		[window center];
		[window setTitle:@"Device Selection"];
		
    }
    return self;

}

- (void)setupButton:(NSButton *)deviceButton fromDictionary:(NSDictionary *)deviceDict
{
	[self setButtonProps:deviceButton];
	NSString *deviceName = [deviceDict valueForKey:@"DeviceName"];
	NSString *productType = [deviceDict valueForKey:@"ProductType"];
	NSString *productVersion = [deviceDict valueForKey:@"ProductVersion"];

	NSString *hardwareModel = [deviceDict valueForKey:@"HardwareModel"];
	NSString *buildVersion = [deviceDict valueForKey:@"BuildVersion"];
	NSString *hardwarePlatform = [[deviceDict valueForKey:@"HardwarePlatform"] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		//s5l8930x
	NSString *tooltip = [NSString stringWithFormat:@"Version: %@ Model: %@ Platform: %@",  buildVersion, hardwareModel, hardwarePlatform];
	
	[deviceButton setToolTip:tooltip];
	[deviceButton setImage:[GPUSLDeviceManager imageForDevice:productType]];
	[deviceButton setTitle:[NSString stringWithFormat:@"%@ (%@)", deviceName, productVersion]];
	
	[deviceButton setTarget:self];
	[deviceButton setAction:@selector(buttonChosen:)];
	
	
}

- (void)buttonChosen:(id)sender
{
	
	int buttonTag = [sender tag];
	[continueButton setEnabled:TRUE];
		//NSLog(@"deviceArray: %@", deviceArray);
		//NSDictionary *chosenOne = [deviceArray objectAtIndex:buttonTag];
	
		//NSLog(@"you have been chosen: %@", chosenOne);

	chosenIndex = buttonTag; 
	
}


- (void)drawButtons
{
	
		//kill old buttons
	
	NSArray *subviews = [[buttonView subviews] copy];
		//NSLog(@"subviews: %@", subviews);
	NSEnumerator *subviewEnum = [subviews objectEnumerator];
	id currentView = nil;
	while (currentView = [subviewEnum nextObject])
	{
		[currentView removeFromSuperview];
	}
	
	[subviews release];
	
	NSArray *theDevices = [deviceArray copy];
	
	int deviceCount = [theDevices count];
	
	/*
	 
	 this is a hideous mess, it is just a placeholder for better code that should be written for full scale refactor/re-write/overhaul
	 
	 
	 */
	
	NSButton *buttonOne = NULL;
	NSButton *buttonTwo = NULL;
	NSButton *buttonThree = NULL;
	id deviceOne = NULL;
	id deviceTwo = NULL;
	id deviceThree = NULL;
	
	
	switch (deviceCount) {
			
		case 1:
			
			deviceOne = [theDevices objectAtIndex:0];
			buttonOne = [[NSButton alloc] initWithFrame:NSMakeRect(165, 5, 148, 177)];
			
			[buttonOne setTag:0];
			
			[self setupButton:buttonOne fromDictionary:deviceOne];
			[buttonView addSubview:buttonOne];
			
			[buttonOne release];
			
			break;
		
		case 2: 
			/*
			 
			 480 - ((148*2 + 8)/2) = 88 x for button 1
			 88 + 148 + 8 = 
			 
			 */
			deviceOne = [theDevices objectAtIndex:0];
			deviceTwo = [theDevices objectAtIndex:1];
			
			buttonOne = [[NSButton alloc] initWithFrame:NSMakeRect(88, 5, 148, 177)];
		
			[self setupButton:buttonOne fromDictionary:deviceOne];
			
			buttonTwo = [[NSButton alloc] initWithFrame:NSMakeRect(244, 5, 148, 177)];
			[self setupButton:buttonTwo fromDictionary:deviceTwo];
			
			[buttonOne setTag:0];
			[buttonTwo setTag:1];
			
			[buttonView addSubview:buttonOne];
			[buttonView addSubview:buttonTwo];
			
			[buttonOne release];
			[buttonTwo release];

			break;
			
		case 3:
			
			deviceOne = [theDevices objectAtIndex:0];
			deviceTwo = [theDevices objectAtIndex:1];
			deviceThree = [theDevices objectAtIndex:2];
			
			buttonOne = [[NSButton alloc] initWithFrame:NSMakeRect(9, 5, 148, 177)];
			[self setupButton:buttonOne fromDictionary:deviceOne];
			
			buttonTwo = [[NSButton alloc] initWithFrame:NSMakeRect(165, 5, 148, 177)];
			[self setupButton:buttonTwo fromDictionary:deviceTwo];
			
			buttonThree = [[NSButton alloc] initWithFrame:NSMakeRect(321, 5, 148, 177)];
			[self setupButton:buttonThree fromDictionary:deviceThree];
			
			[buttonOne setTag:0];
			[buttonTwo setTag:1];
			[buttonThree setTag:2];
			
			
			[buttonView addSubview:buttonOne];
			[buttonView addSubview:buttonTwo];
			[buttonView addSubview:buttonThree];
			
			[buttonOne release];
			[buttonTwo release];
			[buttonThree release];
			
			break;
			
			
			break;
		
		default:
		
			break;
	}
	
		[deviceArray retain];
	
	
	
	
	
}

- (void)dealloc
{
	[buttonView release];
	[deviceArray release];
	[super dealloc];
}

- (void)start
{
	
	[delegate setChosen:chosenIndex];
		//nada
}

+ (NSImage *)imageForDevice:(NSString *)deviceType
{
	NSBundle *ctBundle = [NSBundle bundleWithPath:@"/System/Library/CoreServices/CoreTypes.bundle"];
	
	
	NSImage *outputImage = NULL;
	NSString *path;
	
	if ([deviceType isEqualToString:DEVICES_IPHONE2G])
	{
		path = [ctBundle pathForResource:IMAGE_IPHONE2G ofType:@"icns"];
		
			
	} else if ([deviceType isEqualToString:DEVICES_IPHONE3G])
	{
		path = [ctBundle pathForResource:IMAGE_IPHONE3G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPHONE3GS])
	{
		path = [ctBundle pathForResource:IMAGE_IPHONE3GS ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPHONE4])
	{
		path = [ctBundle pathForResource:IMAGE_IPHONE4 ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPHONE42])
	{
		path = [ctBundle pathForResource:IMAGE_IPHONE42 ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPOD1G])
	{
		path = [ctBundle pathForResource:IMAGE_IPOD1G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPOD2G])
	{
		path = [ctBundle pathForResource:IMAGE_IPOD2G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPOD3G])
	{
		path = [ctBundle pathForResource:IMAGE_IPOD3G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPOD4G])
	{
		path = [ctBundle pathForResource:IMAGE_IPOD4G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_IPAD1G])
	{
		path = [ctBundle pathForResource:IMAGE_IPAD1G ofType:@"icns"];
		
	} else if ([deviceType isEqualToString:DEVICES_APPLETV2])
	{
		path = IMAGE_APPLETV2;
		
	}
	
		//	NSLog(@"path: %@", path);
	
	if ([path length] < 0)
	{
		NSLog(@"device %@ unknown!", deviceType);
		return NULL;
	}
	
	
	outputImage = [[NSImage alloc] initWithContentsOfFile:path];
	
	return outputImage;
}


@end
