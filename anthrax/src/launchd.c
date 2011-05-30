/**
  * GreenPois0n Anthrax - launchd.c
  * Copyright (C) 2010 - 2011 Chronic-Dev Team
  * Copyright (C) 2010 - 2011 Joshua Hill
  * Copyright (C) 2010 - 2011 Dustin Howett
  * Copyright (C) 2010 - 2011 Nicolas Haunold
  * Copyright (C) 2010 - 2011 Justin Williams
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

#include "utils.h"
#include "device.h"
#include "firmware.h"
#include "syscalls.h"
#include "hfs_mount.h"


/**
  * Modules
 **/
#include "modules/afc2.h"
#include "modules/capable.h"
#include "modules/feedface.h"
#include "modules/fstab.h"
#include "modules/hacktivation.h"
#include "modules/loader.h"
#include "modules/pf2.h"
#include "modules/sachet.h"
#include "modules/immutable.h"
#include "modules/animate.h"
#include "modules/fixkeybag.h"
#include "modules/larry.h"
#include "modules/hunnypot.h"
#include "modules/crunchd.h"


	//#define DEBUG 1

#define INSTALL_FIXKEYBAG

#define DEVICE_UNK 0
#define DEVICE_NEW 1
#define DEVICE_OLD 2
#define DEVICE_ATV 3


const char* fsck_hfs[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1", NULL };
const char* fsck_hfs_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s1", NULL };
const char* fsck_hfs_user[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2s1", NULL };
const char* fsck_hfs_user_old[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2", NULL };
const char* fsck_hfs_user_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s2", NULL };

static char* fsck[] = { "/sbin/fsck_hfs", "-fy", NULL, NULL };
static char* fsck_user[] = { "/sbin/fsck_hfs", "-fy", NULL, NULL };

static char** envp = NULL;

void parse_module_response(int err) {
	if(err < 0) {
		puts(" failed.\n");
	} else {
		puts(" done.\n");
	}
}

int install_files(int device) {
	int ret = 0;
	device_info_t info;
	char untethered_exploit[255];

	mkdir("/mnt/private", 0755);

	puts("Checking device information... ");
	parse_module_response(immutable_install());

	ret = device_info(&info);
	if(ret < 0) return -1;

	puts("Model = ");puts(info.model);puts("\n");
	puts("Version = ");puts(info.version);puts("\n");
	puts("Subtype = ");info.cpusubtype == GP_DEVICE_ARMV6 ? puts("ARMv6\n") : puts("ARMv7\n");

	puts("Starting boot animation...");
#ifndef DEBUG
	if (animate_start() != 0) {
		puts("Or maybe not... Moving on....");
	}
#endif
	puts("Installing fstab... ");
	parse_module_response(fstab_install());

	puts("Installing AFC2... ");
	parse_module_response(afc2_install());

	if(!strcmp("iPhone", info.model)) {
	    //puts("Installing hacktivation... \n");
	    //parse_module_response(hacktivation_install());
	}

	if(device != DEVICE_ATV) {
	    puts("Installing Loader... ");
	    parse_module_response(loader_install());

	    if(!strcmp(info.model, DEVICE_IPAD1G)) {
	    	puts("Removing icon lock... ");
	    	parse_module_response(capable_install());
	    }

	    puts("Refreshing icon cache... ");
	    parse_module_response(sachet_install());

	} else if (device == DEVICE_ATV){
		parse_module_response(larry_install());
	
		
	}
	
	
		//temporary Services.plist install for afc2, make sure to comment out!!
	
	//unlink("/mnt/System/Library/Lockdown/Services.plist");
	//install("/files/Services.plist", "/mnt/System/Library/Lockdown/Services.plist", 0, 80, 0755);
	
	// 4.2.1 Untethered Exploit
	//if(!strcmp(FW_BUILD_421, info.version) || !strcmp(info.version, "8C148a")
	//		|| !strcmp(FW_BUILD_426, info.version) || !strcmp(FW_APPLETV_421, info.version)) {
	//	puts("Installing untethered exploit...\n");
	//	parse_module_response(feedface_install());
	//
	//	puts("Installing comex hunnypot...\n");
	//	parse_module_response(hunnypot_install());
	//}
	
		// i0n1c's 4.3.3 Untethered Exploit
	if(!strcmp(FW_BUILD_433, info.version) || !strcmp(info.version, FW_IPAD1_433)
	   || !strcmp(FW_APPLETV_432, info.version)) {
		puts("Installing untethered exploit...\n");
		parse_module_response(crunchd_install());
	
	}
	
		//vzw 4.2.8 untether
	

		if(!strcmp(FW_IPHONE4_VZW_428, info.version) || !strcmp(FW_APPLETV_421, info.version)) {
	
			puts("Installing untethered exploit...\n");
			parse_module_response(feedface_install());
		}
	
		//	puts("Installing untethered exploit...\n");
		//	parse_module_response(feedface_install());
	
	
#ifdef INSTALL_FIXKEYBAG    
    parse_module_response(fixkeybag_install());
#endif
	return 0;
}

int main(int argc, char* argv[], char* env[]) {
	int ret = 0;
	int dev = 0;
	char model[10];
	char root_disk[20];
	char user_disk[20];
	struct stat status;

	console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	envp = env;

	puts("Searching for disk...\n");
	while (stat("/dev/disk0s1", &status) != 0) {
		sleep(1);
	}
	puts("\n\n\n\n\n");
	puts("Pois0nDisk - by Chronic-Dev Team\n");

	puts("Mounting filesystem...\n");
	if (hfs_mount("/dev/disk0s1", "/mnt", MNT_ROOTFS | MNT_RDONLY) != 0) {
		if (hfs_mount("/dev/disk0s1s1", "/mnt", MNT_ROOTFS | MNT_RDONLY) != 0) {
			puts("Unable to mount filesystem!\n");
			return -1;

		} else {
			dev = DEVICE_ATV;
		}
	}
	puts("Filesystem mounted\n");

	puts("Mounting devices...\n");
	if (mount("devfs", "/mnt/dev", 0, NULL) != 0) {
		puts("Unable to mount devices!\n");
		unmount("/mnt", 0);
		return -1;
	}
	puts("Devices mounted\n");

	puts("Checking root filesystem...\n");
	if(dev == DEVICE_ATV) {
		ret = fsexec(fsck_hfs_atv, env, true);
	} else {
		ret = fsexec(fsck_hfs, env, true);
	}
	if (ret != 0) {
		puts("Unable to check root filesystem!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Root filesystem checked\n");

	puts("Updating filesystem...\n");
	if(dev == DEVICE_ATV) {
		ret = hfs_mount("/dev/disk0s1s1", "/mnt", MNT_ROOTFS | MNT_UPDATE);
	} else {
		ret = hfs_mount("/dev/disk0s1", "/mnt", MNT_ROOTFS | MNT_UPDATE);
	}

#ifndef DEBUG
	puts("Starting boot animation\n");
	animate_start();
#endif

	puts("Checking user filesystem...\n");
	if(dev == DEVICE_ATV) {
		fsexec(fsck_hfs_user_atv, env, true);
	} else {
		fsexec(fsck_hfs_user, env, true);
		fsexec(fsck_hfs_user_old, env, true);
	}
	puts("User filesystem checked\n");

	if (ret != 0) {
		puts("Unable to update filesystem!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Filesystem updated\n");

	puts("Mounting user filesystem...\n");
	mkdir("/mnt/private/var2", 0755);

	if(dev == DEVICE_ATV) {
		if (hfs_mount("/dev/disk0s1s2", "/mnt/private/var2", 0) != 0) {
			puts("Unable to mount user filesystem!\n");
			return -1;
		}

	} else {
		if (hfs_mount("/dev/disk0s2s1", "/mnt/private/var2", 0) != 0) {
			if (hfs_mount("/dev/disk0s2", "/mnt/private/var2", 0) != 0) {
				puts("Unable to mount user filesystem!\n");
				return -1;

			} else {
				dev = DEVICE_OLD;
			}

		} else {
			dev = DEVICE_NEW;
		}
	}
	puts("User filesystem mounted\n");

	puts("Installing files...\n");
	if (install_files(dev) != 0) {
		puts("Failed to install files!\n");
		unmount("/mnt/private/var2", 0);
		rmdir("/mnt/private/var2");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}

	//kernel_reader(NULL, NULL);
	puts("Installation complete\n");
	sync();

#ifndef DEBUG
	puts("Stopping boot animation\n");
	animate_stop();
#endif

	puts("Unmounting disks...\n");
	rmdir("/mnt/private/var2");
	unmount("/mnt/private/var2", 0);
	unmount("/mnt/dev", 0);
	unmount("/mnt", 0);

	puts("Flushing buffers...\n");
	sync();

	puts("Rebooting device...\n");
	close(console);
#ifndef DEBUG
	reboot(1);
#endif
	return 0;
}
