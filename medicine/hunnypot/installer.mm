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

	NSFileManager* fm = [NSFileManager defaultManager];	
	NSArray* files = [fm contentsOfDirectoryAtPath: @"." error: nil];
	if (files==nil || [files count]==0) {
		puts("ERR: no files found.");
		return 1;
	}

	// filtering files to find the correct one
	NSString *plistPath = nil;
	for (NSString *file in files) {
		const char * cpath = [file cStringUsingEncoding: [NSString defaultCStringEncoding]];
		if (strncmp(cpath, "com.apple.fairplayd.", 20)==0 && 
			strstr(cpath, ".plist.default")==NULL) {
			plistPath = file;
			break;
		}

	}
	if (plistPath==nil) {
		puts("ERR: can't find fairplayd plist.");
		return 1;
	}
	puts("Found fairplayd plist: ");
	puts([plistPath cStringUsingEncoding: [NSString defaultCStringEncoding]]);

	// reading the contents as a dictionary
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
