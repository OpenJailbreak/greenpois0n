/**
 * GreenPois0n Anthrax - afc2.c
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

#include "afc2.h"
#include "utils.h"

const char* afc2add[] = { "/afc2add", NULL };

int afc2_install() {
	int ret;

	ret = install("/files/afc2add", "/mnt/afc2add", 0, 80, 0755);
	if (ret < 0)
		return -1;
	fsexec(afc2add, cache_env, true);
	unlink("/mnt/afc2add");

	return 0;
}

int afc2_uninstall() {
	return -1;
}

