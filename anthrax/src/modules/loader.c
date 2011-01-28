/**
 * GreenPois0n Anthrax - loader.c
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

#include "loader.h"
#include "utils.h"

int loader_install() {
	int ret;

	mkdir("/mnt/Applications/Loader.app", 0755);

	ret = install("/files/Loader.app/Bootstrap",
			"/mnt/Applications/Loader.app/Bootstrap", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/Loader",
			"/mnt/Applications/Loader.app/Loader", 0, 80, 06755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/cydia.png",
			"/mnt/Applications/Loader.app/cydia.png", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/cydia@2x.png",
			"/mnt/Applications/Loader.app/cydia@2x.png", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/Info.plist",
			"/mnt/Applications/Loader.app/Info.plist", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/icon.png",
			"/mnt/Applications/Loader.app/icon.png", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/icon@2x.png",
			"/mnt/Applications/Loader.app/icon@2x.png", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/icon-ipad.png",
			"/mnt/Applications/Loader.app/icon-ipad.png", 0, 80, 0755);
	if (ret < 0)
		return ret;

	ret = install("/files/Loader.app/PkgInfo",
			"/mnt/Applications/Loader.app/PkgInfo", 0, 80, 0755);
	if (ret < 0)
		return ret;

	return 0;
}

int loader_uninstall() {
	return -1;
}

