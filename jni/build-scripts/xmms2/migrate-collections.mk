include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(XMMS_SOURCE)/tools/migrate-collections/migrate-collections.c

LOCAL_CFLAGS := -pthread -D_SEM_SEMUN_UNDEFINED $(DEBUG_FLAG)

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(GMODULE_INCLUDES) $(S4_INCLUDE) $(XMMS_INCLUDES)

LOCAL_SHARED_LIBRARIES := glib-2.0 gthread-2.0
LOCAL_STATIC_LIBRARIES := xmmstypes xmmsutils
LOCAL_MODULE := migrate-collections
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
