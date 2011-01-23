/**
  * GreenPois0n Anthrax - utils.c
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Justin Williams
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
#include "syscalls.h"
#include "hfs_mount.h"

int console = 0;

int install(const char* src, const char* dst, int uid, int gid, int mode) {
	int ret = 0;

	ret = cp(src, dst);
	if (ret < 0) {
		return ret;
	}

	ret = chown(dst, uid, gid);
	if (ret < 0) {
		return ret;
	}

	ret = chmod(dst, mode);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

void sleep(unsigned int seconds) {
	int i = 0;
	for(i = seconds * 10000000; i > 0; i--) {}
}

void _puts(const char* s) {
	while((*s) != '\0') {
		write(1, s, 1);
		s++;
	}
	sync();
}

void _putc(const char c) {
	char byte[2] = { 0, 0 };
	byte[0] = c;
	write(1, byte, 1);
}

void puti(unsigned int integer) {
	int i = 0;
	char nyble = 0;

	for(i = 7; i >= 0; i--) {
		nyble = (integer >> (4 * i)) & 0xF;
		putc(nyble+0x30);
	}
}

int cp(const char *src, const char *dest) {
	int count = 0;
	char buf[0x800];
	struct stat status;

	while (stat(src, &status) != 0) {
		puts("Unable to find source file\n");
		return -1;
	}

	int in = open(src, O_RDONLY, 0);
	if (in < 0) {
		return -1;
	}

	int out = open(dest, O_WRONLY | O_CREAT, 0);
	if (out < 0) {
		close(in);
		return -1;
	}

	do {
		count = read(in, buf, 0x800);
		if (count > 0) {
			count = write(out, buf, count);
		}
	} while (count > 0);

	close(in);
	close(out);

	if (count < 0) {
		return -1;
	}

	return 0;
}

int hfs_mount(const char* device, const char* mountdir, int options) {
	struct hfs_mount_args args;
	args.fspec = device;
	return mount("hfs", mountdir, options, &args);
}

int fsexec(char* argv[], char* env[]) {
	if(vfork() != 0) {
		while(wait4(-1, NULL, WNOHANG, NULL) <= 0) {
			sleep(1);
		}
	} else {
		chdir("/mnt");
		if (chroot("/mnt") != 0) {
			return -1;
		}
		execve(argv[0], argv, env);
	}
	return 0;
}

int exec(char* argv[], char* env[]) {
	if(vfork() != 0) {
		while(wait4(-1, NULL, WNOHANG, NULL) <= 0) {
			sleep(1);
		}
	} else {
		execve(argv[0], argv, env);
	}
	return 0;
}

int _strlen(const char* s) {
	int i = 0;
	for(i = 0; i >= 0; i++) {
		if(s[i] == '\0') return i;
	}
	return -1;
}

void* memcpy(char* s1, const char* s2, int n) {
	int i = 0;
	for(i = 0; i < n; i++) {
		s1[i] = s2[i];
	}
	return s1;
}

void* memset(char *b, int c, int len) {
	int i = 0;
	for(i = 0; i < len; i++) {
		b[i] = c;
	}
}
