/**
 * GreenPois0n Anthrax - firmware.h
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

#ifndef FIRMWARE_H
#define FIRMWARE_H


#define FW_APPLETV_431 "8F202"
#define FW_APPLETV_432 "8F305"
#define FW_BUILD_431 "8G4"
#define FW_BUILD_433 "8J2"
#define FW_IPAD1_433 "8J3"

#define FW_APPLETV_421 "8C154"
#define FW_BUILD_421 "8C148"
#define FW_BUILD_426 "8E200"

typedef struct {
	const char* build;
	const char* version;
} firmware_info_t;

int firmware_version(char** version);
int firmware_info(firmware_info_t* info);

#endif
