/**
 * GreenPois0n Medicine - wactive.c
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

#include <unistd.h>
#include <sys/sysctl.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define DEVICE "N88DEV"
#define SIZE 6

int my_sysctlbyname(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
	if(strcmp(name, "hw.model") == 0 && oldp != NULL) {
		memcpy(oldp, DEVICE, SIZE);
		return 0;
	}

	return sysctlbyname(name, oldp, oldlenp, newp, newlen);;
}


const struct {void *n; void *o;} interposers[] __attribute((section("__DATA, __interpose"))) = {
	{ (void *)my_sysctlbyname, (void *)sysctlbyname }
};


// vim:ft=c

