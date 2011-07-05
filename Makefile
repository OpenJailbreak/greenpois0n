all:

	#make and convert latest firmware_2.plist to header and copy to syringe
	xxd -i firmware_2.plist syringe/include/firmware.h

	make -C medicine

	make -C cyanide
	cp -R ./cyanide/payloads ./syringe/include/
	
	make -C anthrax
	mkdir -p ./syringe/include/resources/
	cp ./anthrax/ramdisk.h ./syringe/include/resources/
	
	make -C syringe
	cp -a syringe/utilities/injectpois0n ./injectpois0n
	
	make -C doctors
	mkdir -p ./staging/doctor

clean:
	make clean -C medicine
	make clean -C cyanide
	make clean -C anthrax
	make clean_all -C syringe
	make clean -C doctors
	rm -rf injectpois0n syringe/utilities/injectpois0n