#include <Foundation/Foundation.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
	NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

	NSLog(@"Now trying to interpose hunnypot in fairplayd...\n");
	
	chdir("/mnt/System/Library/LaunchDaemons");

	NSFileManager* fm = [NSFileManager defaultManager];	
	NSArray* files = [fm contentsOfDirectoryAtPath: @"." error: nil];

	NSPredicate* pr = [NSPredicate predicateWithFormat: @"self like 'com.apple.fairplayd.*.plist' and not (self == 'com.apple.fairplayd.default.plist')"];
	NSArray* plistFiles = [files filteredArrayUsingPredicate: pr];

	if ([plistFiles count]==0) {
		printf("Can't find fairplay daemon plist ! Hunnypot won't be installed.\n");
		return 1;
	} else if ([plistFiles count]!=1) {
		printf("More than 1 corresponding plist foung ! Hunnypot won't be installed.\n");
		return 1;
	}

	NSString *plistPath = [plistFiles objectAtIndex: 0]; 
		
	NSMutableDictionary *plistDict = [NSPropertyListSerialization
		propertyListWithData: [NSData dataWithContentsOfFile: plistPath]
		options: NSPropertyListMutableContainers
		format: nil
		error: nil];

	// read var
	NSMutableDictionary *envVarsDict = [plistDict objectForKey: @"EnvironmentVariables"];
	if (envVarsDict == nil) {
		envVarsDict = [NSMutableDictionary dictionary];
	}

	NSString *libs = [envVarsDict objectForKey: @"DYLD_INSERT_LIBRARIES"];
	
	// modify var
	NSMutableArray *aLibs = [[NSMutableArray alloc] initWithArray: [libs componentsSeparatedByString: @":"]];
	[aLibs removeObject: @"/usr/lib/hunnypot.dylib"];
	[aLibs addObject: @"/usr/lib/hunnypot.dylib"];
	libs = [aLibs componentsJoinedByString: @":"];

	// write back var
	[envVarsDict setObject: libs forKey: @"DYLD_INSERT_LIBRARIES"];
	[plistDict setObject: envVarsDict forKey: @"EnvironmentVariables"];

	[plistDict writeToFile: plistPath atomically: YES];

	NSLog(@"OK. fairplayd hunnypot installed.\n");

	[p drain];
}
