###
# GreenPois0n Anthrax - Makefile
# Copyright (C) 2010 Chronic-Dev Team
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###
 
RM = rm -rf
CP = cp
SYNC = sync
HDIUTIL = hdiutil
XPWNTOOL = xpwntool

LAUNCHD_TARGET = src/launchd
RAMDISK_TARGET = ramdisk.dmg
ENCRYPT_TARGET = ramdisk.img3


RAMDISK_LABEL=pois0ndisk
RAMDISK_VOLUME=/Volumes/$(RAMDISK_LABEL)

#******** Please fill these in for yourself *********
RAMDISK_IV=4445214ed192b6ccfe6953c6ae80c55e 
RAMDISK_KEY=7f50d391295747a06d03cdb2ae536fa089a368e473a470148f44750712c58105 
RAMDISK_TEMPLATE=018-7074-092.dmg

UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
	TARGETS = $(LAUNCHD_TARGET) $(RAMDISK_TARGET) $(ENCRYPT_TARGET)
else
	TARGETS =
endif

all: $(TARGETS)

clean:
	$(MAKE) -C src clean
	$(RM) ramdisk.img3 ramdisk.dmg

src/launchd:
	$(MAKE) -C src launchd

ramdisk.dmg: src/launchd
	$(CP) template.dmg ramdisk.dmg
	hfsplus ramdisk.dmg add src/launchd /sbin/launchd
	hfsplus ramdisk.dmg chmod 755 /sbin/launchd
	hfsplus ramdisk.dmg addall files/ /files


ramdisk.img3: ramdisk.dmg
	$(XPWNTOOL) ramdisk.dmg ramdisk.img3 -k $(RAMDISK_KEY) -iv $(RAMDISK_IV) -t $(RAMDISK_TEMPLATE)
	$(XPWNTOOL) ramdisk.img3 ramdisk.dmg -k $(RAMDISK_KEY) -iv $(RAMDISK_IV) -decrypt
	xxd -i ramdisk.dmg ramdisk.h
