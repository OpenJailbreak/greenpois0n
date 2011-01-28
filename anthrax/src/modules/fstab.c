/**
 * GreenPois0n Anthrax - fstab.c
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

#include "fstab.h"
#include "utils.h"
#include "device.h"

int fstab_install() {
	int ret;
	gp_device dev;
	gp_get_device_info(&dev);

	mkdir("/mnt/private/etc", 0755);
	if (dev.cpusubtype == GP_DEVICE_ARMV7) {
		ret = cp("/files/fstab_new", "/mnt/private/etc/fstab");
	} else if (dev.cpusubtype == GP_DEVICE_ARMV7) {
		ret = cp("/files/fstab_old", "/mnt/private/etc/fstab");
	}
	/*
	 TODO: strstr(dev.model, "AppleTV")
	 else if(device == DEVICE_ATV) {
	 ret = cp("/files/fstab_atv", "/mnt/private/etc/fstab");
	 }*/
	if (ret < 0)
		return -1;
	return 0;
}

int fstab_uninstall() {
	return -1;
}

