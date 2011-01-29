/**
 * GreenPois0n Anthrax - feedface.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Nicolas Haunold
 * Copyright (C) 2011 Joshua Hill
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
//#include "feedface.h"

#define MAX_PATH 128

int feedface_install() {
	int ret = 0;
	device_info_t info;
	char base_path[MAX_PATH];
	char kern_sploit[MAX_PATH];
	char flat_interpose[MAX_PATH];

	// Clean up prior attempts
	unlink("/mnt/usr/lib/hfs_mdb");
	unlink("/mnt/usr/lib/kern_sploit");

	ret = device_info(&info);
	if(ret < 0) return -1;

	// Construct our base path from device info
	strncat(base_path, "/files/feedface/", MAX_PATH);
	strncat(base_path, info.model, MAX_PATH);
	strncat(base_path, "_", MAX_PATH);
	strncat(base_path, info.version, MAX_PATH);

	// Install kern_sploit binary
	strncpy(kern_sploit, base_path, MAX_PATH);
	strncat(kern_sploit, "/kern_sploit", MAX_PATH);

	ret = install(kern_sploit, "/mnt/usr/lib/kern_sploit", 0, 80, 0755);
	if (ret < 0) return -1;

	// Install flat_interpose dylib
	strncpy(flat_interpose, base_path, MAX_PATH);
	strncat(flat_interpose, "/flat_interpose.dylib", MAX_PATH);

	ret = install(flat_interpose, "/mnt/usr/lib/flat_interpose.dylib", 0, 80, 0755);
	if (ret < 0) return -1;

	// Finally make sure we have out HFS template
	mkdir("/mnt/mnt", 0777);
	ret = install("/files/feedface/hfs_mdb", "/mnt/usr/lib/hfs_mdb", 0, 80, 0755);
	if (ret < 0) return -1;

	return 0;
}

int feedface_uninstall() {
	int ret = 0;

	unlink("/mnt/sbin/launchd");
	unlink("/mnt/usr/lib/hfs_mdb");
	unlink("/mnt/usr/lib/kern_sploit");

	ret = install("/mnt/sbin/punchd", "/mnt/sbin/launchd", 0, 80, 0755);
	if (ret < 0)
		return -1;

	return 0;
}

