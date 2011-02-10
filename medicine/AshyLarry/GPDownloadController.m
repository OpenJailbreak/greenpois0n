//

#import <Foundation/Foundation.h>
#import "GPDownloadController.h"
	//this is the size of the file right now 16721856
@interface BRThemeInfo (SpecialAdditions)

- (id)centeredParagraphTextAttributesGP;
- (id)leftJustifiedParagraphTextAttributesGP;

@end

@implementation BRThemeInfo (SpecialAdditions)

- (id)centeredParagraphTextAttributesGP
{
	NSMutableDictionary *myDict = [[NSMutableDictionary alloc] initWithDictionary:[[BRThemeInfo sharedTheme] leftJustifiedParagraphTextAttributesGP]];
	[myDict setValue:[NSNumber numberWithInt:2] forKey:@"BRTextAlignmentKey"];
	return [myDict autorelease];
}

- (id)leftJustifiedParagraphTextAttributesGP
{
	
	/*
	 
	 BRFontName = ".HelveticaNeueATV";
	 BRFontPointSize = 20;
	 BRLineBreakModeKey = 4;
	 BRTextAlignmentKey = 1;
	 CTForegroundColor = "<CGColor 0x4dfb70> [<CGColorSpace 0x4b97b0> (kCGColorSpaceICCBased; kCGColorSpaceModelRGB; ICCProfile(RGB))] ( 1 1 1 1 )";
	 }
	 
	 
	 */
	NSMutableDictionary *myDict = [[NSMutableDictionary alloc] init];
	
	BRThemeInfo *theInfo = [[BRThemeInfo sharedTheme] settingsItemSmallTextAttributes];
	id colorObject = [theInfo valueForKey:@"CTForegroundColor"];
	id fontName = [theInfo valueForKey:@"BRFontName"];
	
	[myDict setValue:[NSNumber numberWithInt:21] forKey:@"BRFontLines"];
	[myDict setValue:[NSNumber numberWithInt:0] forKey:@"BRTextAlignmentKey"];
	id sizeObject = [theInfo valueForKey:@"BRFontPointSize"];
	id fontObject = [theInfo valueForKey:@"BRFontName"];
	[myDict setValue:sizeObject forKey:@"BRFontPointSize"];
	[myDict setValue:fontObject forKey:@"BRFontName"];
	
	[myDict setValue:fontName forKey:@"BRFontName"];
	
	[myDict setValue:colorObject forKey:@"CTForegroundColor"];
	return [myDict autorelease];
}

@end 

@implementation GPDownloadController

- (id)parentController {
    return _parentController;
}

- (void)setParentController:(id)value {
	
	_parentController = value;
    
}

+ (void) clearAllDownloadCaches
{

	[[NSFileManager defaultManager] removeItemAtPath: [self downloadCachePath] error:nil];
}

+ (NSString *) downloadCachePath
{
    static NSString * __cachePath = @"/var/mobile/Library/Preferences";
	if([[NSFileManager defaultManager] createDirectoryAtPath:__cachePath withIntermediateDirectories:YES attributes:nil error:nil])
	{
		NSLog(@"created directory at path: %@", __cachePath);
	} else {
		NSLog(@"failed to create directory at path: %@", __cachePath);
	}
	return ( __cachePath );
}


+ (NSString *) olddownloadCachePath
{
    static NSString * __cachePath = nil;

    if ( __cachePath == nil )
    {
        // find the user's Caches folder
        NSArray * list = NSSearchPathForDirectoriesInDomains( NSCachesDirectory,
            NSUserDomainMask, YES );

        // handle any failures in that API
        if ( (list != nil) && ([list count] != 0) )
            __cachePath = [list objectAtIndex: 0];
        else
            __cachePath = NSTemporaryDirectory( );

        __cachePath = [[__cachePath stringByAppendingPathComponent: @"greenPoison"] retain];

        // ensure this exists
       [[NSFileManager defaultManager] createDirectoryAtPath:__cachePath withIntermediateDirectories:YES attributes:nil error:nil];

	}

    return ( __cachePath );
}


+ (NSString *) outputPathForURLString: (NSString *) urlstr
{
    NSString * cache = [self downloadCachePath];
    NSString * name = [urlstr lastPathComponent];

    // trim any parameters from the URL
    NSRange range = [name rangeOfString: @"?"];
    if ( range.location != NSNotFound )
        name = [name substringToIndex: range.location];

    NSString * folder = [[name stringByDeletingPathExtension]
                         stringByAppendingPathExtension: @"download"];

    return ( [NSString pathWithComponents: [NSArray arrayWithObjects: cache,
        folder, name, nil]] );
}



- (void)popTop
{
	[[self stack] popController];
}

- (id)initWithDictionary:(NSDictionary *)inputDict
{
    if ( [super init] == nil )
        return ( nil );
	
	//NSLog(@"%@ %s", self, _cmd);
	installCompleted = NO;
	_currentDownload = [inputDict valueForKey:@"displayName"];
	_currentURL = [inputDict valueForKey:@"url"];
	//NSLog(@"customUrl: %@", _customUrl);
	_downloadDictionary = [[NSMutableDictionary alloc] initWithDictionary:inputDict];
	[_currentURL retain];
	
	
    return ( self );
}

- (id)initWithURL:(NSString *)downloadURL withName:(NSString *)inputName
{
    if ( [super init] == nil )
        return ( nil );
	
	//NSLog(@"%@ %s", self, _cmd);
	
    _currentDownload = inputName;
	_currentURL = downloadURL;
	//NSLog(@"customUrl: %@", _customUrl);
	[_currentURL retain];
	
	
    return ( self );
}

- (BOOL)brEventAction:(id)fp8;
{
	if (installCompleted == NO)
		return [super brEventAction:fp8];
	
	int theAction = [fp8 remoteAction];
	
	switch (theAction)
	{
		case 1: //menu
			NSLog(@"reboot!");
			[self rebootSystem];
			return YES;
			
	}
	
	return [super brEventAction:fp8];
}

- (void) drawSelf

{
	NSString *urlstr = _currentURL;
	
	_header = [[BRHeaderControl alloc] init];
	_sourceText = [[BRTextControl alloc] init];
	_progressBar = [[GPProgressBarControl alloc] init];
	
	// work out our desired output path
	_outputPath = [[GPDownloadController outputPathForURLString: urlstr] retain];
	
	// lay out our UI
	CGRect masterFrame = [[self parent] frame];
	CGRect frame = masterFrame;
	
	// header goes in a specific location
	frame.origin.y = frame.size.height * 0.82f;
	frame.size.height = [[BRThemeInfo sharedTheme] listIconHeight];
	[_header setFrame: frame];
	
	// progress bar goes in a specific place too (one-eighth of the way
	// up the screen)
	frame.size.width = masterFrame.size.width * 0.45f;
	frame.size.height = ceilf( frame.size.width * 0.068f );
	frame.origin.x = (masterFrame.size.width - frame.size.width) * 0.5f;
	frame.origin.y = masterFrame.origin.y + (masterFrame.size.height * (1.0f / 8.0f));
	[_progressBar setFrame: frame];
	
	NSString *titleString = [NSString stringWithFormat:BRLocalizedString(@"Downloading %@...",@"Downloading %@..."), _currentDownload];
	
	[self setTitle: titleString];
	//NSLog(@"urlstr length: %i", [urlstr length]);
	if ([urlstr length] > 100)
	{
		urlstr = [urlstr lastPathComponent];
	}
	NSString *reformatted = [NSString stringWithFormat:@"Downloading Package: %@", [urlstr lastPathComponent]];
	[self setSourceText: reformatted];   // this lays itself out
	[_progressBar setCurrentValue: [_progressBar minValue]];
	
	// add the controls
	[self addControl: _header];
	[self addControl: _sourceText];
	[self addControl: _progressBar];
	
	
}

- (id) init {
    if ( [super init] == nil )
        return ( nil );

    return ( self );
}

- (void) dealloc
{
    [self cancelDownload];

    [_header release];
    [_sourceText release];
    [_progressBar release];
    [_downloader release];
    [_outputPath release];

    [super dealloc];
}

- (BOOL) beginDownload
{
    if ( _downloader != nil )
        return ( NO );

    // see if we can resume from the current data
    if ( [self resumeDownload] == YES )
        return ( YES );

    // didn't work, delete & try again
    [self deleteDownload];

	//this is commented out because RUIPreferenceManager will break support in 2.1
	NSString *urlstr = _currentURL;

    NSURL * url = [NSURL URLWithString: urlstr];
    if ( url == nil )
        return ( NO );

    NSURLRequest * req = [NSURLRequest requestWithURL: url
                                          cachePolicy: NSURLRequestUseProtocolCachePolicy
                                      timeoutInterval: 20.0];

    // create the dowloader
    _downloader = [[NSURLDownload alloc] initWithRequest: req delegate: self];
    if ( _downloader == nil )
        return ( NO );

    [_downloader setDeletesFileUponFailure: NO];

    return ( YES );
}

- (BOOL) resumeDownload
{
    if ( _outputPath == nil )
        return ( NO );

    NSString * resumeDataPath = [[_outputPath stringByDeletingLastPathComponent]
                                 stringByAppendingPathComponent: @"ResumeData"];
    if ( [[NSFileManager defaultManager] fileExistsAtPath: resumeDataPath] == NO )
        return ( NO );

    NSData * resumeData = [NSData dataWithContentsOfFile: resumeDataPath];
    if ( (resumeData == nil) || ([resumeData length] == 0) )
        return ( NO );

    // try to initialize using the saved data...
    _downloader = [[NSURLDownload alloc] initWithResumeData: resumeData
                                                   delegate: self
                                                       path: _outputPath];
    if ( _downloader == nil )
        return ( NO );

    [_downloader setDeletesFileUponFailure: NO];

    return ( YES );
}

- (void) cancelDownload
{
    [_downloader cancel];
    [self storeResumeData];
}

- (void) deleteDownload
{
    if ( _outputPath == nil )
        return;

	[[NSFileManager defaultManager] removeItemAtPath: [_outputPath stringByDeletingLastPathComponent] error:nil];

}

// stack callbacks
- (void)controlWasActivated;
{
	[self drawSelf];
	
    if ( [self beginDownload] == NO )
    {
        [self setTitle: @"Download Failed"];
        [_progressBar setPercentage: 0.0f];
        ////[[self scene] renderScene];
    }
	
    [super controlWasActivated];
}

- (void) wasPushed {
	
	[super wasPushed];
}

- (void)willBePopped {
	//NSLog(@"%@ %s", self, _cmd);
	[super willBePopped];
}

- (void)controlWillDeactivate;
{
    [self cancelDownload];
    [super controlWillDeactivate];
}

- (BOOL) isNetworkDependent
{
    return ( YES );
}

- (void) setTitle: (NSString *) title
{
    [_header setTitle: title];
}

- (NSString *) title
{
    return ( [_header title] );
}

- (void) setSourceText: (NSString *) srcText
{
	
	[_sourceText setText: srcText withAttributes:[[BRThemeInfo sharedTheme] leftJustifiedParagraphTextAttributesGP]];
	
	
    CGRect masterFrame = [[self parent] frame];
	
	CGSize maxSize;
	maxSize.height = masterFrame.size.height;
	maxSize.width = masterFrame.size.width * 0.66f;
	
    CGSize txtSize = [_sourceText renderedSizeWithMaxSize:maxSize];
	
	
    CGRect frame;
    frame.origin.x = (masterFrame.size.width - txtSize.width) * 0.5f;
    frame.origin.y = (masterFrame.size.height * 0.75f) - txtSize.height;
    frame.size = txtSize;
    
	[_sourceText setFrame: frame];
}

- (NSString *) sourceText
{
    return ( [_sourceText attributedString] );
}

- (float) percentDownloaded
{
    return ( [_progressBar percentage] );
}

- (void) storeResumeData
{
    NSData * data = [_downloader resumeData];
    if ( data != nil )
    {
            // store this in the .download folder
        NSString * path = [[_outputPath stringByDeletingLastPathComponent]
                           stringByAppendingPathComponent: @"ResumeData"];
        [data writeToFile: path atomically: YES];
    }
}

// NSURLDownload delegate methods
- (void) download: (NSURLDownload *) download
   decideDestinationWithSuggestedFilename: (NSString *) filename
{
    // we'll ignore the given filename and use our own
    // they'll likely be the same, anyway

    // ensure that all new path components exist

	[[NSFileManager defaultManager] createDirectoryAtPath:[_outputPath stringByDeletingLastPathComponent] withIntermediateDirectories:YES attributes:nil error:nil];
    //NSLog( @"Starting download to file '%@'", _outputPath );

    [download setDestination: _outputPath allowOverwrite: YES];
}

- (void) download: (NSURLDownload *) download didFailWithError: (NSError *) error
{
    [self storeResumeData];

    NSLog( @"Download encountered error '%d' (%@)", [error code],
           [error localizedDescription] );

    // show an alert for the returned error (hopefully it has nice
    // localized reasons & such...)
    BRAlertController * obj = [BRAlertController alertForError: error];
    [[self stack] swapController: obj];
}

- (void) download: (NSURLDownload *) download didReceiveDataOfLength: (unsigned) length
{
    _gotLength += (long long) length;
    float percentage = 0.0f;

		// NSLog( @"Got %u bytes, %lld total", length, _gotLength );

    // we'll handle the case where the NSURLResponse didn't include the
    // size of the source file
    if ( _totalLength == 0 )
    {
        // bump up the max value a bit
        percentage = [_progressBar percentage];
        if ( percentage >= 95.0f )
            [_progressBar setMaxValue: [_progressBar maxValue] + (float) (length << 3)];
    }
	[self delayScreensaver];
    [_progressBar setCurrentValue: _gotLength];
}

- (void)delayScreensaver
{
	
	//nothing right now. these old classes don't exist and i havent had an opportunity to find new ones
	
	Class cls = NSClassFromString( @"ATVScreenSaverManager" );
	if ( cls != Nil )
	{
		[[cls singleton] _updateActivity:nil];
		//		[[NSNotificationCenter defaultCenter] postNotificationName: kATVScreenSaverHoldOffNotification object: [cls sharedInstance]];
		
	} else if ( cls == Nil ){
		cls = NSClassFromString( @"BRScreenSaverManager" );
		if ( cls != Nil ) [[cls sharedInstance] updateActivity];
	} 
}

- (void) download: (NSURLDownload *) download didReceiveResponse: (NSURLResponse *) response
{
    // we might receive more than one of these (if we get redirects,
    // for example)
    _totalLength = 0;
    _gotLength = 0;

    NSLog( @"Got response for new download, length = %lld", [response expectedContentLength] );

    if ( [response expectedContentLength] != NSURLResponseUnknownLength )
    {
        _totalLength = [response expectedContentLength];
        [_progressBar setMaxValue: (float) _totalLength];
    }
    else
    {
        // the tar size of the tgz file, no idea why it isnt getting expectedContentLength properly, did some creative logging and this is the value that ended up being the final for the tgz file i have hosted.
        [_progressBar setMaxValue: 38072320];
    }
}

- (BOOL) download: (NSURLDownload *) download
   shouldDecodeSourceDataOfMIMEType: (NSString *) encodingType
{
    return YES;
}

- (void) download: (NSURLDownload *) download
   willResumeWithResponse: (NSURLResponse *) response
                 fromByte: (long long) startingByte
{
    // resuming now, so pretty much as above, except we have a starting
    // value to set on the progress bar
    _totalLength = 0;
    _gotLength = (long long) startingByte;

    // the total here seems to be the amount *remaining*, not the
    // complete total

    NSLog( @"Resumed download at byte %lld, remaining is %lld",
           _gotLength, [response expectedContentLength] );

    if ( [response expectedContentLength] != NSURLResponseUnknownLength )
    {
        _totalLength = _gotLength + [response expectedContentLength];
        [_progressBar setMaxValue: (float) _totalLength];
    }
    else
    {
        // an arbitrary number
        [_progressBar setMaxValue: (float) (_gotLength << 1)];
    }

    // reset current value as appropriate
    [_progressBar setCurrentValue: (float) _gotLength];
}


- (void) anaylzeDownload:(NSString *)theDownload
{

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSString *fileSuffix = [theDownload pathExtension];
	NSString *fileName = [_downloadDictionary objectForKey:@"displayName"];
	[self setTitle: [NSString stringWithFormat:@"Installing %@...", fileName]];
	[self setSourceText:@"Installation in progress, please wait."];   // this lays itself out
	
	NSLog(@"install file at path: %@", theDownload);
		//[NSTask launchedTaskWithLaunchPath:@"/usr/bin/pHelper" arguments:[NSArray arrayWithObjects:@"install", theDownload, nil]];
	
	NSString *command =  [NSString stringWithFormat:@"/usr/bin/pHelper install %@", theDownload];
	NSLog(@"command: %@", command);
	int sysReturn = system([command UTF8String]);
	NSLog(@"install finished with: %i", sysReturn);
	if (sysReturn == 0)
	{
		[self setTitle:@"Installation Successful!"];
		[self setSourceText:@"Press Menu to Reboot"];
		installCompleted = YES;
	} else {
		
		[self setTitle:@"Installation failed!"];
		[self setSourceText:[NSString stringWithFormat:@"Installation failed with status: %i", sysReturn]];
		
	}
	
	[pool release];
	
}


- (NSArray *)tarArray
{
	return [NSArray arrayWithObjects:@"tar", @"bz2", @"gz", @"tgz", nil];
}



- (NSFileHandle *)logHandle
{
	logHandle = [[NSFileHandle fileHandleForWritingAtPath:[self logPath]] retain];
	return logHandle;
}

- (NSString *)logPath
{
	NSString * logPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/GPInstall.log"];
	[[NSFileManager defaultManager] createFileAtPath: logPath contents:nil attributes:nil];
	return logPath;
}

- (int)rebootSystem
{
	NSString *command =  @"/usr/bin/pHelper reboot 2";
		//NSLog(@"command: %@", command);
	int sysReturn = system([command UTF8String]);
	return sysReturn;
}


- (void)rebootOptionSelected:(id)option
{
	id controller = nil;
	
	if([[[self stack] peekController] isKindOfClass: [BROptionDialog class]])
	{
		[[self stack] popController];
	}
	
	switch ([option selectedIndex]) {
			
		case 0:
			
			//[self killFinder];
			
		case 1:
			
			
			//[[self stack] popController];
			controller = [self parentController];
			if (controller != nil)
			{
				[[controller list] reload];
				[[self stack] popToController:controller];
			}
			
			
			break;
			
	}
}

- (void)rebootOption
{
	BROptionDialog *opDi = [[BROptionDialog alloc] init];
	[opDi setTitle:@"Installation Successful!"];
	[opDi setPrimaryInfoText:@"Restart Finder now?"  withAttributes:[[BRThemeInfo sharedTheme] menuItemTextAttributes]];
	[opDi setMenuWidthFactor:0.1];
	[opDi addOptionText:@"Yes" isDefault:YES];
	[opDi addOptionText:@"No"];
	[opDi setActionSelector:@selector(rebootOptionSelected:) target:self];
	

	[opDi autorelease];
	[[self stack] pushController:opDi];
}



- (void) downloadDidFinish: (NSURLDownload *) download
{
    // completed the download: set progress full (just in case) and
    // go do something with the data
    [_progressBar setPercentage: 100.0f];

  //  NSLog( @"Download finished" );

    // we'll swap ourselves off the stack here, so let's remove our
    // reference to the downloader, just in case calling -cancel now
    // might cause a problem
    [_downloader autorelease];
    _downloader = nil;

    // By default I'm downloading a music file, so let's use a music
    // player for it, eh?
   // NSError * error = nil;
    //NSURL * url = [NSURL fileURLWithPath: _outputPath];
	
		[NSThread detachNewThreadSelector:@selector(anaylzeDownload:) toTarget:self withObject:_outputPath];
		//[self anaylzeDownload:_outputPath];
	
	

	
}

@end
