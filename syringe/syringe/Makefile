# /syringe/Makefile

SUBDIRS = exploits

MKSTATICLIB = 1

INCLUDES = ../include ../include/resources

SOURCES = \
	common.c		\
	libirecovery.c	\
	libpartial.c	\
	libpois0n.c		\
	libdioxin.c		\

XPLAT_CFLAGS = -O3 -DCURL_STATICLIB=1
PLAT_CFLAGS = 
XPLAT_LIBRARIES = curl z
PLAT_LIBRARIES =
XPLAT_PREMADE_OBJECTS = exploits/limera1n.o exploits/steaks4uce.o
PLAT_PREMADE_OBJECTS =

include ../platform.mk
ifeq ($(UNAME),Darwin)
	# OS X
	PLAT_CFLAGS = -mmacosx-version-min=10.6 -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk -framework IOKit
	PLAT_LIBRARIES =
	LDFLAGS = -fnested-functions -L/opt/local/lib -mmacosx-version-min=10.6 -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk
	ADDOBJ = ../lib-static/macosx/libusb-1.0.a ../lib-static/macosx/libplist.a ../lib-static/macosx/libimobiledevice.a ../lib-static/macosx/libgnutls.a ../lib-static/macosx/libgnutlsxx.a ../lib-static/macosx/libgpg-error.a ../lib-static/macosx/libusbmuxd.a ../lib-static/macosx/libgcrypt.a
else
	ifneq (,$(findstring MINGW32_NT,$(UNAME)))
		# Win32
		LDFLAGS =
		ADDOBJ = /mingw/lib/libcurl.a /mingw/lib/libwsock32.a /mingw/lib/libwldap32.a /mingw/lib/libpenwin32.a /mingw/lib/libz.a /mingw/lib/libsetupapi.a
	else
		# Linux
		PLAT_LIBRARIES = usb-1.0
		LDFLAGS = -L/opt/local/lib
	endif
endif
PREMADE_OBJECTS = $(XPLAT_PREMADE_OBJECTS) $(PLAT_PREMADE_OBJECTS)
LIBRARIES = $(XPLAT_LIBRARIES) $(PLAT_LIBRARIES)
CFLAGS = $(XPLAT_CFLAGS) $(PLAT_CFLAGS)

TARGET = syringe

include ../common.mk
