	//
	//  VIPAppliance.m
	//  VIP
	//
	//  Created by Brandon Holland on 10-09-30.
	//  Copyright 2010 whatanutbar. All rights reserved.
	//  Updated by Kevin Bradley on 02-12-11 for mutliple OS support

@interface _VIPAppliance : BRBaseAppliance


@end


static id *_sApplianceWhiteList;

@implementation _VIPAppliance

+ (NSString *)properVersion
{
	Class cls = NSClassFromString(@"ATVVersionInfo");
	if (cls != nil)
	{ return [cls currentOSVersion]; }
	
	return nil;	
}


+ (NSString *)currentOSBuildVersions
{
	Class cls = NSClassFromString(@"ATVVersionInfo");
	if (cls != nil)
	{ return [cls currentOSBuildVersion]; }
	
	return nil;	
}

/*
 nm BackRow | grep _sApplianceWhiteList
 
 4.1 0x3e271ccc 
 4.2 0x3e1a97d8
 4.2.1 0x3e5bf7d8 
 8F5148c 0x3e7f4648
 8F5153d 0x3e3bb780
 8F5166b 0x3e7181b0
 */

+ (void) load 
{
	NSString *version = [_VIPAppliance currentOSBuildVersions];
	NSLog(@"VIP -> loaded AppleTV Version: %@", version);

	if (version != nil)
	{
		if ([version isEqualToString:@"8M89"]) //4.1
			_sApplianceWhiteList = (id *)0x3e271ccc;
		else if ([version isEqualToString:@"8C150"]) //4.2
			_sApplianceWhiteList = (id *)0x3e1a97d8;
		else if ([version isEqualToString:@"8C154"]) //4.2.1
			_sApplianceWhiteList = (id *)0x3e5bf7d8;
		else if ([version isEqualToString:@"8F5148c"])
			_sApplianceWhiteList = (id *)0x3e7f4648;
		else if ([version isEqualToString:@"8F5153d"])
			_sApplianceWhiteList = (id *)0x3e3bb780;
		else if ([version isEqualToString:@"8F5166b"])
			_sApplianceWhiteList = (id *)0x3e7181b0;
		
		
	} else {
	
		_sApplianceWhiteList = (id *)0x3e271ccc;
		
	}
	
	
	NSLog(@"VIP -> old whitelist = %@", *(id*)_sApplianceWhiteList);
	
	[*(id*)_sApplianceWhiteList release];
	*(id*)_sApplianceWhiteList = [[self generateCustomWhiteList] retain];
	NSLog(@"VIP -> new whitelist = %@", *(id*)_sApplianceWhiteList);
}

+ (NSMutableArray *) generateCustomWhiteList
{
	NSMutableArray *whiteList = [NSMutableArray array];
	NSString *lowtidePath = [[NSBundle mainBundle] bundlePath];
	NSString *frapPath = [lowtidePath stringByAppendingPathComponent:@"Appliances"];
	NSDirectoryEnumerator *iterator = [[NSFileManager defaultManager] enumeratorAtPath:frapPath];
	NSString *filePath = nil;
	while((filePath = [iterator nextObject])) 
	{
		if([[filePath pathExtension] isEqualToString:@"frappliance"]) 
		{
			NSBundle *applianceBundle = [NSBundle bundleWithPath:[frapPath stringByAppendingPathComponent:filePath]];
			NSString *applianceClassName = NSStringFromClass([applianceBundle principalClass]);
			if(applianceClassName)
			{ [whiteList addObject: applianceClassName]; }
		}
	}
	return whiteList;
}

@end