/*
 *  libdioxin.h
 *  gprc5
 *
 *  Created by Kevin Bradley on 6/4/11.
 *  Copyright 2011 Chronic-Dev Team. All rights reserved.
 *
 */

#include "common.h"

#ifndef LIBDIOXIN_H
#define LIBDIOXIN_H

typedef struct idevice_info_t {
	char *productType;
	char *productVersion;
	char *buildVersion;
	char *deviceName;
	char *hardwareModel;
	char *hardwarePlatform;
	char *uniqueDeviceID;
	char *URL;
	uint64_t uniqueChipID;
	
} idevice_info_t;

uint8_t* getAddressFromUUID(char *uuid);

LIBSYRINGE_EXPORT char * devices_to_xml(idevice_info_t **devices, int itemCount);
LIBSYRINGE_EXPORT idevice_info_t ** get_attached_devices(int *deviceCount);
LIBSYRINGE_EXPORT int print_device_xml();
LIBSYRINGE_EXPORT print_device_info();
LIBSYRINGE_EXPORT char * get_attached_devices_xml();

#endif