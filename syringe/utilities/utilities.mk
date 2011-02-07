UNAME := $(shell uname -s)
INCLUDES = ../include
SOURCES = $(TARGET).c

XPLAT_CFLAGS = -O3
PLAT_CFLAGS =
XPLAT_LIBRARIES = syringe curl z
XPLAT_LDFLAGS = -L../syringe
PLAT_LDFLAGS =
XPLAT_PREMADE_OBJECTS =
PLAT_PREMADE_OBJECTS =

include ../platform.mk
ifeq ($(UNAME),Darwin)
	# OS X
	PLAT_CFLAGS = -mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk
	PLAT_LIBRARIES = usb-1.0
	PLAT_LDFLAGS = -L/opt/local/lib -framework CoreFoundation -framework IOKit -mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk -Wl,-no_compact_linkedit
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
