/**
 * GreenPois0n Absinthe - device.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libimobiledevice/libimobiledevice.h>

#include "device.h"

device_t* device_create(const char* uuid) {
	idevice_error_t err = 0;
	device_t* device = (device_t*) malloc(sizeof(device_t));
	if (device == NULL) {
		return NULL;
	}
	memset(device, '\0', sizeof(device_t));

	if (uuid == NULL) {
		err = idevice_new(&(device->client), NULL);
		if (err != IDEVICE_E_SUCCESS) {
			error("No device found with uuid %s, is it plugged in?\n", uuid);
			return NULL;
		}
		idevice_get_uuid(device->client, (char**) &device->uuid);

	} else {
		err = idevice_new(&(device->client), uuid);
		if (err != IDEVICE_E_SUCCESS) {
			error("No device found with uuid %s, is it plugged in?\n", uuid);
			return NULL;
		}
		device->uuid = strdup(uuid);
	}

	return device;
}

void device_free(device_t* device) {
	if (device) {
		if(device->uuid) {
			free(device->uuid);
			device->uuid = NULL;
		}
		if (device->client) {
			idevice_free(device->client);
		}
		free(device);
	}
}

device_mode_t device_get_mode(device_t* device) {
	device_mode_t mode = kDeviceOff;
	if (recovery_check_mode() == 0) {
		mode = kDeviceRecoveryMode;
	}
	else if (dfu_check_mode() == 0) {
		mode = kDeviceDfuMode;
	}
	else if (ramdisk_check_mode(device->uuid) == 0) {
		mode = kDeviceRamdiskMode;
	}
	else if (normal_check_mode(device->uuid) == 0) {
		mode = kDeviceNormalMode;
	}
	return mode;
}

device_type_t device_get_type(device_t* device) {
	int device = DEVICE_UNKNOWN;
	uint32_t bdid = 0;
	uint32_t cpid = 0;

	switch (client->mode->index) {
	case MODE_RESTORE:
		device = restore_check_device(client->uuid);
		if (device < 0) {
			device = DEVICE_UNKNOWN;
		}
		break;

	case MODE_NORMAL:
		device = normal_check_device(client->uuid);
		if (device < 0) {
			device = DEVICE_UNKNOWN;
		}
		break;

	case MODE_DFU:
	case MODE_RECOVERY:
		if (get_cpid(client, &cpid) < 0) {
			error("ERROR: Unable to get device CPID\n");
			break;
		}

		switch (cpid) {
		case CPID_IPHONE2G:
			// iPhone1,1 iPhone1,2 and iPod1,1 all share the same ChipID
			//   so we need to check the BoardID
			if (get_bdid(client, &bdid) < 0) {
				error("ERROR: Unable to get device BDID\n");
				break;
			}

			switch (bdid) {
			case BDID_IPHONE2G:
				device = DEVICE_IPHONE2G;
				break;

			case BDID_IPHONE3G:
				device = DEVICE_IPHONE3G;
				break;

			case BDID_IPOD1G:
				device = DEVICE_IPOD1G;
				break;

			default:
				device = DEVICE_UNKNOWN;
				break;
			}
			break;

		case CPID_IPHONE3GS:
			device = DEVICE_IPHONE3GS;
			break;

		case CPID_IPOD2G:
			device = DEVICE_IPOD2G;
			break;

		case CPID_IPOD3G:
			device = DEVICE_IPOD3G;
			break;

		case CPID_IPAD1G:
			device = DEVICE_IPAD1G;
			break;

		default:
			device = DEVICE_UNKNOWN;
			break;
		}
		break;

	default:
		device = DEVICE_UNKNOWN;
		break;

	}
	return device;
}

#define ord_from_hex(c) ('0' <= c && c <= '9') ? c - '0' : (('a' <= c && c <= 'f') ? 10 + (c - 'a') : (('A' <= c && c <= 'F') ? 10 + (c - 'A') : -1 ))

int device_get_udid(device_t* device, uint8_t** udid) {
	if (!device || !device->uuid) {
		return -1;
	}
	int len = strlen(device->uuid);
	if ((len == 0) || (len%2 != 0)) {
		return -1;
	}

	char *s = device->uuid;
	int lo, hi;
	uint8_t *d = *udid;
	do {
		if (((hi = ord_from_hex(s[0])) == -1) || ((lo = ord_from_hex(s[1])) == -1)) return -1;
		*d++ = hi<<4 | lo;
	} while (*(s+=2));

	return 0;
}

int device_get_bdid(struct idevicerestore_client_t* client, uint32_t* bdid) {
	switch (client->mode->index) {
	case MODE_NORMAL:
		if (normal_get_bdid(client->uuid, bdid) < 0) {
			*bdid = 0;
			return -1;
		}
		break;

	case MODE_DFU:
	case MODE_RECOVERY:
		if (recovery_get_bdid(client, bdid) < 0) {
			*bdid = 0;
			return -1;
		}
		break;

	default:
		error("ERROR: Device is in an invalid state\n");
		return -1;
	}

	return 0;
}

int device_get_cpid(struct idevicerestore_client_t* client, uint32_t* cpid) {
	switch (client->mode->index) {
	case MODE_NORMAL:
		if (normal_get_cpid(client->uuid, cpid) < 0) {
			client->device->chip_id = -1;
			return -1;
		}
		break;

	case MODE_DFU:
	case MODE_RECOVERY:
		if (recovery_get_cpid(client, cpid) < 0) {
			client->device->chip_id = -1;
			return -1;
		}
		break;

	default:
		error("ERROR: Device is in an invalid state\n");
		return -1;
	}

	return 0;
}

int device_get_ecid(struct idevicerestore_client_t* client, uint64_t* ecid) {
	switch (client->mode->index) {
	case MODE_NORMAL:
		if (normal_get_ecid(client->uuid, ecid) < 0) {
			*ecid = 0;
			return -1;
		}
		break;

	case MODE_DFU:
	case MODE_RECOVERY:
		if (recovery_get_ecid(client, ecid) < 0) {
			*ecid = 0;
			return -1;
		}
		break;

	default:
		error("ERROR: Device is in an invalid state\n");
		return -1;
	}

	return 0;
}

void device_enable_debug() {
	idevice_set_debug_level(3);
}
