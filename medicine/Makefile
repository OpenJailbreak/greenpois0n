UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
	TARGET = macosx;
else
	ifeq ($(UNAME),MINGW32_NT-5.1)
		TARGET = windows
	else
		TARGET = linux
	endif
endif

all:
	make -C $(TARGET)

clean:
	make clean -C $(TARGET)