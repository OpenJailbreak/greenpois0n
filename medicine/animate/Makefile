SDKVERSION=4.2
GO_EASY_ON_ME = 1
include ../theos/makefiles/common.mk

TOOL_NAME = animate
animate_FILES = animate.mm
animate_FRAMEWORKS = Foundation CoreFoundation CoreGraphics IOKit
animate_PRIVATE_FRAMEWORKS = CoreSurface ImageIO IOMobileFramebuffer
animate_CFLAGS = -I.
animate_LDFLAGS = -undefined dynamic_lookup
animate_INSTALL_PATH = /

include $(FW_MAKEDIR)/tool.mk
