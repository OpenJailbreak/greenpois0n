

#import "pHelperClass.h"



@implementation pHelperClass

- (NSFileHandle *)logHandle
{
	logHandle = [[NSFileHandle fileHandleForWritingAtPath:[self logPath]] retain];
	return logHandle;
}

- (NSString *)logPath
{
	NSString * logPath = @"/tmp/aptoutput";
	[[NSFileManager defaultManager] createFileAtPath: logPath contents:nil attributes:nil];
	return logPath;
}

- (int)autoInstallFile:(NSString *)theFile atIndex:(int)indexValue
{
	NSLog(@"autoInstallFIle: %@ atINdex:%i", theFile, indexValue);
	
	NSString *autoInstallPath = @"/var/root/Media/Cydia/AutoInstall";
	if (![[NSFileManager defaultManager] fileExistsAtPath:autoInstallPath])
	{
		NSString *mkdir =  [NSString stringWithFormat:@"/bin/mkdir -p %@", autoInstallPath ];
		int returns = system([mkdir UTF8String]);
		if (returns == 0)
		{
				NSLog(@"%@ run successfully", mkdir);
		} else {
			NSLog(@"%@ failed!!!", mkdir);
		}
	
	}
	NSString *fileNameString = [NSString stringWithFormat:@"%02i_%@", indexValue, [theFile lastPathComponent]];
	NSString *finalPath = [autoInstallPath stringByAppendingPathComponent:fileNameString];
	NSString *command =  [NSString stringWithFormat:@"/bin/mv %@ %@", theFile,finalPath ];
	NSLog(@"autoInstallFile: %@", command);
	int sysReturn = system([command UTF8String]);
	if (sysReturn == 0)
		NSLog(@"copied %@ to %@ successfully!", theFile, finalPath);
	
	return sysReturn;

}

- (int)replaceFile:(NSString *)oldFile withFile:(NSString *)newFile
{
	NSFileManager *man = [NSFileManager defaultManager];
	[man removeFileAtPath:oldFile handler:nil];
	if ([man copyPath:newFile toPath:oldFile handler:nil])
	{
		NSLog(@"%@ replaced with %@ successfully!\n", oldFile, newFile);
		[self makeExecutable:oldFile];
		return 0;
	}
	
	NSLog(@"replace fail");
	return -1;
	
}

-(void)reboot
{
	int sysReturn = system([@"/sbin/reboot" UTF8String]);
		//NSTask *rebootTask = [NSTask launchedTaskWithLaunchPath:@"/sbin/reboot" arguments:nil];
}

- (void)editStartup
{
	NSString *startup = @"/usr/libexec/cydia/startup";
	NSMutableString *strings = [[NSMutableString alloc] initWithContentsOfFile:startup encoding:NSUTF8StringEncoding error:nil];
	[strings replaceOccurrencesOfString:@"rm -f \"${debs[@]}\""
							 withString:@"rm -f \"${debs[@]}\"\nkillall -9 AppleTV"
								options:NSLiteralSearch
								  range:NSMakeRange(0, [strings length])];
	[strings writeToFile:startup atomically:YES encoding:NSUTF8StringEncoding error:nil];
	[strings release];
	[self makeExecutable:startup];
}

- (void)mrSelfDestruct
{
	[self editStartup];
		//return;
	NSFileManager *man = [NSFileManager defaultManager];
	NSString *zero = @"/Applications/Lowtide.app/Appliances/0.frappliance";
	NSString *ashyToClassy = @"/Applications/Lowtide.app/Appliances/ashyLarry.frappliance";
	
	NSString *zero2 = @"/Applications/AppleTV.app/Appliances/0.frappliance";
	NSString *ashyToClassy2 = @"/Applications/AppleTV.app/Appliances/ashyLarry.frappliance";
	
	[man removeFileAtPath:zero handler:nil];
	[man removeFileAtPath:ashyToClassy handler:nil];
	[man removeFileAtPath:zero2 handler:nil];
	[man removeFileAtPath:ashyToClassy2 handler:nil];
}

- (int)untarFile:(NSString *)theFile
{
		//[self patchAppleTV];
		//[NSTask launchedTaskWithLaunchPath:@"/usr/bin/wuntar" arguments:[NSArray arrayWithObjects:@"/", theFile, nil]];
		//return 0;
		NSString *command =  [NSString stringWithFormat:@"/usr/bin/wuntar %@ /", theFile];
		int sysReturn = system([command UTF8String]);
		NSLog(@"install finished with: %i", sysReturn);
		NSLog(@"cleaning up...");
		[self mrSelfDestruct];
	
	return sysReturn;
}

- (int)makeExecutable:(NSString *)theFile
{
	
	NSString *commands =  [NSString stringWithFormat:@"/bin/chmod +x %@", theFile];
	NSLog(@"makeExe: %@", commands);
	int sysReturn = system([commands UTF8String]);
	NSLog(@"makeExecutable finished with: %i", sysReturn);
	return sysReturn;

}

- (int)patchAppleTV
{
	[[NSFileManager defaultManager] createFileAtPath:@"/var/root/Media/Cydia/AutoInstall/testing" contents:nil attributes:nil];
	int patchStatus = [self patchFile:@"/Applications/AppleTV.app/AppleTV" withPatch:@"/usr/bin/AppleTV8F202.patch" endMD5:nil];
	if (patchStatus == 0)
	{
		[[NSFileManager defaultManager] createFileAtPath:@"/Applications/AppleTV.app/.patched" contents:nil attributes:nil];
	}
	return patchStatus;
}

- (int)patchFile:(NSString *)patchFile withPatch:(NSString *)thePatch endMD5:(NSString *)desiredMD5
{
	
	NSString *patchedFile = [patchFile stringByAppendingPathExtension:@"patched"];
	NSString *command =  [NSString stringWithFormat:@"/usr/bin/bspatch %@ %@ %@", patchFile,patchedFile,thePatch ];
	
	NSLog(@"patch: %@", command);
	
	int sysReturn = system([command UTF8String]);

	if (sysReturn == 0)
	{
		if (desiredMD5 == nil)
			
		{
			
			NSLog(@"no MD5, skip check!");
			if([[NSFileManager defaultManager] removeItemAtPath:patchFile error:nil])
			{
				NSLog(@"%@ removed successfully!", patchFile);
				if ([[NSFileManager defaultManager] moveItemAtPath:patchedFile toPath:patchFile error:nil])
				{
					NSLog(@"%@ patched and replaced successfully!!", patchFile);
					if ([[patchFile lastPathComponent] isEqualToString:@"AppleTV"])
					{
							NSLog(@"AppleTV +x");
						[self makeExecutable:patchFile];
					}
					if ([[patchFile lastPathComponent] isEqualToString:@"Lowtide"])
					{
							NSLog(@"Lowtide +x");
						[self makeExecutable:patchFile];
					}
					return 0;
				}
			}
			return 0;
			
		}
	
		
	} else {
		NSLog(@"patching: %@ failed!! ABORT!", patchFile);
		return -1;
	}
	return -1;
	
}



@end
