GO_EASY_ON_ME=1
FW_DEVICE_IP=apple-tv.local
include theos/makefiles/common.mk

BUNDLE_NAME = ashyLarry
ashyLarry_FILES = ashyLarryAppliance.mm P0isonedMenuLauncherController.m GPMedia.m GPProgressBarControl.m GPDownloadController.m GPMediaPreview.mm CPlusFunctions.mm
ashyLarry_INSTALL_PATH = /Applications/Lowtide.app/Appliances
ashyLarry_BUNDLE_EXTENSION = frappliance
ashyLarry_LDFLAGS = -undefined dynamic_lookup #-L$(FW_PROJECT_DIR) -lBackRow

SUBPROJECTS = wuntar pHelper beigelist

include $(FW_MAKEDIR)/aggregate.mk
include $(FW_MAKEDIR)/bundle.mk
include $(FW_MAKEDIR)/tool.mk

after-ashyLarry-stage:: 
	$(FAKEROOT) chmod 6755 $(FW_STAGING_DIR)/usr/bin/pHelper
	cp -R $(FW_STAGING_DIR)/Applications/Lowtide.app/Appliances/* ../../anthrax/files/
	cp -R $(FW_STAGING_DIR)/usr/bin/* ../../anthrax/files/