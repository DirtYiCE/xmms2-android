include $(CLEAR_VARS)

MAD_SOURCE := $(XMMS_PLUGINS)/mad

LOCAL_SRC_FILES := \
	$(MAD_SOURCE)/id3v1.c \
	$(MAD_SOURCE)/mad.c \
	$(MAD_SOURCE)/xing.c

LOCAL_C_INCLUDES := $(MAD_INCLUDES) $(GLIB_INCLUDES) $(XMMS_INCLUDES)
LOCAL_CFLAGS := -fPIC

LOCAL_SHARED_LIBRARIES := glib-2.0 xmms2 madlib
LOCAL_MODULE := mad
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
