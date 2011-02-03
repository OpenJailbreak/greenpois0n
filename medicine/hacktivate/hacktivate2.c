/**
  * GreenPois0n Cynanide - functions.c
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
#include <unistd.h>
#include <mach/vm_map.h>
#include <mach/mach_init.h>

static unsigned char push = 0xB5;
static unsigned char push_r7_lr[] = { 0x80, 0xB5 };
static unsigned char push_r4_r7_lr[] = { 0x90, 0xB5 };
static unsigned char push_r4_to_r7_lr[] = { 0xF0, 0xB5 };
static unsigned char push_r4_r5_r7_lr[] = { 0xB0, 0xB5 };

void __attribute__((constructor)) initializer();
void __attribute__((destructor)) finalizer();

unsigned char* find_string(const char* name, unsigned char* data, unsigned int size) {
	unsigned int i = 0;
	unsigned int address = 0;
	unsigned int len = strlen(name);
	for(i = 0; i < size; i++) {
		if(!memcmp(&data[i], name, len)) {
			address = &data[i];
			break;
		}
	}
	return (unsigned char*) address;
}

unsigned int find_reference(unsigned int value, unsigned char* data, unsigned int size) {
	unsigned int i = 0;
	unsigned int address = 0;
	unsigned int reference = 0;
	for(i = 0; i < size; i++) {
		unsigned int
		reference =  *((unsigned int*) &data[i]);
		if(reference == value) {
			address = reference;
			break;
		}
	}
	return address;
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

void initializer() {
	printf("Hacktivation Initialized\n");
	unsigned char* string = find_string("dealwith_activation", 0x1000, 0x500000);
	if(string != NULL) {
		printf("Found search string at %p\n", string);
		unsigned int reference = find_reference((unsigned int) string, 0x1000, 0x50000);
		if(reference != 0) {
			printf("Found reference at 0x%08x\n", reference);
		} else {
			printf("Unable to find reference\n");
		}
	} else {
		printf("Unable to find string\n");
	}
}

