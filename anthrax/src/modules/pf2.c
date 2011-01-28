/**
 * GreenPois0n Anthrax - pf2.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Nicolas Haunold
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

#include "pf2.h"
#include "utils.h"
#include "device.h"

const char* patch_dyld_new[] = { "/usr/bin/data", "-C",
		"/System/Library/Caches/com.apple.dyld/dyld_shared_cache_armv7", NULL };
const char* patch_dyld_old[] = { "/usr/bin/data", "-C",
		"/System/Library/Caches/com.apple.dyld/dyld_shared_cache_armv6", NULL };
const char* patch_kernel[] = { "/usr/bin/data", "-K", NULL };

int pf2_install() {
	int ret;
	gp_device dev;
	gp_get_device_info(&dev);

	mkdir("/mnt/private/var", 0755);
	mkdir("/mnt/private/var/db", 0755);
	mkdir("/mnt/private/var/db/launchd.db", 0755);
	mkdir("/mnt/private/var/db/launchd.db/com.apple.launchd", 0755);

	unlink("/mnt/usr/lib/pf2");
	unlink("/mnt/usr/bin/data");
	unlink("/mnt/usr/lib/libgmalloc.dylib");
	unlink("/mnt/private/var/db/.launchd_use_gmalloc");

	if (dev.cpusubtype == GP_DEVICE_ARMV6) {
		ret = install("/files/data_old", "/mnt/usr/bin/data", 0, 80, 0755);
	} else if (dev.cpusubtype == GP_DEVICE_ARMV7) {
		ret = install("/files/data_new", "/mnt/usr/bin/data", 0, 80, 0755);
	}

	if (ret < 0)
		return -1;

	if (dev.cpusubtype == GP_DEVICE_ARMV6) {
		fsexec(patch_dyld_old, cache_env);
	} else if (dev.cpusubtype == GP_DEVICE_ARMV7) {
		fsexec(patch_dyld_new, cache_env);
	}

	ret = install("/mnt/libgmalloc.dylib", "/mnt/usr/lib/libgmalloc.dylib", 0,
			80, 0755);

	fsexec(patch_kernel, cache_env);
	ret = install("/mnt/pf2", "/mnt/usr/lib/pf2", 0, 80, 0755);

	ret = install("/files/launchd_use_gmalloc",
			"/mnt/private/var/db/.launchd_use_gmalloc", 0, 80, 0755);
	if (ret < 0)
		return -1;

	unlink("/mnt/pf2");
	unlink("/mnt/libgmalloc.dylib");
	unlink("/mnt/usr/bin/data");

	return 0;
}

int pf2_uninstall() {
	return -1;
}

