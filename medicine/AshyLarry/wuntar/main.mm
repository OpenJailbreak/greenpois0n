#include <stdio.h>
#include <unistd.h>
#include "tar.h"

int main(int argc, char *argv[]) {
    setuid(0);

    if(argc < 3) {
	printf("%s <archive> <path>\n", argv[0]);
	printf("\nCopyright 2010 Nicolas Haunold.\n'tar.h' by Elliot Kroo.\n");
    }

    untar(argv[1], argv[2]);

    return 0;
}
