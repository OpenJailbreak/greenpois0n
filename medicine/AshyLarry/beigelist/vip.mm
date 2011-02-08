#include <nlist.h>

@interface _VIPAppliance: NSObject
@end

@implementation _VIPAppliance
+ (NSMutableArray *) generateCustomWhiteList {
	NSMutableArray *whiteList = [NSMutableArray array];

	NSString *lowtidePath = [[NSBundle mainBundle] bundlePath];
	NSString *frapPath = [lowtidePath stringByAppendingPathComponent:@"Appliances"];
	NSDirectoryEnumerator *iterator = [[NSFileManager defaultManager] enumeratorAtPath:frapPath];

	NSString *filePath = nil;
	while((filePath = [iterator nextObject])) {
		if([[filePath pathExtension] isEqualToString:@"frappliance"]) {
			NSBundle *applianceBundle = [NSBundle bundleWithPath:[frapPath stringByAppendingPathComponent:filePath]];
			NSString *applianceClassName = NSStringFromClass([applianceBundle principalClass]);

			if(applianceClassName)
				[whiteList addObject:applianceClassName];
		}
	}
	return whiteList;
}


static id *_sApplianceWhiteList;

+ (void)load {
	struct nlist nl[2];
	memset(nl, 0, sizeof(nl));
	nl[0].n_name = (char *)"_sApplianceWhiteList";
	nlist("/System/Library/PrivateFrameworks/BackRow.framework/BackRow", nl);
	_sApplianceWhiteList = (id*)nl[0].n_value;

	NSLog(@"Loaded");
		//NSLog(@"%16.16x", *(int*)_sApplianceWhiteList);
		//NSLog(@"%@", *(id*)_sApplianceWhiteList);
	[*(id*)_sApplianceWhiteList release];
	*(id*)_sApplianceWhiteList = [[self generateCustomWhiteList] retain];
		//NSLog(@"%@", *(id*)_sApplianceWhiteList);
}
@end

// vim:ft=objc
