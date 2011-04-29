GO_EASY_ON_ME=1
SYSROOT:=/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk
include theos/makefiles/common.mk

BUNDLE_NAME = 0
0_FILES = vip.m nlist.cpp
0_INSTALL_PATH = /Applications/Lowtide.app/Appliances
0_BUNDLE_EXTENSION = frappliance
0_LDFLAGS = -undefined dynamic_lookup #-L$(FW_PROJECT_DIR) -lBackRow

include $(FW_MAKEDIR)/bundle.mk

after-0-stage:: 
	#cp -R $(FW_STAGING_DIR)/Applications/Lowtide.app/Appliances/0.frappliance ../../anthrax/files/0.frappliance