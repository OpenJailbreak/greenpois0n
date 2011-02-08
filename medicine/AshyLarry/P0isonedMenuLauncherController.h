//
//  P0isonedMenuLauncherController.h
//  greenpois0n
//
//  Created by Kevin Bradley on 10/13/10.

#import "GPMedia.h"
#import "GPMediaPreview.h"

@interface P0isonedMenuLauncherController : BRMediaMenuController {
	NSMutableArray *_menuItems;
	NSMutableArray		*_names;
	NSMutableArray		*_versions;
    NSString *          _imageName;
	NSMutableArray *updateArray;
}
//list provider
- (float)heightForRow:(long)row;
- (long)itemCount;
- (id)itemForRow:(long)row;
- (BOOL)rowSelectable:(long)selectable;
- (id)titleForRow:(long)row;

@end
