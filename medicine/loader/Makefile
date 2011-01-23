UNAME := $(shell uname -s)
SYSROOT=/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.2.sdk
ifeq ($(UNAME),Darwin)
GO_EASY_ON_ME=1
include theos/makefiles/common.mk

APPLICATION_NAME = Loader
TOOL_NAME = Bootstrap
Loader_FILES = main.m Callback.m MemLoaderOperation.m LoaderAppDelegate.mm LoaderVC.m
Bootstrap_FILES = Bootstrap.m
Bootstrap_INSTALL_PATH = /Applications/Loader.app/

#SUBPROJECTS = sachet capable afc2add

include $(FW_MAKEDIR)/application.mk
include $(FW_MAKEDIR)/tool.mk
include $(FW_MAKEDIR)/aggregate.mk

after-Loader-stage::
	$(FAKEROOT) chmod 6755 $(FW_SHARED_BUNDLE_RESOURCE_PATH)/Loader

copy:: stage
	#rm -rf ../ramdisk/files/Loader.app
	cp -R $(FW_STAGING_DIR)/Applications/Loader.app Loader.app
	#cp $(FW_STAGING_DIR)/sachet ../ramdisk/files/sachet
	#cp $(FW_STAGING_DIR)/capable ../ramdisk/files/capable
	#cp $(FW_STAGING_DIR)/afc2add ../ramdisk/files/afc2add
	
real-clean:
	rm -rf _
	rm -rf .obj
else
all clean:
	@echo "Skipping loader on windows"
	
stage copy real-clean:
	@echo "Nothing to do"
endif
