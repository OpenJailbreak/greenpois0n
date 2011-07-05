//
//  main.m
//  greenpois0n
//
//  Created by Ari Weinstein on 7/02/09.
//	Modified for AppleTV goodness by |bile| on 2/12/11
//  Copyright Squish Software 2009. All rights reserved.
//

#include <libpois0n.h>
#include <libdioxin.h>
#include <GPUSLDeviceManager.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

#define OPAQUE_HEXCOLOR(c) [NSColor colorWithDeviceRed:((c>>16)&0xFF)/255.0 \
green:((c>>8)&0xFF)/255.0 \
blue:(c&0xFF)/255.0 \
alpha:1.0]

NSButton *jailbreakButton;
NSButton *resetButton;
NSProgressIndicator *progressIndicator;
NSTextField *secondsLabel;
NSTextField *secondsTextLabel;
NSTextField *firstLabel;
NSTextField *secondLabel;
NSTextField *thirdLabel;
NSTextField *fourthLabel;
NSImageView *greenpois0nLogo;
NSBox *mainBox;
GPUSLDeviceManager *deviceManager;
NSArray* attachedDevices;

void buildMenus(NSString *appName);
void labelIfy(NSTextField *textField);
BOOL reset = false;
BOOL stop = false;
BOOL jailbreaking = false;
BOOL complete = false;
BOOL appletv = false;

void update_progress(double progress) {
	if(progressIndicator) {
		if (progress < 99.0f) {
		    [progressIndicator setIndeterminate:NO];
		    [progressIndicator startAnimation:nil];
        } else {
            [progressIndicator setIndeterminate:YES];
            [progressIndicator startAnimation:nil];
        }
        
		[progressIndicator setDoubleValue:progress];
	}
}

@interface Callback : NSObject {

	NSWindow *window;
	NSDictionary *chosenOne;
}

- (NSWindow *)window;
- (void)setWindow:(NSWindow *)value;

	
@end
@implementation Callback

- (NSWindow *)window {
    return [[window retain] autorelease];
}

- (void)setWindow:(NSWindow *)value {
	window = value;
}



- (void)reset {
	reset = true;
	
	[secondsLabel setStringValue:@"5"];
	[firstLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
	[secondLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
}
- (void)start {
    if (complete) [[NSApplication sharedApplication] terminate:nil];
    
	[resetButton setEnabled:YES];
	[jailbreakButton setEnabled:NO];
	[jailbreakButton setTitle:@"Waiting for DFU"];

	[mainBox addSubview:secondsLabel];
	[mainBox addSubview:secondsTextLabel];
	[[greenpois0nLogo animator] setAlphaValue:0.0];
	[[secondsLabel animator] setAlphaValue:1.0];
	[[secondsTextLabel animator] setAlphaValue:1.0];
	
	[secondsLabel setStringValue:@"5"];
	if (appletv == true)
		[secondsLabel setStringValue:@"7"];
	[firstLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
	[self performSelector:@selector(stage2) withObject:nil afterDelay:1.0];
	[NSThread detachNewThreadSelector:@selector(check:) toTarget:self withObject:chosenOne];
}
- (void)stage2 {
	if (reset) {
		reset = false;
		[self start];
		return;
	}
	
	if (jailbreaking) return;
	
	int current = [[secondsLabel stringValue] intValue];
	if (current != 1) {
		[secondsLabel setStringValue:[NSString stringWithFormat:@"%d", current-1]];
		[self performSelector:@selector(stage2) withObject:nil afterDelay:1.0];
	} else {
		[secondsLabel setStringValue:@"3"];
		if (appletv == true)
			[secondsLabel setStringValue:@"2"]; //used to be 5
		[firstLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
		[secondLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
		[self performSelector:@selector(stage3) withObject:nil afterDelay:1.0];
	}
}
- (void)stage3 {
	if (reset) {
		reset = false;
		[self start];
		return;
	}
	
	if (jailbreaking) return;
	
	int current = [[secondsLabel stringValue] intValue];
	if (current != 1) {
		[secondsLabel setStringValue:[NSString stringWithFormat:@"%d", current-1]];
		[self performSelector:@selector(stage3) withObject:nil afterDelay:1.0];
	} else {
		[secondsLabel setStringValue:@"10"];
		if (appletv == true)
			[secondsLabel setStringValue:@"7"];
		[secondLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
		[thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
		[self performSelector:@selector(stage4) withObject:nil afterDelay:1.0];
	}
}
- (void)stage4 {
	if (reset) {
		reset = false;
		[self start];
		return;
	}
	
	if (jailbreaking) return;
	
	int current = [[secondsLabel stringValue] intValue];
	if (current != 1) {
		[secondsLabel setStringValue:[NSString stringWithFormat:@"%d", current-1]];
		[self performSelector:@selector(stage4) withObject:nil afterDelay:1.0];
	} else {
		[secondsLabel setStringValue:@"10"];
		if (appletv == true)
			[secondsLabel setStringValue:@"5"];
		[thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
		[fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
		[self performSelector:@selector(stage5) withObject:nil afterDelay:1.0];
	}
}

- (void)atvRamdiskTimer
{
	[jailbreakButton setEnabled:NO];
	[[greenpois0nLogo animator] setAlphaValue:0.0];
    [[secondsLabel animator] setAlphaValue:1.0];
    [[secondsTextLabel animator] setAlphaValue:1.0];
	
	int current = [[secondsLabel stringValue] intValue];
	if (current != 1) {
		[secondsLabel setStringValue:[NSString stringWithFormat:@"%d", current-1]];
		[self performSelector:@selector(atvRamdiskTimer) withObject:nil afterDelay:1.0];
	} else {
		[jailbreakButton setEnabled:YES];
		complete = true;
		jailbreaking = false;
		stop = true;
		[[greenpois0nLogo animator] setAlphaValue:1.0];
		[[secondsLabel animator] setAlphaValue:0.0];
		[[secondsTextLabel animator] setAlphaValue:0.0];
		[jailbreakButton setTitle:@"Complete!"];
	}
}

- (void)showYourself
{
	[window makeKeyAndOrderFront:nil];
	[window center];
}

- (BOOL)isCompat:(NSDictionary *)theChosenOne
{
	NSString *urlString = [chosenOne valueForKey:@"URL"];
	if ([urlString isEqualToString:@"NOT_SUPPORTED" ])
	{
		NSLog(@"survey says.... NOPE");
		return FALSE;
	}
	
	return TRUE;
}

- (void)setChosen:(int)chosenIndex
{
		//NSLog(@"SETTING CHOSEN ONE!!");
		chosenOne = [attachedDevices objectAtIndex:chosenIndex];
	
		//NSLog(@"chosenOne: %@", chosenOne);
	
	[chosenOne retain];
	[self newAppleTVCheck];
		//NSLog(@"[deviceManager window]: %@", [deviceManager window]);
	
	if (![self isCompat:chosenOne])
	{
		[self showIncompatibleAlert:chosenOne];
		return;
	}
	
	[deviceManager closeWindow];

	[window makeKeyAndOrderFront:nil];
	[window center];
		//	[[window animator] setAlphaValue:1.0];
}

- (void)check:(NSDictionary *)deviceDict {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
	char *url = NULL;
	if (chosenOne != nil)
	{
			//NSLog(@"chosen one is not null: %@", chosenOne);
			//NSNumber *ecidNumber = [chosenOne valueForKey:@"UniqueChipID"];
		NSString *urlString = [chosenOne valueForKey:@"URL"];
		
			//uint64_t ecidNum = [ecidNumber unsignedLongLongValue];
		url = [urlString UTF8String];
			//fprintf(stderr, "ecidNum: %llu\n", ecidNum);
	}
	
	
    if (stop) return;
    
    pois0n_init();
	pois0n_set_callback(&update_progress, NULL);
	
    while (stop == false) {
        if (pois0n_is_ready() != -1 && pois0n_is_compatible_using_url(url) != -1) {
            jailbreaking = true;
            stop = true;
            
            [fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
            [secondsLabel setStringValue:@"0"];
            
            [progressIndicator setIndeterminate:YES];
            [progressIndicator startAnimation:nil];
            [jailbreakButton setTitle:@"Jailbreaking..."];
            
            [self performSelectorOnMainThread:@selector(cancel) withObject:nil waitUntilDone:NO];
            
            int result = pois0n_inject(NULL);
            [progressIndicator setIndeterminate:YES];
            [progressIndicator stopAnimation:nil];
            
            if (result == 0) {
				
				
				if (appletv == true)
				{
					[[greenpois0nLogo animator] setAlphaValue:0.0];
					[[secondsLabel animator] setAlphaValue:1.0];
					[[secondsTextLabel animator] setAlphaValue:1.0];
					[secondsLabel setStringValue:@"45"];
					 [jailbreakButton setTitle:@"Running ramdisk"];
						[self performSelectorOnMainThread:@selector(atvRamdiskTimer) withObject:nil waitUntilDone:NO];
						//[self atvRamdiskTimer];
				} else {
					complete = true;
					jailbreaking = false;
					stop = true;
					   [jailbreakButton setTitle:@"Complete!"];
					
				}
				
             
               
				
            } else {
                complete = false;
                stop = false;
                [jailbreakButton setTitle:@"Failed :("];
            }
                
            jailbreaking = false;
            [jailbreakButton setEnabled:YES];
        }
    }
    
    pois0n_exit();
    [pool release];
}
- (void)cancel {
    [resetButton setEnabled:NO];
    [[greenpois0nLogo animator] setAlphaValue:1.0];
    [[secondsLabel animator] setAlphaValue:0.0];
    [[secondsTextLabel animator] setAlphaValue:0.0];
    [[firstLabel animator] setEnabled:NO];
    [[secondLabel animator] setEnabled:NO];
    [[thirdLabel animator] setEnabled:NO];
    [[fourthLabel animator] setEnabled:NO];
    [firstLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
    [secondLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
    [thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
    [fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
}

- (void)stage5 {
	if (reset) {
		reset = false;
		[self start];
		return;
	}
	
	if (jailbreaking) return;
    
    // I know... system() isn't great programming practice... But when I tried to get the code that loops through the list of running processes to work, I ended up killing every running process on my computer, and I just don't have time to test that right now, since it takes like 10 minutes to reboot.
    system("killall iTunes\ Helper");
    system("killall iTunes");
	int current = [[secondsLabel stringValue] intValue];
	
    if (current != 0) {
        [secondsLabel setStringValue:[NSString stringWithFormat:@"%d", current-1]];
        [self performSelector:@selector(stage5) withObject:nil afterDelay:1.0];
    } else {
        [fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
        
        [self cancel];
        [jailbreakButton setEnabled:YES];
        [jailbreakButton setTitle:@"Try Again?"];
        [progressIndicator stopAnimation:nil];
    }
}

- (void)newAppleTVCheck
{
	NSString *productType = [chosenOne valueForKey:@"ProductType"];
	
	if ([productType isEqualToString:@"AppleTV2,1"])
	{
		NSLog(@"productType is AppleTV2,1");
		appletv = true;
		[self new_appletvafy];
	} else {
		appletv = false;
	}
}

- (void)showIncompatibleAlert:(NSDictionary *)chosen 
{
	NSString *productType = [chosen valueForKey:@"ProductType"];
	NSString *productVersion = [chosen valueForKey:@"BuildVersion"];
	NSAlert *incompatAlert = [NSAlert alertWithMessageText:@"Incompatible Setup" defaultButton:@"Quit" alternateButton:@"Different device" otherButton:nil informativeTextWithFormat:@"The '%@' running '%@' is not compatible with this version of greenpois0n. Either Quit or choose a different device.", productType, productVersion];
	int button = [incompatAlert runModal];
	
	switch (button) {
			
		case 1: //Quit
			
			[[NSApplication sharedApplication] terminate:self];
			
			break;
			
		case 0: //Different Device
			
				//nada

			break;
			
			
	}
	
}

- (void)showNoDeviceAlert
{
	NSAlert *startupAlert = [NSAlert alertWithMessageText:@"No Devices Detected!" defaultButton:@"Quit" alternateButton:@"Continue" otherButton:nil informativeTextWithFormat:@"Devices must be attached in userland mode for version detection (For AppleTV's that means powered on first, then plugged in to USB)\n\nTo continue with support for 4.3.3 only (8F305 for AppleTV) press 'Continue' otherwise connect your devices and relaunch."];
	int button = [startupAlert runModal];
	
	switch (button) {
			
		case 1: //Quit
		
			[[NSApplication sharedApplication] terminate:self];
			
			break;
			
		case 0: //Continue
			
			[self appleTVCheck];
			break;
			
			
	}
	
}
- (void)appleTVCheck
{
	NSAlert *startupAlert = [NSAlert alertWithMessageText:@"Are you jailbreaking an AppleTV?" defaultButton:@"No" alternateButton:@"Yes" otherButton:nil informativeTextWithFormat:@"If you are jailbreaking an AppleTV, please choose yes before continuing.\n\nNOTE: it takes approximately 40 seconds after 'Complete!' for the ramdisk to finish on an AppleTV jailbreak. \n\nPlease don't unplug the USB cable until then."];
	int button = [startupAlert runModal];
	
	switch (button) {
		case 1: //no
			
			appletv = false;
			break;
			
		case 0: //yes
			appletv = true;
			[self new_appletvafy];
			break;
			
			
	}
	[self showYourself];
}

- (void)dealloc
{
	[deviceManager release];
	
}

- (NSDictionary *)fetchAttachedDevices
{
		//NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	const char *xml = get_attached_devices_xml();
	NSString *string = [NSString stringWithUTF8String:xml];
	NSData * data = [string dataUsingEncoding:NSUTF8StringEncoding];
	
	NSString *errorDesc = nil;
	NSPropertyListFormat format;
	NSDictionary * dict = (NSDictionary*)[NSPropertyListSerialization
										  propertyListFromData:data
										  mutabilityOption:NSPropertyListMutableContainersAndLeaves
										  format:&format
										  errorDescription:&errorDesc];
	
		//[pool release];
	return dict;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	
		//[self appleTVCheck];
	attachedDevices = [self fetchAttachedDevices];
		//NSLog(@"attachedDevices: %@", attachedDevices);
		//NSString *attachedDevicesPlist = [NSHomeDirectory() stringByAppendingPathComponent:@"attached.plist"];
		//[attachedDevices writeToFile:attachedDevicesPlist atomically:YES];
	
		//OG code below-- well sort of.
	//[window makeKeyAndOrderFront:nil];
//	[window center];
	
	

	if ([attachedDevices count] > 0)
	{
			
		deviceManager = [[GPUSLDeviceManager alloc] initWithDevices:attachedDevices];
		[deviceManager setDelegate:self];
	} else {
		
		[self showNoDeviceAlert];
		
	}

	
	
}

- (void)appletvafy
{
	[firstLabel setStringValue:@"Plug AppleTV in to USB"];
	[secondLabel setStringValue:@"Plug in power adapter"];
	[thirdLabel setStringValue:@"Press and hold MENU and PLAY/PAUSE"];
	[fourthLabel setStringValue:@"Release both buttons"];
	
	
}

- (void)new_appletvafy
{
	[firstLabel setStringValue:@"Press and hold MENU and DOWN"];
	[secondLabel setStringValue:@"Release both buttons"];
	[thirdLabel setStringValue:@"Press and hold MENU and PLAY/PAUSE"];
	[fourthLabel setStringValue:@"Release both buttons"];
	
	
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}
@end

int main(int argc, char *argv[]) {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	[NSApplication sharedApplication];
    
	NSString *appName = @"greenpois0n";
	buildMenus(appName);
	
	Callback *callback = [[Callback alloc] init];
    [[NSApplication sharedApplication] setDelegate:callback];

	NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(250, 312, 480, 270) styleMask:NSClosableWindowMask|NSTitledWindowMask|NSMiniaturizableWindowMask backing:NSBackingStoreBuffered defer:NO];
	NSView *greenView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 420, 270)];
	NSTextField *poisonJBLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(111, 217, 257, 44)];
	NSTextField *instructionLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(17, 199, 446, 17)];
	secondsLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(340, 50, 76, 57)];
	secondsTextLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(348, 40, 56, 16)];
	firstLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 85, 317, 16)];
	secondLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 61, 317, 16)];
	thirdLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 37, 317, 16)];
	fourthLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 13, 317, 16)];
	NSTextField *copyrightLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(18, 11, 453, 13)];
	mainBox = [[NSBox alloc] initWithFrame:NSMakeRect(29, 67, 434, 138)];
	NSBox *dividerBox = [[NSBox alloc] initWithFrame:NSMakeRect(319, 7, 5, 98)];
	resetButton = [[NSButton alloc] initWithFrame:NSMakeRect(347, 12, 61, 17)];
	greenpois0nLogo = [[NSImageView alloc] initWithFrame:NSMakeRect(346, 38, 64, 64)];
	progressIndicator = [[NSProgressIndicator alloc] initWithFrame:NSMakeRect(164, 34, 298, 20)];

	[window setContentView:greenView];
	[window setTitle:appName];
	
	labelIfy(poisonJBLabel);
	labelIfy(instructionLabel);
	labelIfy(secondsLabel);
	labelIfy(secondsTextLabel);
	labelIfy(firstLabel);
	labelIfy(secondLabel);
	labelIfy(thirdLabel);
	labelIfy(fourthLabel);
	labelIfy(copyrightLabel);
	[poisonJBLabel setStringValue:appName];
	[poisonJBLabel setFont:[NSFont fontWithName:@"Helvetica Neue Light" size:32.0]];
	[instructionLabel setStringValue:@"Press Jailbreak and follow the directions below."];
	[instructionLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:13.0]];
	[secondsLabel setStringValue:@"0"];
	[secondsLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:48.0]];
	[secondsTextLabel setStringValue:@"Seconds"];
	[secondsTextLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[firstLabel setStringValue:@"Get ready to start."];
	[firstLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[secondLabel setStringValue:@"Press and hold the sleep button."];
	[secondLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[thirdLabel setStringValue:@"Continue holding sleep; press and hold home."];
	[thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[fourthLabel setStringValue:@"Release sleep button; continue holding home."];
	[fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
	[copyrightLabel setStringValue:@"© 2009-2011 chronic dev team (http://chronic-dev.org). Beware the copyright monster!"];
	[copyrightLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:10.0]];
	
	[secondsLabel setAlphaValue:0.0];
	[secondsTextLabel setAlphaValue:0.0];
	[progressIndicator setIndeterminate:FALSE];
	[greenpois0nLogo setImage:[NSImage imageNamed:@"greenpois0n.icns"]];

	[[resetButton cell] setControlSize:NSMiniControlSize];
	[resetButton setBezelStyle:NSRoundRectBezelStyle];
	[resetButton setTitle:@"Reset"];
	[resetButton setFont:[NSFont fontWithName:@"Lucida Grande" size:9.0]];
	[resetButton setFocusRingType:NSFocusRingTypeNone];
	[resetButton setTarget:callback];
	[resetButton setAction:@selector(reset)];
	[resetButton setEnabled:FALSE];
	
	[mainBox addSubview:firstLabel];
	[mainBox addSubview:secondLabel];
	[mainBox addSubview:thirdLabel];
	[mainBox addSubview:fourthLabel];
	[mainBox addSubview:dividerBox];
	[mainBox addSubview:greenpois0nLogo];
	[mainBox addSubview:resetButton];
	[mainBox setTitle:@""];
	[dividerBox setTitle:@""];
	[dividerBox setBoxType:NSBoxSeparator];
	
	jailbreakButton = [[NSButton alloc] initWithFrame:NSMakeRect(26, 28, 138, 32)];
	[jailbreakButton setBezelStyle:NSRoundedBezelStyle];
	[jailbreakButton setTitle:@"Jailbreak"];
	[jailbreakButton setFont:[NSFont fontWithName:@"Lucida Grande" size:13.0]];
	[jailbreakButton setFocusRingType:NSFocusRingTypeNone];
	[jailbreakButton setTarget:callback];
	[jailbreakButton setAction:@selector(start)];
	[greenView addSubview:jailbreakButton];
	[greenView addSubview:progressIndicator];
	[greenView addSubview:mainBox];
	[greenView addSubview:copyrightLabel];
	[greenView addSubview:instructionLabel];
	[greenView addSubview:poisonJBLabel];
		[callback setWindow:window];
	
		//[window makeKeyAndOrderFront:nil];
		//[window center];
    return NSApplicationMain(argc, (const char **)argv);
	[pool release];
}
