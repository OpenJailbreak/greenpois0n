/**
 * GreenPois0n Anthrax - sachet.c
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

#include "sachet.h"
#include "utils.h"

const char* sachet[] = { "/sachet", "/Applications/Loader.app", NULL };

int sachet_install() {
	int ret;

	ret = install("/files/sachet", "/mnt/sachet", 0, 80, 0755);
	if (ret < 0)
		return -1;
	fsexec(sachet, cache_env);
	unlink("/mnt/sachet");

	return 0;
}

int sachet_uninstall() {
	return -1;
}

