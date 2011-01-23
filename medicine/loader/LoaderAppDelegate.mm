/**
  * GreenPois0n Medicine - LoaderAppDelegate.mm
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Nicolas Haunold
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#import "LoaderAppDelegate.h"

#include <notify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <objc/runtime.h>

@implementation LoaderAppDelegate
@synthesize window, reboot = _reboot;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	LoaderVC *loader = [[LoaderVC alloc] initWithStyle:UITableViewStyleGrouped];
	navigationController = [[UINavigationController alloc] initWithRootViewController:loader];
	
	[window addSubview:[navigationController view]];
	[window makeKeyAndVisible]; 
	[loader release];
	
	return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
	system("su mobile -c uicache");
	notify_post("com.apple.mobile.application_installed");
	sleep(2);
	if(self.reboot) {
		system("reboot");
	} else {
		system("killall SpringBoard");
	}
	exit(1);
}

- (void)applicationWillResignActive:(UIApplication *)application {
	if([[[UIDevice currentDevice] systemVersion] intValue] >= 4) {
		// no backgrounding for you!
		system("su mobile -c uicache");
		notify_post("com.apple.mobile.application_installed");
		sleep(2);
		if(self.reboot) {
			system("reboot");
		} else {
			system("killall SpringBoard");
		}
		exit(1);
	}
}

- (void)dealloc {
	[navigationController release];
	[window release];
	[super dealloc];
}


@end
