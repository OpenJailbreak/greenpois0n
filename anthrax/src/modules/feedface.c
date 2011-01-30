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
#include "feedface.h"

#define MAX_PATH 128

int feedface_install() {
	int ret = 0;
	device_info_t info;
	char base[MAX_PATH];
	char punchd[MAX_PATH];
	char kern_sploit[MAX_PATH];
	char flat_interpose[MAX_PATH];

	// Clean up prior attempts
	if(!file_exists("/mnt/sbin/punchd")) {
		puts("- removing evenutal old feedface files.\n");
		ret = feedface_uninstall();
		if(ret < 0) return -1; // you're screwed! sorry!!!
	}

	puts("- detecting device version.\n");
	ret = device_info(&info);
	if(ret < 0) return -1;

	// Construct our base path from device info
	strncat(base, "/files/feedface/", MAX_PATH);
	strncat(base, info.model, MAX_PATH);
	strncat(base, "_", MAX_PATH);
	strncat(base, info.version, MAX_PATH);
	puts("- base_path: ");
	puts(base);
	puts("\n");

	// Install kern_sploit binary
	puts("- installing kernel exploit.\n");
	strncpy(kern_sploit, base, MAX_PATH);
	strncat(kern_sploit, "/kern_sploit", MAX_PATH);
	ret = install(kern_sploit, "/mnt/usr/lib/kern_sploit", 0, 80, 0755);
	if (ret < 0) return -1;

	puts("- backing up launchd.\n");
	ret = install("/mnt/sbin/launchd", "/mnt/sbin/punchd", 0, 80, 0755);
	if (ret < 0) return -1;

	puts("- removing launchd.\n");
	unlink("/mnt/sbin/launchd");
	
	puts("- installing fake launchd.\n");
	strncpy(punchd, base, MAX_PATH);
	strncat(punchd, "/punchd", MAX_PATH);
	ret = install(punchd, "/mnt/sbin/launchd", 0, 80, 0755);
	if (ret < 0) return -1;
	
	// Finally make sure we have our HFS template
	puts("- installing evil hfs image.\n");
	mkdir("/mnt/mnt", 0777);
	ret = install("/files/feedface/hfs_mdb", "/mnt/usr/lib/hfs_mdb", 0, 80, 0755);
	if (ret < 0) return -1;

	return 0;
	
	// // Install flat_interpose dylib
	// strncpy(flat_interpose, base_path, MAX_PATH);
	// strncat(flat_interpose, "/flat_interpose.dylib", MAX_PATH);
	// ret = install(flat_interpose, "/mnt/usr/lib/flat_interpose.dylib", 0, 80, 0755);
	// if (ret < 0) return -1;
}

int feedface_uninstall() {
	int ret = 0;
	if(file_exists("/mnt/sbin/punchd")) {
		unlink("/mnt/sbin/launchd");
		unlink("/mnt/usr/lib/hfs_mdb");
		unlink("/mnt/usr/lib/kern_sploit");

		ret = install("/mnt/sbin/punchd", "/mnt/sbin/launchd", 0, 80, 0755);
		if (ret < 0) return -1;
	}
	return 0;
}

