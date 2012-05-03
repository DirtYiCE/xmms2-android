GLIB_TOP := glib
GLIB_CONFIG := $(CONFIG_PATH)/glib
ICONV_TOP := iconv

ICONV_INCLUDES := \
	$(LOCAL_PATH)/$(ICONV_TOP) \
	$(LOCAL_PATH)/$(ICONV_TOP)/include \
	$(LOCAL_PATH)/$(ICONV_TOP)/lib \
	$(CONFIG_PATH)/iconv

GLIB_INCLUDES := \
	$(LOCAL_PATH)/$(GLIB_TOP) \
	$(LOCAL_PATH)/$(GLIB_TOP)/glib \
	$(LOCAL_PATH)/$(GLIB_TOP)/glib/libcharset \
	$(LOCAL_PATH)/$(GLIB_TOP)/glib/gnulib \
	$(LOCAL_PATH)/$(GLIB_TOP)/glib/pcre \
	$(GLIB_CONFIG)

GMODULE_INCLUDES := \
	$(LOCAL_PATH)/$(GLIB_TOP)/gmodule


S4_TOP := s4
S4 := $(LOCAL_PATH)/$(S4_TOP)
S4_INCLUDE := $(S4)/include

include $(BUILD_SCRIPTS_DIR)/iconv/iconv.mk
include $(BUILD_SCRIPTS_DIR)/glib/pcre.mk
include $(BUILD_SCRIPTS_DIR)/glib/glib.mk
include $(BUILD_SCRIPTS_DIR)/glib/gmodule.mk
include $(BUILD_SCRIPTS_DIR)/glib/gthread.mk
include $(BUILD_SCRIPTS_DIR)/s4/s4.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/xmms2.mk
