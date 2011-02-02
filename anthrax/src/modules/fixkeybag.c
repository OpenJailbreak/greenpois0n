/**
 * GreenPois0n Anthrax - fixkeybag.c
 * Copyright (C) 2011 Chronic-Dev Team
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
#include "fixkeybag.h"

const char* fixkeybag_params[] = { "/fixkeybag", NULL};

int fixkeybag_install() {
	int ret = 0;

	puts("- Installing fixkeybag\n");
	ret = install("/files/fixkeybag", "/mnt/fixkeybag", 0, 80, 0755);
	if (ret < 0) return ret;
	
    puts("- Running fixkeybag\n");

    fsexec(fixkeybag_params, cache_env, true);
	
    puts("- Removing fixkeybag\n");

    unlink("/mnt/fixkeybag");

	return 0;
}

int fixkeybag_uninstall() {
	return -1;
}

