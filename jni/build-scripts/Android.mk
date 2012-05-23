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

XMMS_TOP := xmms2
XMMS_SOURCE := $(XMMS_TOP)/src
XMMS_CONFIG := $(LOCAL_PATH)/config/xmms2
XMMS_PLUGINS := $(XMMS_SOURCE)/plugins

XMMS_INCLUDES := \
                 $(XMMS_CONFIG) \
                 $(XMMS_CONFIG)/include \
				 $(LOCAL_PATH)/$(XMMS_SOURCE)/lib/xmmsipc \
                 $(LOCAL_PATH)/$(XMMS_SOURCE)/includepriv \
                 $(LOCAL_PATH)/$(XMMS_SOURCE)/include \
                 $(LOCAL_PATH)/$(XMMS_SOURCE)/xmms \
                 $(LOCAL_PATH)/$(XMMS_SOURCE) \
                 $(XMMS_CONFIG)/ipc

MAD_TOP := mad
MAD_SOURCE := $(MAD_TOP)
MAD_INCLUDES := $(LOCAL_PATH)/$(MAD_SOURCE)

S4_TOP := s4
S4 := $(LOCAL_PATH)/$(S4_TOP)
S4_INCLUDE := $(S4)/include

FLAC_TOP := flac
FLAC := $(LOCAL_PATH)/$(FLAC_TOP)
FLAC_SOURCE := $(FLAC_TOP)/src/libFLAC
FLAC_INCLUDE := $(FLAC)/include

OGG_TOP := ogg
OGG_SOURCE := $(OGG_TOP)/src
OGG_INCLUDE := $(LOCAL_PATH)/$(OGG_TOP)/include

TREMOR_TOP := tremor
TREMOR_SOURCE := $(TREMOR_TOP)

include $(BUILD_SCRIPTS_DIR)/iconv/iconv.mk
include $(BUILD_SCRIPTS_DIR)/glib/pcre.mk
include $(BUILD_SCRIPTS_DIR)/glib/glib.mk
include $(BUILD_SCRIPTS_DIR)/glib/gmodule.mk
include $(BUILD_SCRIPTS_DIR)/glib/gthread.mk
include $(BUILD_SCRIPTS_DIR)/s4/s4.mk
include $(BUILD_SCRIPTS_DIR)/flac/flac.mk
include $(BUILD_SCRIPTS_DIR)/mad/mad.mk
include $(BUILD_SCRIPTS_DIR)/ogg/ogg.mk
include $(BUILD_SCRIPTS_DIR)/tremor/tremor.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/xmms2.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/null.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/file.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/flac.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/mad.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/id3v2.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/tremor.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/android.mk
