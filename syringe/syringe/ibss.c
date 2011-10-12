/**
 * GreenPois0n Syringe - ibss.c
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

#include "ibss.h"

ibss_t* ibss_create() {
	ibss_t* ibss = (ibss_t*)malloc(sizeof(ibss_t));
	if (!ibss) {
		return NULL;
	}
	memset(ibss, '\0', sizeof(ibss_t));
	return ibss;
}

ibss_t* ibss_open(char* path) {
	// TODO: Implement ibss_t open function
	return NULL;
}

ibss_t* ibss_download(char* url) {
	// TODO: Implement ibss_t download function
	return NULL;
}

ibss_t* ibss_load(unsigned char* data, unsigned int size) {
	// TODO: Implement ibss_t load function
	return NULL;
}

void ibss_free(ibss_t* ibss) {
	if(ibss) {
		free(ibss);
	}
}

#include "ibss.h"
