/**
 * GreenPois0n Anthrax - crunchd.c (based on feedface)
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Nicolas Haunold
 * Copyright (C) 2011 Joshua Hill
 * Copyright (C) 2011 Kevin Bradley
 * Copyright (C) 2011 Stefan Esser (4.3.x untether exploit)
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
#include "crunchd.h"

#define MAX_PATH 128

int crunchd_install() {
	int ret = 0;
	device_info_t info;
	char base[MAX_PATH];
	char crunchd[MAX_PATH];
	char test[MAX_PATH];
	char flat_interpose[MAX_PATH];

	// Clean up prior attempts
	if(!file_exists("/mnt/sbin/crunchd")) {
		puts("- removing evenutal old crunchd files.\n");
		ret = crunchd_uninstall();
		if(ret < 0) return -1; // you're screwed! sorry!!!
	}

	puts("- detecting device version.\n");
	ret = device_info(&info);
	if(ret < 0) return -1;

	// Construct our base path from device info
	strncat(test, "/mnt/", MAX_PATH);
	strncat(test, info.model, MAX_PATH);
	strncat(test, "_", MAX_PATH);
	strncat(test, info.version, MAX_PATH);
	
	mkdir(test, 0755);
		//return -1;
	
	strncat(base, "/files/crunchd/", MAX_PATH);
	strncat(base, info.model, MAX_PATH);
	strncat(base, "_", MAX_PATH);
	strncat(base, info.version, MAX_PATH);
	puts("- base_path: ");
	puts(base);
	puts("\n");
	

	puts("- backing up launchd.\n");
	if (file_exists("/mnt/sbin/crunchd")==-1) {
		ret = install("/mnt/sbin/launchd", "/mnt/sbin/crunchd", 0, 80, 0755);
		if (ret < 0) return -1;
	} else {
		puts("[!] huh, backup's already there. I don't overwrite it.\n");
	}

	
	puts("- removing launchd.\n");
		unlink("/mnt/sbin/launchd");
	
	puts("- installing fake launchd.\n");
	strncpy(crunchd, base, MAX_PATH);
	strncat(crunchd, "/launchd", MAX_PATH);
	ret = install(crunchd, "/mnt/sbin/launchd", 0, 80, 0755);
	if (ret < 0)
	{
		ret = crunchd_uninstall();
		return -1;
		
	}
	

	return 0;
}

int crunchd_uninstall() {
	int ret = 0;
	if(file_exists("/mnt/sbin/crunchd")) {
		unlink("/mnt/sbin/launchd");


		ret = install("/mnt/sbin/crunchd", "/mnt/sbin/launchd", 0, 80, 0755);
		if (ret < 0) return -1;
	}
	return 0;
}

