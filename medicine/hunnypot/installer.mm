#include <Foundation/Foundation.h>
#include <unistd.h>
#include <stdio.h>

void _puts(const char* s) {
	while((*s) != '\0') {
		write(1, s, 1);
		s++;
	}
	sync();
}

int main(int argc, char **argv, char **envp) {
	NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

	puts("Now trying to interpose hunnypot in fairplayd...");
	
	chdir("/System/Library/LaunchDaemons");
	puts("XXX: chdir done");

	NSFileManager* fm = [NSFileManager defaultManager];	
	puts("XXX: file manager inited");
	NSArray* files = [fm contentsOfDirectoryAtPath: @"." error: nil];
	puts("XXX: files listed");
	for (NSString *file in files) {
		puts([file cStringUsingEncoding: [NSString defaultCStringEncoding]]);
	}

	if (files==nil) {
		puts("ERR: no files found.");
		return 1;
	}

	NSPredicate* pr = [NSPredicate predicateWithFormat: @"self like 'com.apple.fairplayd.*.plist' and not (self == 'com.apple.fairplayd.default.plist')"];
	puts("XXX: files before filter");
	NSArray* plistFiles = [files filteredArrayUsingPredicate: pr];
	puts("XXX: files filtered");

	if ([plistFiles count]==0) {
		puts("ERR: Can't find fairplay daemon plist! Hunnypot won't be installed.");
		return 1;
	} else if ([plistFiles count]!=1) {
		puts("ERR: More than 1 corresponding plist found! Hunnypot won't be installed.");
		return 1;
	}

	NSString *plistPath = [plistFiles objectAtIndex: 0]; 

	puts("Found fairplayd plist: ");
	puts([plistPath cStringUsingEncoding: [NSString defaultCStringEncoding]]);

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

	puts("OK. fairplayd hunnypot installed.\n");

	[p drain];
}
