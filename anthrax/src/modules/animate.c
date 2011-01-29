/**
 * GreenPois0n Anthrax - animate.c
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

#include "animate.h"
#include "utils.h"

static int animate_pid = 0;
const char* animate[] = { "/usr/bin/animate", NULL };

int animate_start() {
	int ret = 0;

	ret = install("/files/animate", "/mnt/usr/bin/animate", 0, 80, 0755);
	if(ret < 0) return -1;

	ret = fsexec(animate, cache_env, false);
	if(ret < 0) return -1;

	animate_pid = ret;
	return 0;
}

int animate_stop() {
	int ret = 0;
	//kill(animate_pid);
	unlink("/mnt/usr/bin/animate");
	return 0;
}
