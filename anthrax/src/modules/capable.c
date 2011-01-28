/**
 * GreenPois0n Anthrax - capable.c
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

#include "capable.h"
#include "utils.h"

const char* capable[] = { "/capable", "K48AP", "hide-non-default-apps", NULL };

int capable_install() {
	int ret;

	if (access("/mnt/System/Library/CoreServices/SpringBoard.app/K48AP.plist",
			0) == 0) {
		ret = install("/files/capable", "/mnt/capable", 0, 80, 0755);
		if (ret < 0)
			return -1;
		fsexec(capable, cache_env, true);
		unlink("/mnt/capable");

		return 0;
	}

	return -1;
}

int capable_uninstall() {
	return -1;
}

