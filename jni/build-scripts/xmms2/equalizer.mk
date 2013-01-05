include $(CLEAR_VARS)

EQ_SOURCE := $(XMMS_PLUGINS)/equalizer

LOCAL_SRC_FILES := \
	$(EQ_SOURCE)/eq.c \
	$(EQ_SOURCE)/iir.c \
	$(EQ_SOURCE)/iir_cfs.c \
	$(EQ_SOURCE)/iir_fpu.c

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(XMMS_INCLUDES)
LOCAL_CFLAGS := -fPIC $(DEBUG_FLAG)

LOCAL_SHARED_LIBRARIES := glib-2.0 xmms2
LOCAL_MODULE := equalizer
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
