CFLAGS=-I../../syringe/include -I/opt/local/include -mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk
LDFLAGS=-L../../syringe/syringe -L/opt/local/lib -lsyringe -lcurl -lz -framework CoreFoundation -framework IOKit -framework Cocoa -mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk -Wl,-no_compact_linkedit

all:
	@echo "Building Mac OS X GUI"
	mkdir -p greenpois0n.app/Contents/MacOS
	$(CC) $(CFLAGS) $(LDFLAGS) main.m appFunctions.m -o greenpois0n.app/Contents/MacOS/greenpois0n ../../syringe/lib-static/macosx/libusb-1.0.a 
	
clean:
	@echo "Cleaning Mac OS X GUI"
	rm -rf greenpois0n.app/Contents/MacOS/greenpois0n
