include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    $(XMMS_SOURCE)/lib/xmmsutils/stacktrace_dummy.c \
    $(XMMS_SOURCE)/lib/xmmsutils/strlist.c \
    config/xmms2/lib/xmmsutils/utils_android.c \
    $(XMMS_SOURCE)/lib/xmmsutils/utils.c

LOCAL_CFLAGS := -pthread -D_SEM_SEMUN_UNDEFINED $(DEBUG_FLAG)

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(GMODULE_INCLUDES) $(S4_INCLUDE) $(XMMS_INCLUDES)

LOCAL_SHARED_LIBRARIES := glib-2.0 gmodule-2.0 gthread-2.0

LOCAL_MODULE := xmmsutils
LOCAL_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)
