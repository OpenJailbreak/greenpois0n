/**
 * GreenPois0n Anthrax - hacktivation.c
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

#include "utils.h"
#include "hacktivation.h"

int hacktivation_install() {
	int ret = 0;

	puts("- Installing whacktivate.dylib\n");
	ret = install("/files/whacktivate.dylib", "/mnt/usr/lib/whacktivate.dylib", 0, 80, 0755);
	if (ret < 0) return ret;

	// We should really back this plist up before replacing it
	puts("- Installing com.mobile.localdown.plist\n");
	ret = install("/files/com.apple.mobile.lockdown.plist", "/mnt/System/Library/LaunchDaemons/com.apple.mobile.lockdown.plist", 0, 0, 0644);
	if (ret < 0) return ret;

	return 0;
}

int hacktivation_uninstall() {
	puts("Uninstalling hacktivation...\n");
	unlink("/mnt/usr/lib/whacktivate.dylib");
	return -1;
}

