//
//  P0isonedMenuLauncherController.m
//  greenpois0n
//
//  Created by Kevin Bradley on 10/13/10.


#import "P0isonedMenuLauncherController.h"
#import "GPDownloadController.h"
#import <Foundation/Foundation.h>

#define kGPWebURL @"http://nitosoft.com/ATV2/gp/payloads.plist"

@implementation P0isonedMenuLauncherController

- (id) init
{
	if((self = [super init]) != nil) {
		
		//NSLog(@"%@ %s", self, _cmd);
		
		[self setListTitle:@"greenpois0n"];
		
		NSString *settingsPng = [[NSBundle bundleForClass:[P0isonedMenuLauncherController class]] pathForResource:@"gp" ofType:@"png"];
		
		
		id sp = [BRImage imageWithPath:settingsPng];
		[self setListIcon:sp horizontalOffset:0.4 kerningFactor:0.1];
		
		_names = [[NSMutableArray alloc] init];
		_versions = [[NSMutableArray alloc] init];
		updateArray = [[NSMutableArray alloc] init];
	
		BOOL internetAvailable = [BRIPConfiguration internetAvailable];
	
		
		if (internetAvailable == YES)
		{
			
			updateArray = [[NSArray alloc] initWithContentsOfURL:[[NSURL alloc]initWithString:kGPWebURL]];		
		} else {
			
			
			//BRAlertController *alertCon = [self _internetNotAvailable];
			//[alertCon retain];
			//return alertCon;
			
		}
		
	
		
		[updateArray retain];
	
		[[self list] setDatasource:self];
		
		return ( self );
		
	}
	
	return ( self );
}	


-(void)dealloc
{
	[_names release];
	[updateArray release];
	[super dealloc];
}


- (id)previewControlForItem:(long)item
{

	
	GPMedia *currentAsset = [[GPMedia alloc] init];
	[currentAsset setTitle:[[updateArray objectAtIndex:item] valueForKey:@"name"]];
	NSString *currentURL = [[updateArray objectAtIndex:item] valueForKey:@"imageUrl"];
	NSString *currentVersion = [[updateArray objectAtIndex:item] valueForKey:@"version"];
	NSString *description = nil;
	if ([[[updateArray objectAtIndex:item] allKeys] containsObject:@"description"])
		description = [[updateArray objectAtIndex:item] valueForKey:@"description"];
	[currentAsset setCoverArt:[BRImage imageWithURL:[NSURL URLWithString:currentURL]]];
	NSMutableArray *customKeys = [[NSMutableArray alloc] init];
	NSMutableArray *customObjects = [[NSMutableArray alloc] init];
	
	[customKeys addObject:@"Version"];
	[customObjects addObject:@"4.20"];
	
	[customKeys addObject:@"Architect"];
	[customObjects addObject:@"Chronic-Dev Team"];
	if(description != nil)
	{
		[currentAsset setSummary:description];
	}
	[currentAsset setCustomKeys:[customKeys autorelease] 
					 forObjects:[customObjects autorelease]];
	
	
	GPMediaPreview *preview = [[GPMediaPreview alloc]init];
	[preview setAsset:currentAsset];
	[preview setShowsMetadataImmediately:YES];
	[currentAsset release];
	return [preview autorelease];
}


- (void)itemSelected:(long)selected; {
	
	NSDictionary *currentObject = [updateArray objectAtIndex:selected];
	NSLog(@"install item: %@", currentObject);
	GPDownloadController *downloadController = [[GPDownloadController alloc] initWithDictionary:currentObject];
	[[self stack] pushController:downloadController];
	[downloadController release];
}

- (void)doSSHGoodness {
	//NSLog(@"doSSHGoodness");
	//NSLog(@"im goin' from ashy to classy");
}

- (float)heightForRow:(long)row {
	return 0.0f;
}

- (long)itemCount {
	return [updateArray count];
}

- (id)itemForRow:(long)row {
	if(row > [updateArray count])
		return nil;

	//NSLog(@"%@ %s", self, _cmd);
	BRMenuItem * result = [[BRMenuItem alloc] init];
	//NSString *theTitle = [_menuItems objectAtIndex: row];
	NSString *theTitle = [[updateArray objectAtIndex:row] valueForKey:@"name"];
	[result setText:theTitle withAttributes:[[BRThemeInfo sharedTheme] menuItemTextAttributes]];
	[result addAccessoryOfType:7];
	return result;
}

- (BOOL)rowSelectable:(long)selectable {
	return TRUE;
}

- (id)titleForRow:(long)row {
	return [_menuItems objectAtIndex:row];
}

@end
