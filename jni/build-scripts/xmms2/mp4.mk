include $(CLEAR_VARS)

MP4_SOURCE := $(XMMS_PLUGINS)/mp4

LOCAL_SRC_FILES := \
	$(MP4_SOURCE)/mp4ff/mp4atom.c \
	$(MP4_SOURCE)/mp4ff/mp4ff.c \
	$(MP4_SOURCE)/mp4ff/mp4meta.c \
	$(MP4_SOURCE)/mp4ff/mp4sample.c \
	$(MP4_SOURCE)/mp4ff/mp4tagupdate.c \
	$(MP4_SOURCE)/mp4ff/mp4util.c \
	$(MP4_SOURCE)/mp4.c

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(XMMS_INCLUDES) $(MP4_PLUGIN)/mp4ff/
LOCAL_CFLAGS := -fPIC -DUSE_TAGGING

LOCAL_SHARED_LIBRARIES := glib-2.0 xmms2
LOCAL_MODULE := mp4
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
