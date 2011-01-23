//
//  appFunctions.m
//  greenpois0n
//
//  Created by AriX on 9/4/10.
//  Copyright Chronic Dev Team 2010. All rights reserved.
//

#import <Cocoa/Cocoa.h>

void buildMenus(NSString *appName) {
	[NSApp setMainMenu:[[NSMenu alloc] init]];
	
	NSMenu *appleMenu;
	NSMenuItem *menuItem;
	NSString *title;
	NSMenu *windowMenu;
	NSMenuItem  *windowMenuItem;
	
	// Application menu
	appleMenu = [[NSMenu alloc] initWithTitle:@""];
	title = [@"About " stringByAppendingString:appName];
	[appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
	[appleMenu addItem:[NSMenuItem separatorItem]];
	title = [@"Hide " stringByAppendingString:appName];
	[appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
	menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
	[menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
	[appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
	[appleMenu addItem:[NSMenuItem separatorItem]];
	title = [@"Quit " stringByAppendingString:appName];
	[appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];

	// Window menu
	windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
	menuItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
	[windowMenu addItem:menuItem];
	[menuItem release];
	
	// Put menus into the menu bar
	menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
	[menuItem setSubmenu:appleMenu];
	[[NSApp mainMenu] addItem:menuItem];
	[NSApp setAppleMenu:appleMenu];
	windowMenuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
	[windowMenuItem setSubmenu:windowMenu];
	[[NSApp mainMenu] addItem:windowMenuItem];
	[NSApp setWindowsMenu:windowMenu];

	[appleMenu release];
	[menuItem release];
	[windowMenu release];
	[windowMenuItem release];
}

void labelIfy(NSTextField *textField) {
	[textField setBezeled:NO];
	[textField setBordered:NO];
	[textField setDrawsBackground:NO];
	[textField setEditable:NO];
	[textField setSelectable:NO];
	[textField setAlignment:NSCenterTextAlignment];
}