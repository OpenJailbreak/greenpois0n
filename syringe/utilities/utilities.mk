UNAME := $(shell uname -s)
INCLUDES = ../include
SOURCES = $(TARGET).c

XPLAT_CFLAGS = -O3
PLAT_CFLAGS =
XPLAT_LIBRARIES = syringe curl z xml2
XPLAT_LDFLAGS = -L../syringe
PLAT_LDFLAGS =
XPLAT_PREMADE_OBJECTS =
PLAT_PREMADE_OBJECTS =

include ../platform.mk
ifeq ($(UNAME),Darwin)
	# OS X
	PLAT_CFLAGS = -mmacosx-version-min=10.6 -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk -framework IOKit
	PLAT_LIBRARIES =
	PLAT_LDFLAGS = -L/opt/local/lib -framework CoreFoundation -framework IOKit -mmacosx-version-min=10.6 -arch i386 -isysroot /Developer/SDKs/MacOSX10.6.sdk -fnested-functions
	ADDOBJ = ../lib-static/macosx/libusb-1.0.a ../lib-static/macosx/libplist.a ../lib-static/macosx/libimobiledevice.a ../lib-static/macosx/libgnutls.a ../lib-static/macosx/libgnutlsxx.a ../lib-static/macosx/libgpg-error.a ../lib-static/macosx/libusbmuxd.a ../lib-static/macosx/libgcrypt.a
else
	ifneq (,$(findstring MINGW32_NT,$(UNAME)))
		# Win32
		PLAT_LIBRARIES =
		ADDOBJ = /mingw/lib/libcurl.a /mingw/lib/libwsock32.a /mingw/lib/libwldap32.a /mingw/lib/libpenwin32.a /mingw/lib/libz.a /mingw/lib/libsetupapi.a
	else
		# Linux
		PLAT_LIBRARIES = usb-1.0
		PLAT_LDFLAGS = -L/opt/local/lib
	endif
endif

PREMADE_OBJECTS = $(XPLAT_PREMADE_OBJECTS) $(PLAT_PREMADE_OBJECTS)
LIBRARIES = $(XPLAT_LIBRARIES) $(PLAT_LIBRARIES)
LDFLAGS = $(XPLAT_LDFLAGS) $(PLAT_LDFLAGS)
CFLAGS = $(XPLAT_CFLAGS) $(PLAT_CFLAGS)

include ../common.mk
