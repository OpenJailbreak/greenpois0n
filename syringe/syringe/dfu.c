/**
 * GreenPois0n Syringe - dfu.c
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 Joshua Hill
 *
 * Functions for handling devices in DFU mode
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
#include <libirecovery.h>

#include "dfu.h"

int dfu_progress_callback(irecv_client_t client, const irecv_event_t* event) {
	if (event->type == IRECV_PROGRESS) {
		print_progress_bar(event->progress);
	}
	return 0;
}

dfu_mode_t* dfu_create() {
	dfu_mode_t* dfu = NULL;
	if(dfu == NULL) {
		return NULL;
	}

	if(dfu) {
		dfu_free(dfu);
	}

	dfu = (dfu_mode_t*) malloc(sizeof(dfu_mode_t));
	if (dfu == NULL) {
		error("ERROR: Out of memory\n");
		return NULL;
	}

	if (dfu_open_with_timeout(10) < 0) {
		dfu_free(dfu);
		return NULL;
	}

	if(dfu->client->mode != kDfuMode) {
		dfu_free(dfu);
		return NULL;
	}

	return dfu;
}

void dfu_free(dfu_mode_t* mode) {
	dfu_mode_t* dfu = NULL;
	if(client != NULL) {
		dfu = mode;
		if (dfu != NULL) {
			if(dfu->client != NULL) {
				irecv_close(dfu->client);
				dfu->client = NULL;
			}
			free(dfu);
		}
	}
}

dfu_mode_t* dfu_open_with_timeout(uint32_t timeout) {
	int i = 0;
	irecv_client_t recovery = NULL;
	irecv_error_t recovery_error = IRECV_E_UNKNOWN_ERROR;

	dfu_mode_t* dfu = dfu_create();
	for (i = 1; i <= timeout; i++) {
		recovery_error = irecv_open(&recovery);
		if (recovery_error == IRECV_E_SUCCESS) {
			break;
		}

		if (i == timeout) {
			error("ERROR: Unable to connect to device in DFU mode\n");
			return NULL;
		}

		sleep(1);
		debug("Retrying connection...\n");
	}

	irecv_event_subscribe(recovery, IRECV_PROGRESS, &dfu_progress_callback, NULL);
	dfu->client = recovery;
	return dfu;
}

int dfu_check_mode() {
	return -1;
}

/*
int dfu_enter_recovery(plist_t build_identity) {
	irecv_client_t dfu = NULL;
	const char* component = "iBSS";
	irecv_error_t dfu_error = IRECV_E_SUCCESS;

	if (recovery_open_with_timeout(client) < 0 || dfu->mode != kDfuMode) {
		error("ERROR: Unable to connect to DFU device\n");
		if (dfu)
			irecv_close(dfu);
		return -1;
	}

	if (recovery_send_component(client, build_identity, component) < 0) {
		error("ERROR: Unable to send %s to device\n", component);
		irecv_close(dfu);
		return -1;
	}

	dfu_error = irecv_reset(client->dfu->client);
	if (dfu_error != IRECV_E_SUCCESS) {
		error("ERROR: Unable to reset device\n");
		irecv_close(dfu);
		return -1;
	}
	irecv_close(client->dfu->client);
	client->dfu->client = NULL;

	// Reconnect to device, but this time make sure we're not still in DFU mode
	if (recovery_open_with_timeout(client) < 0 || client->mode->index != kDfuMode) {
		error("ERROR: Unable to connect to recovery device\n");
		if (client->dfu->client)
			irecv_close(client->dfu->client);
		return -1;
	}

	client->mode = &idevicerestore_modes[MODE_RECOVERY];
	irecv_close(client->dfu->client);
	client->dfu->client = NULL;
	return 0;
}
*/
