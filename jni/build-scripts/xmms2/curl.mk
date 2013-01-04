include $(CLEAR_VARS)

CURL_SOURCE := $(XMMS_PLUGINS)/curl

LOCAL_SRC_FILES := \
	$(CURL_SOURCE)/curl_http.c

LOCAL_C_INCLUDES := $(CURL_INCLUDE) $(GLIB_INCLUDES) $(XMMS_INCLUDES)
LOCAL_CFLAGS := -fPIC $(DEBUG_FLAG)

LOCAL_SHARED_LIBRARIES := glib-2.0 xmms2
LOCAL_STATIC_LIBRARIES := curllib
LOCAL_MODULE := curl
LOCAL_LDLIBS := -llog -lz

include $(BUILD_SHARED_LIBRARY)
