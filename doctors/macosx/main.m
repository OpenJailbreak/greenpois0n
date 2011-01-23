//
//  main.m
//  greenpois0n
//
//  Created by Ari Weinstein on 7/02/09.
//  Copyright Squish Software 2009. All rights reserved.
//

#include <libpois0n.h>
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
void buildMenus(NSString *appName);
void labelIfy(NSTextField *textField);
BOOL reset = false;
BOOL stop = false;
BOOL jailbreaking = false;
BOOL complete = false;

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

@interface Callback : NSObject {}
@end
@implementation Callback
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
	[firstLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
	[self performSelector:@selector(stage2) withObject:nil afterDelay:1.0];
	[NSThread detachNewThreadSelector:@selector(check) toTarget:self withObject:nil];
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
		[thirdLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
		[fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande Bold" size:12.0]];
		[self performSelector:@selector(stage5) withObject:nil afterDelay:1.0];
	}
}

- (void)check {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    if (stop) return;
    
    pois0n_init();
	pois0n_set_callback(&update_progress, NULL);
	
    while (stop == false) {
        if (pois0n_is_ready() != -1 && pois0n_is_compatible() != -1) {
            jailbreaking = true;
            stop = true;
            
            [fourthLabel setFont:[NSFont fontWithName:@"Lucida Grande" size:12.0]];
            [secondsLabel setStringValue:@"0"];
            
            [progressIndicator setIndeterminate:YES];
            [progressIndicator startAnimation:nil];
            [jailbreakButton setTitle:@"Jailbreaking..."];
            
            [self performSelectorOnMainThread:@selector(cancel) withObject:nil waitUntilDone:NO];
            
            int result = pois0n_inject();
            [progressIndicator setIndeterminate:YES];
            [progressIndicator stopAnimation:nil];
            
            if (result == 0) {
                [jailbreakButton setTitle:@"Complete!"];
                complete = true;
                jailbreaking = false;
                stop = true;
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
	[copyrightLabel setStringValue:@"© 2009-2010 chronic dev team (http://chronic-dev.org). Beware the copyright monster!"];
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
	
	
	[window makeKeyAndOrderFront:nil];
	[window center];
    return NSApplicationMain(argc, (const char **)argv);
	[pool release];
}