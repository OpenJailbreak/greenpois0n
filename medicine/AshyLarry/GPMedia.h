@interface GPMedia : BRXMLMediaAsset {
	unsigned int		resumeTime;			
	int					installType;
	NSString			*downloadURL;
	NSString			*version;
	NSString			*imagePath;
	NSMutableDictionary *_meta;
    BRImage *_image;
}
	
- (NSString *)imagePath;
- (void)setImagePath:(NSString *)value;
- (int)installType;
- (void)setInstallType:(int)value;
- (NSString *)downloadURL;
- (void)setDownloadURL:(NSString *)value;
- (NSString *)version;
- (void)setVersion:(NSString *)value;
- (id)initWithMediaURL:(NSURL *)url;

-(void)setObject:(id)arg1 forKey:(id)arg2;
-(void)setTitle:(NSString *)title;
-(void)setSummary:(NSString *)summary;
-(void)setCustomKeys:(NSArray *)keys forObjects:(NSArray *)objects;
-(void)setCoverArt:(BRImage *)coverArt;
-(void)setCoverArtPath:(NSString *)path;
-(NSDictionary *)orderedDictionary;



@end
