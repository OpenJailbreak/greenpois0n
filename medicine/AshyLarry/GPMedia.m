

#import "GPMedia.h"
#import "GPMediaPreview.h"


@implementation GPMedia

- (id)initWithDictionary:(NSDictionary *)dict
{
	//This is here to fix 2.2
	self = [super init];
	[self setTitle:[dict valueForKey:@"name"]];
	[self setObject:[dict valueForKey:@"name"] forKey:@"title"];
	[self setObject:[dict valueForKey:@"name"] forKey:@"id"];
	[self setObject:[BRMediaType TVShow] forKey:@"mediaType"];
	[self setInstallType:[[dict valueForKey:@"installType"] intValue]];
	[self setDownloadURL:[dict valueForKey:@"url"]];
	[self setVersion:[dict valueForKey:@"version"]];
	[self setImagePath:[dict valueForKey:@"imageUrl"]];
	NSURL *imageURL = [NSURL URLWithString:[dict valueForKey:@"imageUrl"]];
	[self setCoverArt:[BRImage imageWithURL:imageURL]];
	
	return self;
}

- (void)dealloc
{
	[imagePath release];
	[_meta release];
	[super dealloc];
}
-(id)init
{
    self=[super init];
    _meta=[[NSMutableDictionary alloc]init];
    //_image=[GPMedia notFoundImage];
    return self;
}
-(void)setObject:(id)arg1 forKey:(id)arg2
{
    [_meta setObject:arg1 forKey:arg2];
}
-(void)setTitle:(NSString *)title
{
    [_meta setObject:title forKey:GP_META_TITLE];
}
-(void)setSummary:(NSString *)summary
{
    [_meta setObject:summary forKey:GP_META_SUMMARY];
}
-(void)setCustomKeys:(NSArray *)keys forObjects:(NSArray *)objects
{
    if([keys count]==[objects count])
    {
        [_meta setObject:keys forKey:GP_META_CUSTOM_KEYS];
        [_meta setObject:objects forKey:GP_META_CUSTOM_OBJECTS];
    }
}
-(BRImage *)coverArt
{
    return _image;
}
-(void)setCoverArt:(BRImage *)coverArt
{

	_image = coverArt;
}
-(void)setCoverArtPath:(NSString *)path
{
    if ([[NSFileManager defaultManager] fileExistsAtPath:path]) {
        [_image release];
        _image=[[BRImage imageWithPath:path] retain];
    }
	
}
-(NSDictionary *)orderedDictionary
{
    NSMutableDictionary *a=[[NSMutableDictionary alloc] init];
    if([_meta objectForKey:GP_META_TITLE]!=nil)
        [a setObject:[_meta objectForKey:GP_META_TITLE] forKey:GP_META_TITLE];
    if([_meta objectForKey:GP_META_SUMMARY]!=nil)
        [a setObject:[_meta objectForKey:GP_META_SUMMARY] forKey:GP_META_SUMMARY];
    if ([_meta objectForKey:GP_META_CUSTOM_KEYS]!=nil && [_meta objectForKey:GP_META_CUSTOM_OBJECTS]!=nil) {
        [a setObject:[_meta objectForKey:GP_META_CUSTOM_KEYS] forKey:GP_META_CUSTOM_KEYS];
        [a setObject:[_meta objectForKey:GP_META_CUSTOM_OBJECTS] forKey:GP_META_CUSTOM_OBJECTS];
        
    }
	NSDictionary *returnDict = [NSDictionary dictionaryWithDictionary:a];
	[a release];
    return returnDict;
}
- (id)mediaType
{
    return [BRMediaType movie];
}
-(id)assetID
{
    return @"BaseAsset";
}
-(id)title
{
    return [_meta objectForKey:GP_META_TITLE];
}
-(id)summary
{
    return [_meta objectForKey:GP_META_SUMMARY];
}
- (BOOL)hasCoverArt
{
	return YES;
}


+(id)notFoundImage
{
    return [BRImage imageWithPath:[[NSBundle bundleForClass:[self class]] pathForResource:@"ApplianceIcon" ofType:@"png"]] ;
}

- (NSString *)imagePath {
    return [[imagePath retain] autorelease];
}

- (void)setImagePath:(NSString *)value {
    if (imagePath != value) {
        [imagePath release];
        imagePath = [value copy];
    }
}

- (id)initWithMediaURL:(NSURL *)url
{
	//This is here to fix 2.2
	self = [super initWithMediaProvider:nil];
	NSString *urlString = [url absoluteString];
	NSString *filename = [url path];
	[self setObject:[filename lastPathComponent] forKey:@"id"];
	[self setObject:[BRMediaType movie] forKey:@"mediaType"];
	[self setObject:urlString forKey:@"mediaURL"];
	
	return self;
}









- (int)installType {
    return installType;
}

- (void)setInstallType:(int)value {
    if (installType != value) {
        installType = value;
    }
}

- (NSString *)downloadURL {
    return [[downloadURL retain] autorelease];
}

- (void)setDownloadURL:(NSString *)value {
    if (downloadURL != value) {
        [downloadURL release];
        downloadURL = [value copy];
    }
}

- (NSString *)version {
    return [[version retain] autorelease];
}

- (void)setVersion:(NSString *)value {
    if (version != value) {
        [version release];
        version = [value copy];
    }
}



-(id)imageAtPath:(NSString *)path
{
	
	// this returns a CGImageRef
	id sp= [BRImage imageWithPath:[self imagePath]];
	return sp;
		
}

@end
