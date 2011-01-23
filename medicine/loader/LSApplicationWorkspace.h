#import <Foundation/NSObject.h>

@interface LSApplicationWorkspace : NSObject {
}
+ (id)defaultWorkspace;	// 0xc9c8
- (id)applicationsAvailableForOpeningDocument:(id)openingDocument;	// 0xc6c8
- (id)operationToOpenResource:(id)openResource usingApplication:(id)application uniqueDocumentIdentifier:(id)identifier userInfo:(id)info;	// 0xadc4
- (id)operationToOpenResource:(id)openResource usingApplication:(id)application uniqueDocumentIdentifier:(id)identifier userInfo:(id)info delegate:(id)delegate;	// 0xadf8
- (id)operationToOpenResource:(id)openResource usingApplication:(id)application userInfo:(id)info;	// 0xad90
- (BOOL)registerApplication:(id)application;	// 0xc8bc
- (BOOL)unregisterApplication:(id)application;	// 0xc8dc
@end

