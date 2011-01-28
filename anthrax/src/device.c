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

#include "device.h"
#include "utils.h"

int gp_get_device_info(gp_device* dev) {
	int v[2], l, x, y;
	v[0] = 6;
	v[1] = 2;
	l = 10;
	sysctl(v, 2, &dev->model, &l, 0, 0);

	v[0] = 1;
	v[1] = 65;
	sysctl(v, 2, &dev->kernv, &l, 0, 0);

	v[0] = 6;
	v[1] = 15;
	y = sizeof(int);
	sysctl(v, 2, &x, &y, 0, 0);

	if (y <= 412) {
		dev->cpusubtype = GP_DEVICE_ARMV6;
	} else {
		dev->cpusubtype = GP_DEVICE_ARMV7;
	}

	return 0;
}

