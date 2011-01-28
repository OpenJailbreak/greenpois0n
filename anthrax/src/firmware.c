/**
 * GreenPois0n Anthrax - firmware.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Joshua Hill
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
#include "firmware.h"

const static firmware_info_t firmwares[] = {
		{ "Unknown", "Unknown" },
		{ "8C148",   "4.2.1"   },
		{  NULL,      NULL     }
};

int firmware_version(char** version) {
	int size = 10;
	int node[2] = { NODE_KERN, KERN_OSVERSION };
	return sysctl(node, 2, version, &size, 0, 0);
}

int firmware_info(firmware_info_t* info) {
	return -1;
}

