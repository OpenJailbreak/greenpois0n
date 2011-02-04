//
//  GPDownloadController.h
//  QuDownloader
//
//  Created by Alan Quatermain on 19/04/07.
//  Copyright 2007 AwkwwardTV. All rights reserved.
//
// Updated by nito 08-20-08 - works in 2.x

#import <Foundation/Foundation.h>
#import "GPProgressBarControl.h"

@class BRHeaderControl, BRTextControl, GPProgressBarControl, NSURLDownload;

@interface GPDownloadController : BRController
{

    BRHeaderControl *       _header;
    BRTextControl *         _sourceText;
	GPProgressBarControl *  _progressBar;

    NSURLDownload *_downloader;
    NSString *              _outputPath;
    long long               _totalLength;
    long long               _gotLength;
	
	NSString *_currentURL;
	NSString *_currentDownload;
	NSMutableDictionary *_downloadDictionary;
	NSFileHandle *logHandle;
	BOOL installCompleted;
	id _parentController;
	
}
- (id)parentController;
- (void)setParentController:(id)value;
- (NSFileHandle *)logHandle;
- (NSString *)logPath;
-(CGRect)frame;
- (void)delayScreensaver;
+ (void) clearAllDownloadCaches;
+ (NSString *) downloadCachePath;
+ (NSString *) outputPathForURLString: (NSString *) urlstr;

- (id) init;
- (BOOL) beginDownload;
- (BOOL) resumeDownload;
- (void) cancelDownload;
- (void) deleteDownload;

// stack callbacks

- (void)controlWillDeactivate;

- (void) wasPushed;
- (void) willBePopped;
- (BOOL) isNetworkDependent;

- (void) setTitle: (NSString *) title;
- (NSString *) title;

- (void) setSourceText: (NSString *) text;
- (NSString *) sourceText;

- (float) percentDownloaded;

- (void) storeResumeData;

// NSURLDownload delegate methods
- (void) download: (NSURLDownload *) download
   decideDestinationWithSuggestedFilename: (NSString *) filename;
- (void) download: (NSURLDownload *) download didFailWithError: (NSError *) error;
- (void) download: (NSURLDownload *) download didReceiveDataOfLength: (unsigned) length;
- (void) download: (NSURLDownload *) download didReceiveResponse: (NSURLResponse *) response;
- (BOOL) download: (NSURLDownload *) download
   shouldDecodeSourceDataOfMIMEType: (NSString *) encodingType;
- (void) download: (NSURLDownload *) download
   willResumeWithResponse: (NSURLResponse *) response
                 fromByte: (long long) startingByte;
- (void) downloadDidFinish: (NSURLDownload *) download;

@end
