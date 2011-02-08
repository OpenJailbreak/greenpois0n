GO_EASY_ON_ME=1
FW_DEVICE_IP=apple-tv.local
export SDKVERSION=4.2
TOOL_NAME := pHelper
pHelper_FILES = pHelper.m pHelperClass.m
pHelper_PACKAGE_TARGET_DIR = /usr/bin
pHelper_LDFLAGS = -framework Foundation #-framework BackRow

include theos/makefiles/common.mk
include theos/makefiles/tool.mk

after-pHelper-stage::
	$(FAKEROOT) chmod 6755 $(FW_STAGING_DIR)/usr/bin/pHelper
	$(FAKEROOT) cp $(FW_STAGING_DIR)/usr/bin/pHelper ../layout/usr/bin/pHelper
	$(FAKEROOT) chmod 6755 ../layout/usr/bin/pHelper