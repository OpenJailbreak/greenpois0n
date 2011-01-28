/**
  * GreenPois0n Anthrax - launchd.c
  * Copyright (C) 2010 - 2011 Chronic-Dev Team
  * Copyright (C) 2010 - 2011 Joshua Hill
  * Copyright (C) 2010 - 2011 Dustin Howett
  * Copyright (C) 2010 - 2011 Nicolas Haunold
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

//#include <sys/stat.h>
//#include <sys/wait.h>

#include "utils.h"
#include "syscalls.h"
#include "hfs_mount.h"
#include "device.h"


/**
  * Modules
 **/

#include <modules/afc2.h>
#include <modules/capable.h>
#include <modules/feedface.h>
#include <modules/fstab.h>
#include <modules/hacktivation.h>
#include <modules/loader.h>
#include <modules/pf2.h>
#include <modules/sachet.h>


#define DEVICE_UNK 0
#define DEVICE_NEW 1
#define DEVICE_OLD 2
#define DEVICE_ATV 3


const char* fsck_hfs[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1", NULL };
const char* fsck_hfs_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s1", NULL };
const char* fsck_hfs_user[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2s1", NULL };
const char* fsck_hfs_user_old[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s2", NULL };
const char* fsck_hfs_user_atv[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s2", NULL };

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
	mkdir("/mnt/private", 0755);

	puts("Installing fstab... ");
	parse_module_response(fstab_install());

	puts("Installing AFC2... ");
	parse_module_response(afc2_install());

	if(access("/mnt/Applications/MobilePhone.app/", 0) == 0) {
	    puts("Hacktivating... ");
	    parse_module_response(hacktivation_install());
	}

	if(device != DEVICE_ATV) {
	    puts("Installing Loader... ");
	    parse_module_response(loader_install());

	    /**
	      *	  TODO: this should be iPad-only.
	      **/
	    puts("Removing icon lock... ");
	    parse_module_response(capable_install());

	    puts("Refreshing icon cache... ");
	    parse_module_response(sachet_install());
	}

	/**
	  *   TODO: Load untether exploits
	  **/


	return 0;
}

int main(int argc, char* argv[], char* env[]) {
	int ret = 0;
	int device = 0;
	struct stat status;

	console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	dup2(console, 2);
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
			device = DEVICE_ATV;
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
	if(device == DEVICE_ATV) {
		ret = fsexec(fsck_hfs_atv, env);
	} else {
		ret = fsexec(fsck_hfs, env);
	}
	if (ret != 0) {
		puts("Unable to check root filesystem!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Root filesystem checked\n");

	puts("Checking user filesystem...\n");
	if(device == DEVICE_ATV) {
		fsexec(fsck_hfs_user_atv, env);
	} else {
		fsexec(fsck_hfs_user, env);
		fsexec(fsck_hfs_user_old, env);
	}
	puts("User filesystem checked\n");

	puts("Updating filesystem...\n");
	if(device == DEVICE_ATV) {
		ret = hfs_mount("/dev/disk0s1s1", "/mnt", MNT_ROOTFS | MNT_UPDATE);
	} else {
		ret = hfs_mount("/dev/disk0s1", "/mnt", MNT_ROOTFS | MNT_UPDATE);
	}
	if (ret != 0) {
		puts("Unable to update filesystem!\n");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Filesystem updated\n");

	puts("Mounting user filesystem...\n");
	mkdir("/mnt/private/var2", 0755);

	if(device == DEVICE_ATV) {
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
				device = DEVICE_OLD;
			}

		} else {
			device = DEVICE_NEW;
		}
	}
	puts("User filesystem mounted\n");

	puts("Installing files...\n");
	if (install_files(device) != 0) {
		puts("Failed to install files!\n");
		unmount("/mnt/private/var2", 0);
		rmdir("/mnt/private/var2");
		unmount("/mnt/dev", 0);
		unmount("/mnt", 0);
		return -1;
	}
	puts("Installation complete\n");
	sync();

	puts("Unmounting disks...\n");
	rmdir("/mnt/private/var2");
	unmount("/mnt/private/var2", 0);
	unmount("/mnt/dev", 0);
	unmount("/mnt", 0);

	puts("Flushing buffers...\n");
	sync();

	puts("Rebooting device...\n");
	close(console);
	reboot(1);

	return 0;
}
