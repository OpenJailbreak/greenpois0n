# /syringe/Makefile

SUBDIRS = exploits

MKSTATICLIB = 1

INCLUDES = ../include ../include/resources

SOURCES = \
	common.c		\
	libirecovery.c	\
	libpartial.c	\
	libpois0n.c		\

XPLAT_LIBRARIES = curl z
PLAT_LIBRARIES =
XPLAT_PREMADE_OBJECTS = exploits/limera1n.o exploits/steaks4uce.o
PLAT_PREMADE_OBJECTS =
ifeq ($(UNAME),Darwin)
	# OS X
	PLAT_LIBRARIES = usb-1.0
	LDFLAGS = -L/opt/local/lib
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
CFLAGS = -O3 -DCURL_STATICLIB=1

TARGET = syringe

include ../common.mk
