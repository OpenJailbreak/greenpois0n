CFLAGS=-I../../injector -I/opt/local/include #-mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk
LDFLAGS=-L../../injector -L/opt/local/lib -lpois0n -lusb-1.0 -lcurl -lz -framework CoreFoundation -framework IOKit -framework Cocoa #-mmacosx-version-min=10.5 -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk -Wl,-no_compact_linkedit

all:
	@echo "Building Mac OS X GUI"
	mkdir -p greenpois0n.app/Contents/MacOS
	$(CC) $(CFLAGS) $(LDFLAGS) main.m appFunctions.m -o greenpois0n.app/Contents/MacOS/greenpois0n
	install_name_tool -change /Users/nicolas/Downloads/libusb-1.0.8/build/lib/libusb-1.0.0.dylib @executable_path/../Frameworks/libusb-1.0.dylib greenpois0n.app/Contents/MacOS/greenpois0n
	
clean:
	@echo "Cleaning Mac OS X GUI"
	rm -rf greenpois0n.app/Contents/MacOS/greenpois0n
