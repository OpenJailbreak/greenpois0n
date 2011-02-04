UNAME := $(shell uname -s)
INCLUDES = ../include
SOURCES = $(TARGET).c

XPLAT_LIBRARIES = syringe curl z
XPLAT_LDFLAGS = -L../syringe -L/opt/local/lib
ifeq ($(UNAME),Darwin)
	
	# OS X
	PLAT_LIBRARIES = usb-1.0
	PLAT_LDFLAGS = -framework CoreFoundation -framework IOKit
else
	ifneq (,$(findstring MINGW32_NT,$(UNAME)))
	
		# Win32
		PLAT_LIBRARIES = setupapi ws2_32
		PLAT_LDFLAGS =	
	else
	
		# Linux
		PLAT_LIBRARIES = usb-1.0
		PLAT_LDFLAGS =
	endif
endif

LIBRARIES = $(XPLAT_LIBRARIES) $(PLAT_LIBRARIES)
LDFLAGS = $(XPLAT_LDFLAGS) $(PLAT_LDFLAGS)

include ../common.mk