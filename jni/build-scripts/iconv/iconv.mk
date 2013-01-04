include $(CLEAR_VARS)

ICONV_SRC_DIR := $(ICONV_TOP)/lib

LOCAL_SRC_FILES := \
	$(ICONV_SRC_DIR)/iconv.c \
	$(ICONV_SRC_DIR)/relocatable.c \
	$(ICONV_TOP)/libcharset/lib/localcharset.c

LOCAL_CFLAGS := \
	-Wno-multichar \
	-D_ANDROID \
	-DLIBDIR=\"$(libdir)\" \
	-DBUILDING_LIBICONV \
	-DIN_LIBRARY \
	$(DEBUG_FLAG)

LOCAL_C_INCLUDES := $(ICONV_INCLUDES)

LOCAL_MODULE := iconv

include $(BUILD_STATIC_LIBRARY)
