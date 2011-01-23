INCLUDES = ../include
SOURCES = $(TARGET).c

LIBRARIES = syringe usb-1.0 curl z
LDFLAGS = -L../syringe -L/opt/local/lib -framework CoreFoundation -framework IOKit

include ../common.mk