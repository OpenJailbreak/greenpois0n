UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	OS_SHARED_EXT = .dylib
	OS_STATIC_EXT = .a
	OS_EXEC_EXT = 
else
	ifneq (,$(findstring MINGW32_NT,$(UNAME)))
		OS_SHARED_EXT = .dll
		OS_STATIC_EXT = .a
		OS_EXEC_EXT = .exe
	else
		OS_SHARED = .so
		OS_STATIC_EXT = .a
		OS_EXEC_EXT = 
	endif
endif