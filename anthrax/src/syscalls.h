/**
  * GreenPois0n Anthrax - syscalls.h
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

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <sys/stat.h>
#include <sys/wait.h>

#define O_RDONLY        0x0000
#define O_WRONLY        0x0001
#define O_RDWR          0x0002
#define O_CREAT         0x0200
#define O_TRUNC         0x0400
#define O_EXCL          0x0800

void exit(int status);
int fork(void);
void sync(void);
int chdir(const char *path);
//int chmod(const char *path, int mode);
int chown(const char *path, int owner, int group);
int read(int fd, void* buf, unsigned int count);
int write(int fd, const void *buf, unsigned int count);
int open(const char* pathname, int flags, ...);
int close(int fd);
int unlink(const char* pathname);
int dup2(int oldfd, int newfd);
int stat(const char* path, struct stat* buf);
int reboot(int howto);
int mlock(const void* addr, unsigned int len);
int mkdir(const char* path, mode_t mode);
int rmdir(const char* path);
int mount(const char* filesystemtype, const char* target, int mountflags, void *source);
int unmount(const char* dir, int flags);
int access(const char *path, int mode);
int pread(int fildes, void *buf, int nbyte, int offset);
int pwrite(int fildes, const void *buf, int nbyte, int offset);
int wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);
int execve(const char *path, char *const argv[], char *const envp[]);
int chroot(const char *dirname);
int vfork(void);

#endif
