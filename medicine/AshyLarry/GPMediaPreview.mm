

#import "GPMediaPreview.h"
#import "GPMedia.h"
#import "CPlusFunctions.mm"

@interface BRCoverArtImageLayer (compat)
-(id)texture;
@end

@interface BRMetadataPreviewControl (compat)
- (void)_populateMetadata;
- (void)_updateMetadataLayer;
- (void) _loadCoverArt;
@end

@interface BRMetadataPreviewControl (protectedAccess)
- (BRMetadataControl *)gimmieMetadataLayer;
@end

@implementation BRMetadataPreviewControl (protectedAccess)
- (BRMetadataControl *)gimmieMetadataLayer
{
	return MSHookIvar<BRMetadataControl *>(self, "_metadataLayer");
}
@end



@implementation GPMediaPreview


- (id)init
{
    self=[super init];
    meta=[[NSMutableDictionary alloc] init];
	return self;
}

- (void)dealloc
{
	[meta release];
	[super dealloc];
}

-(id)coverArtLayer
{
	
	return MSHookIvar<BRCoverArtImageLayer *>(self, "_coverArtLayer");
}

- (void)setImage:(id)currentImage
{
    [image release];
    image=currentImage;
	[currentImage release];
	[[self coverArtLayer] setImage:image];
	
}


- (void)setAsset:(id)asset
{
    MetaDataType=kMetaTypeDefault;
    [super setAsset:asset];
    [[self coverArtLayer] setImage:[asset coverArt]];

}
-(void)setAssetMeta:(id)asset
{
    [self setAsset:asset];
}


+(id)coverArtForPath
{
	return [[NSBundle bundleForClass:[self class]] pathForResource:@"ApplianceIcon" ofType:@"png"];
}

- (id)asset
{
	return MSHookIvar<id>(self, "_asset");
}

- (id)coverArtForPath
{
    if (image!=nil)
        return image;
    image=[[self asset] coverArt];
    if (image!=nil)
        return image;
	return [GPMediaPreview coverArtForPath];
}


- (void)_loadCoverArt
{
	[super _loadCoverArt];
	if([[self coverArtLayer] texture] != nil)
		return;
	
}

- (void)_populateMetadata
{
	[super _populateMetadata];
	[self doPopulation];
}


- (void)_updateMetadataLayer
{
	[super _updateMetadataLayer];
	[self doPopulation];
}

- (void)doPopulation
{
    BRMetadataControl *metaLayer = [self gimmieMetadataLayer];
    switch (MetaDataType) {
        case kMetaTypeDefault:
        {
            id asset = [self asset];
            if ([asset respondsToSelector:@selector(orderedDictionary)]) {
                NSDictionary *assetDict=[asset orderedDictionary];
                if([[assetDict allKeys] containsObject:GP_META_TITLE])
                    [metaLayer setTitle:[assetDict objectForKey:GP_META_TITLE]];
                if([[assetDict allKeys] containsObject:GP_META_SUMMARY])
                    [metaLayer setSummary:[assetDict objectForKey:GP_META_SUMMARY]];
                if([[assetDict allKeys] containsObject:GP_META_CUSTOM_KEYS])
                {
                
                    [metaLayer setMetadata:[assetDict objectForKey:GP_META_CUSTOM_OBJECTS] withLabels:[assetDict objectForKey:GP_META_CUSTOM_KEYS]];
                }
            }
            break;
        }
        default:
        {
            [metaLayer setTitle:[meta objectForKey:GP_META_TITLE]];
            [metaLayer setSummary:[meta objectForKey:GP_META_SUMMARY]];
            break;
        }
			
    }
   
	
}


- (BOOL)_assetHasMetadata
{
	return YES;
}

@end



