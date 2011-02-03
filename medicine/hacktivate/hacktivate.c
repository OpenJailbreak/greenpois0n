/**
 * GreenPois0n Medicine - hacktivate.c
 * Copyright (C) 2011 Chronic-Dev Team
 * Copyright (C) 2011 Joshua Hill
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
#include <unistd.h>
#include <mach/vm_map.h>
#include <mach/mach_init.h>

void __attribute__((constructor)) initializer();
void __attribute__((destructor)) finalizer();

unsigned char* find_fxn(const char* name, unsigned char* start, unsigned int size) {
	return NULL;
}

void patch_dword(void* offset, unsigned int value) {
	int page_size = getpagesize();
	int page = (unsigned int) offset / page_size;
	int address = page * page_size;
	vm_protect(mach_task_self(), address, page_size, 0,  0x13);
	*((volatile unsigned int*) &offset) = value;
	vm_protect(mach_task_self(), address, page_size, 0,  0x5);
}

void patch_word(void* offset, unsigned short value) {
	unsigned int page_size = getpagesize();
	int page = (unsigned int) offset / page_size;
	int address = page * page_size;
	vm_protect(mach_task_self(), address, page_size, 0,  0x13);
	*((volatile unsigned short*) &offset) = value;
	vm_protect(mach_task_self(), address, page_size, 0,  0x5);
}

const char search[] = "dealwith_activation";
void initializer() {
	printf("Hacktivation Initialized\n");
	unsigned char* string = find_fxn(search, 0x1000, sizeof(search));
	unsigned char* reference = find_fxn(string, 0x1000, sizeof(string));
	while(*((unsigned int*) &reference) != 0xE1A02001 && *((unsigned short*) &reference) != 0x460A) {
		reference -= 2;
	}
}
