/**
 * GreenPois0n Anthrax - device.h
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

#ifndef DEVICE_H
#define DEVICE_H

#include "utils.h"
//#include "firmware.h"

#define MODEL_IPHONE2G      "M68AP"
#define MODEL_IPHONE3G      "N82AP"
#define MODEL_IPHONE3GS     "N88AP"
#define MODEL_IPHONE4       "N90AP"
#define MODEL_IPHONE42      "N92AP"
#define MODEL_IPOD1G        "N45AP"
#define MODEL_IPOD2G        "N72AP"
#define MODEL_IPOD3G        "N18AP"
#define MODEL_IPOD4G        "N81AP"
#define MODEL_IPAD1G        "K48AP"
#define MODEL_APPLETV2      "K68AP"

#define DEVICE_IPHONE2G     "iPhone1,1"
#define DEVICE_IPHONE3G     "iPhone1,2"
#define DEVICE_IPHONE3GS    "iPhone2,1"
#define DEVICE_IPHONE4      "iPhone3,1"
#define DEVICE_IPHONE42	    "iPhone3,3"
#define DEVICE_IPOD1G       "iPod1,1"
#define DEVICE_IPOD2G       "iPod2,1"
#define DEVICE_IPOD3G       "iPod3,1"
#define DEVICE_IPOD4G       "iPod4,1"
#define DEVICE_IPAD1G       "iPad1,1"
#define DEVICE_APPLETV2     "AppleTV2,1"

typedef struct {
	int index;
	char type[10];
	char model[11];
	char version[10];
	//firmware_info_t* firmware;
	enum {
		GP_DEVICE_ARMV6, GP_DEVICE_ARMV7
	} cpusubtype;
} device_info_t;

int device_model(char** model);
int device_version(char** version);
int device_cpusubtype(int* subtype);
int device_info(device_info_t* info);

#endif
