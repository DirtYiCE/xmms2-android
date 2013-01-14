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

OPUS_TOP := opus
OPUS_SOURCE := $(OPUS_TOP)
OPUS_INCLUDES := $(LOCAL_PATH)/$(OPUS_SOURCE)/include

S4_TOP := s4
S4 := $(LOCAL_PATH)/$(S4_TOP)
S4_INCLUDE := $(S4)/include

FLAC_TOP := flac
FLAC := $(LOCAL_PATH)/$(FLAC_TOP)
FLAC_SOURCE := $(FLAC_TOP)/src/libFLAC
FLAC_INCLUDE := $(FLAC)/include

OGG_TOP := ogg
OGG_SOURCE := $(OGG_TOP)/src
OGG_CONFIG := $(LOCAL_PATH)/config/ogg
OGG_INCLUDE := $(LOCAL_PATH)/$(OGG_TOP)/include $(OGG_CONFIG)/include

TREMOR_TOP := tremor
TREMOR_SOURCE := $(TREMOR_TOP)

FAAD_TOP := faad
FAAD_SOURCE := $(FAAD_TOP)/libfaad
FAAD_CONFIG := $(LOCAL_PATH)/config/faad
FAAD_INCLUDE := $(LOCAL_PATH)/$(FAAD_TOP)/include $(FAAD_CONFIG)

CURL_TOP := curl
CURL_SOURCE := $(CURL_TOP)/lib
CURL_CONFIG := $(LOCAL_PATH)/config/curl
CURL_INCLUDE := $(LOCAL_PATH)/$(CURL_TOP)/include $(CURL_CONFIG) $(CURL_CONFIG)/curl

MODPLUG_TOP := modplug/libmodplug
MODPLUG_SOURCE := $(MODPLUG_TOP)/src
MODPLUG_CONFIG := $(LOCAL_PATH)/config/modplug
MODPLUG_INCLUDE := $(LOCAL_PATH)/$(MODPLUG_SOURCE) $(MODPLUG_CONFIG)

include $(BUILD_SCRIPTS_DIR)/iconv/iconv.mk
include $(BUILD_SCRIPTS_DIR)/glib/pcre.mk
include $(BUILD_SCRIPTS_DIR)/glib/glib.mk
include $(BUILD_SCRIPTS_DIR)/glib/gmodule.mk
include $(BUILD_SCRIPTS_DIR)/glib/gthread.mk
include $(BUILD_SCRIPTS_DIR)/s4/s4.mk
include $(BUILD_SCRIPTS_DIR)/flac/flac.mk
ifneq ($(APP_ABI),x86)
include $(BUILD_SCRIPTS_DIR)/curl/curl.mk
include $(BUILD_SCRIPTS_DIR)/faad/faad.mk  # disabled, super slow
endif
include $(BUILD_SCRIPTS_DIR)/mad/mad.mk
include $(BUILD_SCRIPTS_DIR)/ogg/ogg.mk
include $(BUILD_SCRIPTS_DIR)/modplug/modplug.mk
include $(BUILD_SCRIPTS_DIR)/tremor/tremor.mk
include $(BUILD_SCRIPTS_DIR)/opus/opus.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/xmms2.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/file.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/flac.mk
ifneq ($(APP_ABI),x86)
include $(BUILD_SCRIPTS_DIR)/xmms2/faad.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/curl.mk
endif
include $(BUILD_SCRIPTS_DIR)/xmms2/mad.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/id3v2.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/tremor.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/modplug.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/android.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/icymetaint.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/mp4.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/equalizer.mk
include $(BUILD_SCRIPTS_DIR)/xmms2/opus.mk
