/**
 * GreenPois0n Syringe - device.h
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 Joshua Hill
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

#ifndef DEVICE_H_
#define DEVICE_H_

#include <libimobiledevice/libimobiledevice.h>

typedef enum {
	kDeviceOff = 0,
	kDeviceDfuMode,
	kDeviceRecoveryMode,
	kDeviceRamdiskMode,
	kDeviceNormalMode
} device_mode_t;

// TODO: Finish or replace device_type_t
typedef enum {
	kDevice
} device_type_t;

typedef struct device_t {
	idevice_t client;
	device_mode_t mode;
	device_type_t type;
	unsigned char* uuid;
	unsigned char* ecid;
} device_t;

device_t* device_create(const char* uuid);
void device_free(device_t* device);

device_mode_t device_get_mode(device_t* device);
device_type_t device_get_type(device_t* device);

int device_get_udid(device_t* device, uint8_t** udid);
int device_get_bdid(device_t* device, uint32_t* bdid);
int device_get_cpid(device_t* device, uint32_t* cpid);
int device_get_ecid(device_t* device, uint64_t* ecid);
void device_enable_debug();

#endif /* DEVICE_H_ */
