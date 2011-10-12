/**
 * GreenPois0n Syringe - syringe.c
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
#include <getopt.h>

#define _DEBUG
#include "debug.h"

static struct option longopts[] = {
	{ "help",         no_argument,         NULL,   'h' },
	{ "verbose",      no_argument,         NULL,   'v' },
	{ "ipsw",         required_argument,   NULL,   'i' },
	{ "url",          required_argument,   NULL,   'u' },
	{ "shatter",      no_argument,         NULL,   'x' },
	{ "limera1n",     no_argument,         NULL,   'l' },
	{ "steaks4uce",   no_argument,         NULL,   't' },
	{ "ibss",         required_argument,   NULL,   's' },
	{ "ibec",         required_argument,   NULL,   'c' },
	{ "iboot",        required_argument,   NULL,   'o' },
	{ "applelogo",    required_argument,   NULL,   'a' },
	{ "devicetree",   required_argument,   NULL,   'd' },
	{ "ramdisk",      required_argument,   NULL,   'r' },
	{ "kernelcache",  required_argument,   NULL,   'k' },
	{ "bootargs",     required_argument,   NULL,   'b' },
	{ NULL, 0, NULL, 0 }
};

void usage(int argc, char* argv[]) {
	// TODO: Clean up indents to the help messages are aligned
	char* name = strrchr(argv[0], '/');
	printf("Usage: %s [OPTIONS]\n", (name ? name + 1 : argv[0]));
	printf("Copyright 2010-2011, Chronic-Dev LLC\n");
	printf("Jailbreak Utility for iPhone/iPod/iPad using SecureROM exploits.\n");
	printf("  General\n");
	printf("    -h, --help\t\t\tprints usage information\n");
	printf("    -v, --verbose\t\tprint debuging info while running\n");
	printf("    -i, --ipsw FILE\t\t\tuse firmware files from this FILE\n");
	printf("    -u, --url URL\t\t\tuse firmware files from this URL\n");
	printf("\n");

	printf("  Exploiting\n");
	printf("    -x, --shatter\t\tuse SHAtter exploit (only A4 devices)\n");
	printf("    -l, --limera1n\t\tuse LimeRa1n exploit\n");
	printf("    -t, --steaks4uce\t\tuse SteakS4uce exploit (iPod2g only)\n");
	printf("\n");

	printf("  Loading\n");
	printf("    -s, --ibss FILE\t\tspecify iBSS to use\n");
	printf("    -c, --ibec FILE\t\tspecify iBEC to use\n");
	printf("    -o, --iboot FILE\t\tspecify iBoot to use\n");
	printf("    -a, --applelogo FILE\t\tspecify AppleLogo to use\n");
	printf("    -d, --devicetree FILE\t\tspecify DeviceTree to use\n");
	printf("\n");

	printf("  Booting\n");
	printf("    -r, --ramdisk FILE\t\tspecify ramdisk to boot with\n");
	printf("    -k, --kernelcache FILE\t\tspecify a kernel to boot with\n");
	printf("    -b, --bootargs ARGS\t\tspecify boot-args to be passed to kernel\n");
	printf("\n");
}
typedef enum {
	kExploitLimeRa1n,
	kExploitShatter,
	kExploitSteakS4uce,
	kExploitUnknown = -1
} exploit_t;

int main(int argc, char* argv[]) {
	int opt = 0;
	int optindex = 0;

	// General
	int verbose = 0;
	char* ipsw_path = NULL;
	char* ipsw_url = NULL;

	// Exploiting
	exploit_t* exploit = kExploitUnknown;

	// Loading
	char* ibss_path = NULL;
	char* ibec_path = NULL;
	char* iboot_path = NULL;
	char* applelogo_path = NULL;
	char* devicetree_path = NULL;

	// Booting
	char* bootargs = NULL;
	char* ramdisk_path = NULL;
	char* kernelcache_path = NULL;

	while ((opt = getopt_long(argc, argv, "hvxlti:u:s:c:o:a:d:r:k:b:", longopts, &optindex)) > 0) {
		switch (opt) {
		/////////////////////////////////////////
		/// General Options
		/// --help
		case 'h':
			usage(argc, argv);
			return 0;

		/// --verbose
		case 'v':
			verbose++;
			break;

		/// --ipsw
		case 'i':
			if(ipsw_url != NULL) {
				error("Unable to set both --ipsw and --url at the same time\n");
				usage(argc, argv);
				return -1;
			}
			ipsw_path = strdup(optarg);
			break;

		/// --url
		case 'u':
			if(ipsw_path != NULL) {
				error("Unable to set both --ipsw and --url at the same time\n");
				usage(argc, argv);
				return -1;
			}
			ipsw_url = strdup(optarg);
			break;

		/////////////////////////////////////////
		/// Exploiting Options
		/// --shatter
		case 'x':
			break;

		/// --limera1n
		case 'l':
			break;

		/// --steaks4uce
		case 't':
			break;

		/////////////////////////////////////////
		/// Loading Options
		/// --ibss
		case 's':
			ibss_path = strdup(optarg);
			break;

		/// --ibec
		case 'c':
			ibec_path = strdup(optarg);
			break;

		/// --iboot
		case 'o':
			iboot_path = strdup(optarg);
			break;

		/// --applelogo
		case 'a':
			applelogo_path = strdup(optarg);
			break;

		/// --devicetree
		case 'd':
			devicetree_path = strdup(optarg);
			break;

		/////////////////////////////////////////
		/// Booting Options
		/// --ramdisk
		case 'r':
			ramdisk_path = strdup(optarg);
			break;

		/// --kernelcache
		case 'k':
			kernelcache_path = strdup(optarg);
			break;

		/// --bootargs
		case 'b':
			bootargs = strdup(optarg);
			break;

		/////////////////////////////////////////
		/// Unknown Option
		default:
			usage(argc, argv);
			return -1;
		}
	}

	if ((argc-optind) == 0) {
		argc -= optind;
		argv += optind;

	} else {
		usage(argc, argv);
		return -1;
	}

	// TODO: Detect which device is attached
	// TODO: Detect which firmware version device is running
	// TODO: Choose which exploits to use for this device
	// TODO: Make sure device is in correct mode for exploit
	// TODO: Get iBSS from chosen source
	// TODO: Execute exploit module and wait for iBSS
	// TODO: Get iBEC from chosen source
	// TODO: Send iBEC and wait for reconnection
	// TODO: Download DeviceTree from chose source
	// TODO: Send DeviceTree

	// General Clean-up
	if(ipsw_url) free(ipsw_url);
	if(ipsw_path) free(ipsw_path);

	// Loading Clean-up
	if(ibss_path) free(ibss_path);
	if(ibec_path) free(ibec_path);
	if(applelogo_path) free(applelogo_path);
	if(devicetree_path) free(devicetree_path);

	// Booting Clean-up
	if(bootargs) free(bootargs);
	if(ramdisk_path) free(ramdisk_path);
	if(kernelcache_path) free(kernelcache_path);
	return 0;
}
