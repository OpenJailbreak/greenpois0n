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

