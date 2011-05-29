CC=/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/arm-apple-darwin10-gcc-4.2.1
CFLAGS=-isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk/ -framework MobileKeyBag -O2 -F/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk/System/Library/PrivateFrameworks/

all: fixkeybag

fixkeybag: fixkeybag.c
		$(CC) $(CFLAGS) -o $@ $^
		ldid -S $@

clean:
		rm -f fixkeybag

rebuild: clean all
