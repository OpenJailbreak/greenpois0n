/**
 * GreenPois0n Anthrax - device.c
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

#include "utils.h"
#include "sysctl.h"
#include "device.h"
//#include "firmware.h"

#define BV_CFILE "/mnt/private/var2/mobile/Media/buildversion"


int device_model(char** model) {
	int size = 11;
	int node[2] = { NODE_HW, HW_MODEL };
	return sysctl(node, 2, model, &size, 0, 0);
}

int device_version_new(char** version) {
	
	struct stat status;
	
	//if(stat(BV_CFILE, &status) != 0)
//	{
//		*version = 0;
//		puts("build version file is missing!!! ohnoes!!!\n");
//		return -1;
//	}
	
	while (stat(BV_CFILE, &status) != 0) {
			//sleep(1);
	}
		
	
	int fp = open(BV_CFILE, 0x0000); //O_RDONLY
	
	if (fp < 0) {
		return -1;
	}
	char buf[12];
	int count = read(fp, version, 11);
	
		//putc(version[0]); putc(version[1]); putc(version[2]);
	close(fp);
//	_puts("count: ");
//	puti(count);
//	_puts("\n");
	if (count == 0) {
		return -1;
	}
	
		//*version[count] = 0; // 0-termination
//
//	puts("version: ");
//	puts(version);
//	puts("\n");
	
	return 0;
}


int device_version(char** versions) {
	
	int size = 0;
	int node[2] = { NODE_KERN, KERN_OSVERSION };
	return sysctl(node, 2, versions, &size, 0, 0);
}

int device_cpusubtype(int* subtype) {
	int size = sizeof(int);
	int node[2] = { NODE_HW, HW_CPUSUBTYPE };
	return sysctl(node, 2, subtype, &size, 0, 0);
}

int device_info(device_info_t* info) {
	int i = 0;
	int ret = 0;
	int subtype = 0;
		//char version[12];

	ret = device_model(&info->model);
	if(ret < 0) return -1;

	
	if (!strcmp(info->model, DEVICE_APPLETV2))
	{
		puts("device version appletv!!!\n");
		ret = device_version(&info->version);
		if(ret < 0) return -1;
		
	} else {
		puts("device version new!!!\n");
		ret = device_version_new(&info->version);
		if(ret < 0) return -1;
	}
	

	ret = device_cpusubtype(&subtype);
	if(ret < 0) return -1;

	if (!strcmp(info->model, DEVICE_IPOD2G)) {
		info->cpusubtype = GP_DEVICE_ARMV6;
	} else {
		info->cpusubtype = GP_DEVICE_ARMV7;
	}

	return 0;
}

