/**
 * GreenPois0n Anthrax - larry.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Kevin Bradley
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

#include "larry.h"
#include "utils.h"

//int writeToFile(const char* info)
//{
//	FILE *file; 
//	file = fopen("/mnt/ramdisk_info.txt","a+"); /* apend file (add text to 
//									a file or create a file if it does not exist.*/ 
//	fprintf(file,"%s",info); /*writes*/ 
//	fclose(file); /*done!*/ 
//	return 0;
//}

int larry_install() {
	int ret;
	
		//ret = cp("/files/fstab_atv", "/mnt/private/etc/fstab");
	
	/*
	ret = install("/files/feedface/AppleTV2,1_8C154/kern_sploit", "/mnt/usr/lib/kern_sploit", 0, 80, 0755);
	ret = install("/mnt/sbin/launchd", "/mnt/sbin/punchd", 0, 80, 0755);
	unlink("/mnt/sbin/launchd");
	install("/files/feedface/AppleTV2,1_8C154/punchd", "/mnt/sbin/launchd", 0, 80, 0755);
	mkdir("/mnt/mnt", 0777);
	ret = install("/files/feedface/hfs_mdb", "/mnt/usr/lib/hfs_mdb", 0, 80, 0755);
	*/
		//mkdir("/mnt/private/var/db", 0755);
	
	/*
	 
	 test / troubleshooting unlinks, not needed for anything in particular for release, just never took em out cuz they help more than 
	 hurt for my purposes
	 
	 */
	
	unlink("/mnt/etc/syslog.conf");
	unlink("/mnt/System/Library/LaunchDaemons/com.apple.syslogd.plist");
	unlink("/mnt/bin/bash");
	unlink("/mnt/usr/bin/pHelper");
	unlink("/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/ashyLarry");
		//unlink("/mnt/Library/LaunchDaemons/com.openssh.sshd.plist");
	
	/*
	 
	 bash, sh and libncurses are the barebones minimum to get wuntar to run from pHelper (setuid tool) from ashyLarry.frappliance loader
	 
	 */
	
	ret = install("/files/libncurses.5.dylib", "/mnt/usr/lib/libncurses.5.dylib", 0, 80, 0755);
	ret = install("/files/bash", "/mnt/bin/bash", 0, 80, 0755);
	ret = install("/files/sh", "/mnt/bin/sh", 0, 80, 0755);
	ret = install("/files/mv", "/mnt/bin/mv", 0, 80, 0755);
	
		//syslog stuff, instrumental for debugging.
	
	ret = install("/files/syslog.conf", "/mnt/etc/syslog.conf", 0, 80, 0755);
	ret = install("/files/com.apple.syslogd.plist", "/mnt/System/Library/LaunchDaemons/com.apple.syslogd.plist", 0, 80, 0755);
	/*
	 ret = install("/files/launchd_use_gmalloc", "/mnt/private/var/db/.launchd_use_gmalloc", 0, 80, 0755); //i dont remember which one of these finally got untether working properly
	 
	 
	 mkdir("/mnt/private/var2/db", 0755); //might not be necessary if hte line below isnt, cant remember which one got it workin var2 or var
	 ret = install("/files/launchd_use_gmalloc", "/mnt/private/var2/db/.launchd_use_gmalloc", 0, 80, 0755);
	 
	 //untether stuff because the step in INSTALL_UNTETHERED didn't work and i didn't full understand them
	 
	 ret = install("/files/libgmalloc.dylib", "/mnt/usr/lib/libgmalloc.dylib", 0, 80, 0755);
	 ret = install("/files/pf2", "/mnt/usr/lib/pf2", 0, 80, 0755);
	 */
	
	/*
	 
	 directory preparation for the loader, 2 frappliances (think bundles to an application, which is how appletv appliances work)
	 
	 0.frappliance is the predecessor of beigelist written by brandon holland in the pre-jailbreak days where we relied on the iphone/pod test harness its sole function 
	 is to replace the built in whitelist and get ashyLarry loaded, is symbol address is hardcoded and will need to be adjusted accordingly for future revisions
	 (i have plans for this that aren't yet implemented)
	 
	 
	 */
	
	mkdir("/mnt/Applications/AppleTV.app/Appliances/0.frappliance", 0755);
	mkdir("/mnt/Applications/AppleTV.app/Appliances/0.frappliance", 0755);
	mkdir("/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance", 0755);
	mkdir("/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/English.lproj", 0755);
	
	puts("Installing old beigelist\n");
	
	ret = install("/files/0.frappliance/0", "/mnt/Applications/AppleTV.app/Appliances/0.frappliance/0", 0, 80, 0755);
		//if (ret < 0) return ret;
	
	ret = install("/files/0.frappliance/Info.plist", "/mnt/Applications/AppleTV.app/Appliances/0.frappliance/Info.plist", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	puts("Installing ashyLarry\n"); //these logs are pointless till i figure out how to get debug logging working to the tv
	
	ret = install("/files/ashyLarry.frappliance/ashyLarry", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/ashyLarry", 0, 80, 06755);
		//if (ret < 0) return ret;
	
	ret = install("/files/ashyLarry.frappliance/About.txt", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/About.txt", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	ret = install("/files/ashyLarry.frappliance/gp_mainMenu.png", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/gp_mainMenu.png", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	ret = install("/files/ashyLarry.frappliance/gp.png", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/gp.png", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	ret = install("/files/ashyLarry.frappliance/Info.plist", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/Info.plist", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	ret = install("/files/ashyLarry.frappliance/English.lproj/InfoPlist.strings", "/mnt/Applications/AppleTV.app/Appliances/ashyLarry.frappliance/English.lproj/InfoPlist.strings", 0, 80, 0644);
		//if (ret < 0) return ret;
	
	ret = install("/files/wuntar", "/mnt/usr/bin/wuntar", 0, 80, 06755);
		//if (ret < 0) return ret;
	
	ret = install("/files/pHelper", "/mnt/usr/bin/pHelper", 0, 80, 06755);
	
	return ret;
}

int larry_uninstall() {
	return -1;
}

