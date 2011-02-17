/*
 pHelper.m
 gp
 
 Written by Kevin Bradley

 
 */


#import <Foundation/Foundation.h>
#include <sys/types.h>
#include <unistd.h>
#import "pHelperClass.h"


int main (int argc, const char * argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	setuid(0);
	int i;
	for (i = 1; i < (argc - 1); i+= 2){
		
		NSString *path = [NSString stringWithUTF8String:argv[0]];
		NSString *option = [NSString stringWithUTF8String:argv[i]];
		NSString *value = [NSString stringWithUTF8String:argv[i+1]];
		int index = [[NSString stringWithUTF8String:argv[i+2]] intValue];
			NSLog(@"index: %i", index);
			//	NSLog(@"option: %@", option);
	
		pHelperClass *phc = [[pHelperClass alloc] init];
		if ([option isEqualToString:@"install"])
		{
			int termStatus = [phc untarFile:value];
			[phc release];
			phc = nil;
			return termStatus;
			
		} else if ([option isEqualToString:@"reboot"]){
			NSLog(@"should reboot");
			[phc reboot];
			[phc release];
			phc = nil;
			return 0;
		} else if ([option isEqualToString:@"patch"]){
			NSLog(@"should patch");
			[phc patchAppleTV];
			[phc release];
			phc = nil;
			return 0;
		} else if ([option isEqualToString:@"autoInstall"]){
			NSLog(@"should autoInstall: %@",value );
			int termStatus = [phc autoInstallFile:value atIndex:index];
			[phc release];
			phc = nil;
			return termStatus;
		}
		
		
	
	}
	
	[pool release];
    return 0;
}



void LogIt (NSString *format, ...)
{
    va_list args;
	
    va_start (args, format);
	
    NSString *string;
	
    string = [[NSString alloc] initWithFormat: format  arguments: args];
	
    va_end (args);
	
    printf ("%s", [string cString]);
	
    [string release];
	
} // LogIt
