/**
 * GreenPois0n Syringe - dfu.h
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 Joshua Hill
 *
 * Functions for handling idevices in normal mode
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

#ifndef DFU_H
#define DFU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libirecovery.h>
#include "common.h"

typedef struct dfu_mode_t {
	irecv_client_t client;
	const char* ipsw;
	plist_t tss;
} dfu_mode_t;

dfu_mode_t* dfu_create();
dfu_mode_t* dfu_open();
dfu_mode_t* dfu_open_with_timeout(uint32_t timeout);
void dfu_free(dfu_mode_t* dfu);
int dfu_close(dfu_mode_t* dfu);

// TODO: Extract to parent class
//int dfu_enter_recovery(struct idevicerestore_client_t* client, plist_t build_identity);


#ifdef __cplusplus
}
#endif

#endif
