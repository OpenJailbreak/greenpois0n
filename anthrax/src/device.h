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

typedef struct _gp_device {
    char model[10];
    char kernv[10];
    enum {
	GP_DEVICE_ARMV6,
	GP_DEVICE_ARMV7
    } cpusubtype;
} gp_device;

int gp_get_device_info(gp_device* dev);

#endif



