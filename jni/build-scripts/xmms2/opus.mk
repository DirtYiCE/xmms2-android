include $(CLEAR_VARS)

OPUS_SOURCE := $(XMMS_PLUGINS)/opus

LOCAL_SRC_FILES := \
	$(OPUS_SOURCE)/opus.c \
	$(OPUS_SOURCE)/opusfile/http.c \
	$(OPUS_SOURCE)/opusfile/info.c \
	$(OPUS_SOURCE)/opusfile/internal.c \
	$(OPUS_SOURCE)/opusfile/opusfile.c \
	$(OPUS_SOURCE)/opusfile/stream.c

LOCAL_C_INCLUDES := $(OPUS_INCLUDES) $(LOCAL_PATH)/$(OPUS_SOURCE)/opusfile $(OGG_INCLUDE) $(GLIB_INCLUDES) $(XMMS_INCLUDES)
LOCAL_CFLAGS := -fPIC $(DEBUG_FLAG)

LOCAL_SHARED_LIBRARIES := glib-2.0 xmms2
LOCAL_STATIC_LIBRARIES := opuslib ogglib
LOCAL_MODULE := opus
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
