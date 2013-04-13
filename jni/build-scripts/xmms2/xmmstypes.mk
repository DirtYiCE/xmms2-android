include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(XMMS_SOURCE)/lib/xmmstypes/value_serialize.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xlist.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_bitbuffer.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_build.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_coll.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_copy.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_dict.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_general.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_list.c \
	$(XMMS_SOURCE)/lib/xmmstypes/xmmsv_util.c

LOCAL_CFLAGS := -pthread -DXMMSV_USE_INT64=1 -D_SEM_SEMUN_UNDEFINED $(DEBUG_FLAG)

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(GMODULE_INCLUDES) $(S4_INCLUDE) $(XMMS_INCLUDES)

LOCAL_SHARED_LIBRARIES := glib-2.0 gmodule-2.0 gthread-2.0

LOCAL_MODULE := xmmstypes
LOCAL_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)
