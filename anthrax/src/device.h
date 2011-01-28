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

#define MODEL_IPHONE2G      "M68AP"
#define MODEL_IPHONE3G      "N82AP"
#define MODEL_IPHONE3GS     "N88AP"
#define MODEL_IPHONE4       "N90AP"
#define MODEL_IPOD1G        "N45AP"
#define MODEL_IPOD2G        "N72AP"
#define MODEL_IPOD3G        "N18AP"
#define MODEL_IPOD4G        "N81AP"
#define MODEL_IPAD1G        "K48AP"
#define MODEL_APPLETV2      "K68AP"

#define DEVICE_UNKNOWN      -1
#define DEVICE_IPHONE2G      0
#define DEVICE_IPOD1G        1
#define DEVICE_IPHONE3G      2
#define DEVICE_IPOD2G        3
#define DEVICE_IPHONE3GS     4
#define DEVICE_IPOD3G        5
#define DEVICE_IPAD1G        6
#define DEVICE_IPHONE4       7
#define DEVICE_IPOD4G        8
#define DEVICE_APPLETV2      9

typedef struct _gp_device {
	int device;
	char model[10];
	char version[10];
	enum {
		GP_DEVICE_ARMV6, GP_DEVICE_ARMV7
	} cpusubtype;
} gp_device;

int gp_get_device_info(gp_device* dev);

#endif
