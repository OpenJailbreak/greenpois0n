all:
	# afc2add
	make -C afc2add
	cp ./afc2add/obj/afc2add ../anthrax/files/

	#make -C animate

	make stage -C ashyLarry
	
	# capable
	make -C capable
	cp ./capable/obj/capable ../anthrax/files/

	make -C fixkeybag
	cp ./fixkeybag/fixkeybag ../anthrax/files/

	#make -C hacktivate 

	make -C hunnypot
	cp ./hunnypot/obj/installer ../anthrax/files/hunnypot/

	make -C immutable
	cp ./immutable/obj/immutable ../anthrax/files/

	make stage -C Loader
	cp -r Loader/_/Applications/Loader.app ../anthrax/files/

	make -C sachet
	cp ./sachet/obj/sachet ../anthrax/files/	

	#make -C activate
	
	#make -C whacktivate


clean:

	make clean -C afc2add
	rm -rf ../anthrax/files/afc2add

	make clean -C ashyLarry
	rm -rf ../anthrax/files/0.frappliance
	rm -rf ../anthrax/files/ashyLarry.frappliance
	rm -rf ../anthrax/files/wuntar
	rm -rf ../anthrax/files/pHelper

	make clean -C capable
	rm -rf ../anthrax/files/capable

	make clean -C fixkeybag
	rm -rf ../anthrax/files/fixkeybag

	make clean -C hunnypot
	rm -rf ../anthrax/files/hunnypot/installer

	make clean -C immutable
	rm -rf ../anthrax/files/immutable

	make clean -C loader
	rm -rf ../anthrax/files/Loader.app

	make clean -C sachet
	rm -rf ../anthrax/files/sachet