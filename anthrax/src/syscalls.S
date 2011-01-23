/**
  * GreenPois0n Anthrax - syscalls.S
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

.text

.globl _exit
.globl _fork
.globl _read
.globl _write
.globl _open
.globl _close
.globl _unlink
.globl _chdir

.globl _mlock
.globl _mkdir
.globl _rmdir
.globl _unmount

.globl _chmod
.globl _chown
.globl _sync
.globl _kill
.globl _dup
.globl _symlink

.globl _chroot
.globl _vfork
.globl _reboot

.globl _dup2
.globl _mount
.globl _stat
.globl _pread
.globl _pwrite

.globl _access
.globl _wait4
.globl _execve


/* void exit(int status) */
_exit:
    mov    r12, #0x1
    swi    #0x80
    bx     lr
    
/* pid_t fork(void) */
_fork:
    mov    r12, #0x2
    swi    #0x80
    bx     lr
    
/* ssize_t read(int fd, void *buf, size_t count) */
_read:
    mov    r12, #0x3
    swi    #0x80
    bx     lr
    
/* ssize_t write(int fd, const void *buf, size_t count) */
_write:
    mov    r12, #0x4
    swi    #0x80
    bx     lr
    
/* int open(const char *pathname, int flags, mode_t mode) */
_open:
    mov    r12, #0x5
    swi    #0x80
    bx     lr

/* int close(int fd) */
_close:
    mov    r12, #0x6
    swi    #0x80
    bx     lr
    
/* int unlink(const char *pathname); */
_unlink:
    mov    r12, #0xA
    swi    #0x80
    bx     lr
    
/* int chdir(const char *path) */
_chdir:
    mov    r12, #0xC
    swi    #0x80
    bx     lr
    
/* int chmod(const char *path, int mode) */
_chmod:
    mov    r12, #0xF
    swi    #0x80
    bx     lr

/* int chown(const char *path, int owner, int group) */
_chown:
    mov    r12, #0x10
    swi    #0x80
    bx     lr

/* void sync(void) */
_sync:
    mov    r12, #0x24
    swi    #0x80
    bx     lr

/* int mlock(const void *addr, size_t len) */
_mlock:
    mov    r12, #0xCB
    swi    #0x80
    bx     lr

/* int mkdir(const char *path, mode_t mode) */
_mkdir:
    mov    r12, #0x88
    swi    #0x80
    bx     lr

/* int rmdir(const char *path) */
_rmdir:
    mov    r12, #0x89
    swi    #0x80
    bx     lr

/* int unmount(const char *dir, int flags) */
_unmount:
    mov    r12, #0x9F
    swi    #0x80
    bx     lr

/* int dup2(int oldfd, int newfd) */
_dup2:
    mov    r12, #0x5A
    swi    #0x80
    bx     lr

/* int stat(const char *path, struct stat *buf) */
_stat:
    mov    r12, #0xBC
    swi    #0x80
    bx     lr
    
/* int mount(const char *filesystemtype, const char *target, int mountflags, void *source) */
_mount:
    mov    r12, #0xA7
    swi    #0x80
    bx     lr
    
/* ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset) */
_pread:
    mov    r12, #0x99
    swi    #0x80
    bx     lr

/* ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset) */
_pwrite:
    mov    r12, #0x9A
    swi    #0x80
    bx     lr

/* int kill(pid_t pid, int sig) */
_kill:
    mov    r12, #0x25
    swi    #0x80
    bx     lr
    
/* int dup(int oldfd) */
_dup:
    mov    r12, #0x29
    swi    #0x80
    bx     lr
    
/* int symlink(const char *oldpath, const char *newpath) */
_symlink:
    mov    r12, #0x39
    swi    #0x80
    bx     lr
    
/* int chroot(const char *path) */
_chroot:
    mov    r12, #0x3D
    swi    #0x80
    bx     lr
    
/* pid_t vfork(void) */
_vfork:
	eor    r0, r0, r0
	mov    r12, #0x42
	swi    #0x80
	cmp    r1, #0x0
	beq    vfork_parent
	mov    r0, #0x0
vfork_parent:
	bx     lr

/* int reboot(int howto) */
_reboot:
    mov    r12, #0x37
    swi    #0x80
    bx     lr

/* access(const char *path, int amode) */
_access:
    mov    r12, #0x21
    swi    #0x80
    bx     lr

/* pid_t wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage) */
_wait4:
    mov    r12, #0x7
    swi    #0x80
    bx     lr

/* int execve(const char *path, char *const argv[], char *const envp[]) */
_execve:
    mov    r12, #0x3B
    swi    #0x80
    bx     lr
