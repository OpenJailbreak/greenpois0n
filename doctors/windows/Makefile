CC = gcc
UNAME := $(shell uname -s)

CFLAGS = -O3 -DCURL_STATICLIB -DWINVER=0x0501 -std=gnu99 -m32 -mwindows -DUSE_POIS0N
LDFLAGS =
ADDOBJ = ../../injector/libpois0n.a /mingw/lib/libcurl.a /mingw/lib/libwsock32.a /mingw/lib/libwldap32.a /mingw/lib/libz.a /mingw/lib/libsetupapi.a /mingw/lib/libcomctl32.a

all: wingui.c wingui.rc
	echo "Building Win32 Interface"
	windres wingui.rc -O coff -o wingui.res
	$(CC) $(CFLAGS) $(LDFLAGS) -o wingui.exe wingui.c wingui.res $(ADDOBJ)
	
clean:
	echo "Cleaning Win32 Interface"
	rm -rf *.o wingui.exe