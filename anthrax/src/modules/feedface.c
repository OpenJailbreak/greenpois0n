/**
  * GreenPois0n Anthrax - feedface.c
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

#include "feedface.h"
#include "utils.h"

int feedface_install() {
    int ret;

    mkdir("/mnt/mnt", 0777);

    //feedface_uninstall();

    unlink("/mnt/usr/lib/hfs_mdb");
    unlink("/mnt/usr/lib/kern_sploit");
    //unlink("/mnt/usr/lib/libgmalloc.dylib");


    ret = install("/mnt/sbin/launchd", "/mnt/sbin/punchd", 0, 80, 0755);
    if (ret < 0) return -1;

    //unlink("/mnt/sbin/launchd");
    //ret = install("/files/punchd", "/mnt/sbin/launchd", 0, 80, 0755);
    if (ret < 0) return -1;

    ret = install("/files/feedface", "/mnt/usr/lib/kern_sploit", 0, 80, 0755);
    if (ret < 0) return -1;

    ret = install("/files/hfs_mdb", "/mnt/usr/lib/hfs_mdb", 0, 80, 0755);
    if (ret < 0) return -1;

    return 0;
}

int feedface_uninstall() {
    int ret = 0;

    unlink("/mnt/sbin/launchd");
    unlink("/mnt/usr/lib/hfs_mdb");
    unlink("/mnt/usr/lib/kern_sploit");

    ret = install("/mnt/sbin/punchd", "/mnt/sbin/launchd", 0, 80, 0755);
    if (ret < 0) return -1;

    return 0;
}

