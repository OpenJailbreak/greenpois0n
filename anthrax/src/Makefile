###
# GreenPois0n Anthrax - src/Makefile
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
 
SDKVER = 4.2
PLATFORM = /Developer/Platforms/iPhoneOS.platform
SDK = $(PLATFORM)/Developer/SDKs/iPhoneOS$(SDKVER).sdk
CC = $(PLATFORM)/Developer/usr/bin/gcc-4.2
STRIP = $(PLATFORM)/Developer/usr/bin/strip
LDID = /usr/local/bin/ldid

TARGETS = $(LAUNCHD_TARGET)

# Setupp objects for launchd
LAUNCHD_TARGET = launchd
LAUNCHD_OBJECTS = launchd.o utils.o syscalls.o
LAUNCHD_CFLAGS = -arch armv6 -isysroot=$(SDK) -I$(SDK)/usr/include -static -nostartfiles -nodefaultlibs -nostdlib -Wl,-e,_main
LAUNCHD_LDFLAGS = 

PWD = $(shell pwd)

%.o: %.S
	$(CC) -c $(<) -o $(@) $(LAUNCHD_CFLAGS)

%.o: %.c
	$(CC) -c $(<) -o $(@) $(LAUNCHD_CFLAGS) 

all: $(TARGETS)

launchd: $(LAUNCHD_OBJECTS)
	$(CC) -o $(LAUNCHD_TARGET) $(LAUNCHD_OBJECTS) $(LAUNCHD_CFLAGS) $(LAUNCHD_LDFLAGS)
	$(STRIP) $(LAUNCHD_TARGET)
	ldid -S $(LAUNCHD_TARGET)
	
clean:
	rm -rf *.o launchd


