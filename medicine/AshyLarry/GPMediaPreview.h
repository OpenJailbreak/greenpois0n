#define GP_META_IMAGE_URL      @"ImageURL"
#define GP_META_TITLE          @"Name"
#define GP_META_SUMMARY        @"Summary"
#define GP_META_CUSTOM_KEYS    @"KeysArray"
#define GP_META_CUSTOM_OBJECTS @"ObjectsArray"

typedef enum {
    kMetaTypePlug=0,
    kMetaTypeCust=1,
    kMetaTypeSimp=2,
    kMetaTypeDefault=3,
} GPMetaType;


@interface GPMediaPreview : BRMetadataPreviewControl{
	NSMutableDictionary			*meta;
	GPMetaType                MetaDataType;
	BRImage                     *image;

}

- (id)coverArtForPath;
- (void)setImage:(BRImage *)currentImage;


@end

@interface GPMediaPreview (Private)
- (void)doPopulation;
- (NSString *)coverArtForPath;
@end
