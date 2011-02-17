/**
 * GreenPois0n Anthrax - hunnypot.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 pod2g
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
// thx to comex for hunnypot iBooks DRM fix

#include "hunnypot.h"
#include "utils.h"

const char* command[] = { "/installer", NULL, NULL };

int hunnypot_install() {
	int ret;

	ret = install("/files/hunnypot/hunnypot.dylib", "/mnt/usr/lib/hunnypot.dylib", 0, 80, 0755);
	if (ret < 0) {
		puts("Can't install hunnypot.dylib.\n");
		return -1;
	}
	
	ret = install("/files/hunnypot/installer", "/mnt/installer", 0, 80, 0755);
	if (ret < 0) {
		puts("Can't install hunnypot installer command.\n");
		return -1;
	}

	fsexec(command, cache_env, true);
	unlink("/mnt/installer");

	return 0;
}

int hunnypot_uninstall() {
	return -1;
}

