/**
  * GreenPois0n Medicine - LoaderVC.m
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Nicolas Haunold
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#import "LoaderVC.h"
#import "UIProgressHUD.h"
#import "Defines.h"
#import "Callback.h"
#import "MemLoaderOperation.h"
#import "NSURLDownload.h"
#import <unistd.h> 
#import "tar.h"

@interface UIDevice (LoaderExt) 
- (BOOL)isWildcat;
@end

@implementation LoaderVC

- (void)addHUDWithText:(NSString *)text {
	[self.view setUserInteractionEnabled:NO];
	[_myHud setAutoresizingMask:(UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight)];
	[_myHud setText:text];
	[_myHud showInView:[[UIApplication sharedApplication] keyWindow]];
}

- (void)removeHUD {
	[_myHud hide];
	[self.view setUserInteractionEnabled:YES];
}

- (void)showOptions:(id)sender {
	// sigh
	UIActionSheet *_ = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:@"Remove Loader.app" otherButtonTitles:nil];
	[_ setTag:0x8BAA];
	[_ showInView:self.view];
	[_ release];
}

- (void)viewDidLoad {
	[super viewDidLoad];

	self.title = kTitle;
	
	UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithTitle:@"Options" style:UIBarButtonItemStyleBordered target:self action:@selector(showOptions:)];
	self.navigationItem.leftBarButtonItem = item;
	[item release];

	_queue = [[NSOperationQueue alloc] init];
	_myHud = [[UIProgressHUD alloc] initWithWindow:[[UIApplication sharedApplication] keyWindow]];
	[self addHUDWithText:@"Loading Sources"];
	
	// Loading Sources
	Callback *c = [[Callback alloc] initWithTarget:self action:@selector(updatedSources:) object:nil];
	MemLoaderOperation *o = [[MemLoaderOperation alloc] init];
	[o setUrl:[NSURL URLWithString:kLoaderURL]];
	[o setCallback:c];
	
	[_queue addOperation:o];
	[o release];
	[c release];
}

// -------
// Loader Delegates

- (void)updatedSources:(id)obj {
	if(obj == nil) {
		[self removeHUD];
		UIAlertView *_ = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Please make sure that you're connected to the internet before launching Loader." delegate:nil cancelButtonTitle:@"Dismiss" otherButtonTitles:nil];
		[_ show];
		[_ release];
	} else {
		NSDictionary *ref = (NSDictionary *)CFPropertyListCreateFromXMLData(kCFAllocatorDefault, (CFDataRef)obj, kCFPropertyListImmutable, NULL);
		if(ref != nil && [ref isKindOfClass:[NSDictionary class]]) {
			_sourceDict = [ref retain];
		}
		
		
		[self performSelector:@selector(removeHUD) withObject:nil afterDelay:1.0];
		[self.tableView performSelector:@selector(reloadData) withObject:nil afterDelay:1.0];
	}
}

// -------
// Table View Delegates

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return [[_sourceDict objectForKey:@"AvailableSoftware"] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	static NSString *CellIdentifier = @"Cell";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if(cell == nil) {
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
	}
	
	UIImage *img = [[[UIImage alloc] initWithContentsOfFile:[NSString stringWithFormat:@"/Applications/Loader.app/%@", [[[_sourceDict objectForKey:@"AvailableSoftware"] objectAtIndex:indexPath.row] objectForKey:@"Icon"]]] autorelease];
	cell.imageView.image = img;
	cell.textLabel.text = [[[_sourceDict objectForKey:@"AvailableSoftware"] objectAtIndex:indexPath.row] objectForKey:@"Name"];
	cell.detailTextLabel.text = [[[_sourceDict objectForKey:@"AvailableSoftware"] objectAtIndex:indexPath.row] objectForKey:@"Description"];
	
	return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return 55;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
	if(_sourceDict && [_sourceDict objectForKey:@"Version"]) {
		NSTimeInterval unixDate = (NSTimeInterval)[[_sourceDict objectForKey:@"LastUpdate"] longLongValue];
		NSDate *date = [NSDate dateWithTimeIntervalSince1970:unixDate];
		NSDateFormatter *form = [[[NSDateFormatter alloc] init] autorelease];
		[form setDateStyle:NSDateFormatterMediumStyle];
		[form setTimeStyle:NSDateFormatterShortStyle];
	
		return [NSString stringWithFormat:@"%@\nLast Update: %@\nVersion %@", [_sourceDict objectForKey:@"Message"], [form stringFromDate:date], [_sourceDict objectForKey:@"Version"]];
	}
	
	return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *item = [[_sourceDict objectForKey:@"AvailableSoftware"] objectAtIndex:indexPath.row];
	_currentIndex = indexPath;

	UIActionSheet *a = [[UIActionSheet alloc] init];
	[a setDelegate:self];
	[a addButtonWithTitle:[NSString stringWithFormat:@"Install %@", [item objectForKey:@"Name"]]];
	[a addButtonWithTitle:@"Cancel"];
	[a setCancelButtonIndex:1];
	
	[a showInView:self.view];
	[a release];
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
	[self.tableView deselectRowAtIndexPath:_currentIndex animated:YES];

	if(actionSheet.tag != 0x8BAA) {
		if(buttonIndex != [actionSheet cancelButtonIndex]) {
			NSDictionary *item = [[_sourceDict objectForKey:@"AvailableSoftware"] objectAtIndex:_currentIndex.row];
		
			if([[item objectForKey:@"AllowReinstall"] boolValue] == FALSE) {
				if([[NSFileManager defaultManager] fileExistsAtPath:[item objectForKey:@"ReinstallCheckPattern"]]) {
					UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:[NSString stringWithFormat:@"%@ has already been installed.", [item objectForKey:@"Name"]] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
					[alert show];
					[alert release];
					return;
				}
			}

			NSURLRequest *theRequest = [NSURLRequest requestWithURL:[NSURL URLWithString:[item objectForKey:@"URL"]]];
			NSURLDownload *theDownload = [[NSURLDownload alloc] initWithRequest:theRequest delegate:self];
			if(theDownload) {
				[theDownload setDestination:@"/var/mobile/loader_package.tar" allowOverwrite:YES];
				[self addHUDWithText:@"Downloading..."];
			} else {
				UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Unknown Error. Check Internet Connection." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
				[alert show];
				[alert release];
			}
		}
	} else {
		if(buttonIndex != [actionSheet cancelButtonIndex]) {
			if(buttonIndex == 0) {
				[self suicide];
			}
		}
	}
}


- (void)download:(NSURLDownload *)download didReceiveDataOfLength:(unsigned)length {
	long long expectedLength = [downloadResponse expectedContentLength];
	bytesReceived = bytesReceived+length;
	
	float percentComplete = (bytesReceived/(float)expectedLength);
	NSString *str = [NSString stringWithFormat:@"Downloading... (%d", (long long)(percentComplete*100)];
	str = [str stringByAppendingString:@"%)"];
	
	[_myHud setText:str];
}

- (void)download:(NSURLDownload *)download didReceiveResponse:(NSURLResponse *)response {
	bytesReceived = 0;
	[self setDownloadResponse:response];
}

- (void)download:(NSURLDownload *)download didFailWithError:(NSError *)error {
	[download release];
	
	[self removeHUD];
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:[error localizedDescription] delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

- (void)setDownloadResponse:(NSURLResponse *)aDownloadResponse {
	[aDownloadResponse retain];
	[downloadResponse release];
	downloadResponse = aDownloadResponse;
}
 
- (void)removeStuff {
	NSFileManager *f = [NSFileManager defaultManager];
	[f removeItemAtPath:@"/var/mobile/loader_package.tar.gz" error:nil];
}

- (void)suicide {
	[[NSFileManager defaultManager] removeItemAtPath:@"/Applications/Loader.app/" error:nil];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
	if(alertView.tag == 0xDEADBEEF) {
		if(buttonIndex != [alertView cancelButtonIndex]) {
			[self suicide];
		}
	}
	
	[[[UIApplication sharedApplication] delegate] setReboot:YES];
}

- (void)extractPackage {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	untar("/var/mobile/loader_package.tar", "/");

	[self performSelectorOnMainThread:@selector(cleanUp) withObject:nil waitUntilDone:YES];

	[pool release];
}


- (BOOL)isWildcat {
	if([[UIDevice currentDevice] respondsToSelector:@selector(isWildcat)] && [[UIDevice currentDevice] isWildcat]) {
		return YES;
	}

	return NO;
}

- (void)cleanUp {
	notify_post("com.apple.mobile.application_installed");
	
	[_myHud done];
	[_myHud setText:@"Success!"];

/*	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Warning" message:@"Do you want to remove Loader from your device?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Remove", nil];
	[alert setTag:0xDEADBEEF];
	[alert show];
	[alert release];
*/

	[self removeStuff];
	[self performSelector:@selector(removeHUD) withObject:nil afterDelay:2.0];
	
	if([self isWildcat]) {
		NSString *filePath = @"/System/Library/CoreServices/SpringBoard.app/K48AP.plist";
		
		NSMutableDictionary *capabilityDict, *fileDict;

		fileDict = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
		capabilityDict = [[NSMutableDictionary alloc] initWithDictionary:[fileDict objectForKey:@"capabilities"]];
		
		[capabilityDict setObject:[NSNumber numberWithBool:NO] forKey:@"hide-non-default-apps"];

		[fileDict setObject:capabilityDict forKey:@"capabilities"];
		[fileDict writeToFile:filePath atomically:NO];

		[fileDict release];
		[capabilityDict release];
	}

}

- (void)downloadDidFinish:(NSURLDownload *)download {
	[download release];
	[_myHud setText:@"Extracting..."];
	
	[NSThread detachNewThreadSelector:@selector(extractPackage) toTarget:self withObject:nil];
}

- (void)dealloc {
	if(_sourceDict) [_sourceDict release];
	
	[_queue release];
	[_myHud release];
	[super dealloc];
}


@end

