include $(CLEAR_VARS)

XMMS := $(LOCAL_PATH)/$(XMMS_TOP)

LOCAL_SRC_FILES := \
    service.c \
    $(XMMS_SOURCE)/xmms/fetchinfo.c \
    $(XMMS_SOURCE)/xmms/medialib_query.c \
    $(XMMS_SOURCE)/xmms/medialib_session.c \
    $(XMMS_SOURCE)/xmms/plugin.c \
    $(XMMS_SOURCE)/xmms/mediainfo.c \
    $(XMMS_SOURCE)/xmms/utils.c \
    $(XMMS_SOURCE)/xmms/ringbuf.c \
    $(XMMS_SOURCE)/xmms/compat/localtime_unix.c \
    $(XMMS_SOURCE)/xmms/xform_plugin.c \
    $(XMMS_SOURCE)/xmms/playlist.c \
    $(XMMS_SOURCE)/xmms/compat/checkroot_unix.c \
    $(XMMS_SOURCE)/xmms/bindata.c \
    $(XMMS_SOURCE)/xmms/ipc.c \
    $(XMMS_SOURCE)/xmms/medialib_query_result.c \
    $(XMMS_SOURCE)/xmms/medialib.c \
    $(XMMS_SOURCE)/xmms/metadata.c \
    $(XMMS_SOURCE)/xmms/object.c \
    $(XMMS_SOURCE)/xmms/xform.c \
    $(XMMS_SOURCE)/xmms/compat/statfs_linux.c \
    $(XMMS_SOURCE)/xmms/streamtype.c \
    $(XMMS_SOURCE)/xmms/compat/symlink_unix.c \
    $(XMMS_SOURCE)/xmms/fetchspec.c \
    $(XMMS_SOURCE)/lib/xmmsipc/transport.c \
    $(XMMS_SOURCE)/lib/xmmsipc/url.c \
    $(XMMS_SOURCE)/lib/xmmsipc/transport_unix.c \
    $(XMMS_SOURCE)/lib/xmmsipc/msg.c \
    $(XMMS_SOURCE)/lib/xmmsipc/socket_tcp.c \
    $(XMMS_SOURCE)/lib/xmmsipc/socket_unix.c \
    $(XMMS_SOURCE)/xmms/config.c \
    config/xmms2/compat/thread_name_prctl.c \
    $(XMMS_SOURCE)/xmms/outputplugin.c \
    $(XMMS_SOURCE)/xmms/playlist_updater.c \
    $(XMMS_SOURCE)/xmms/output.c \
    $(XMMS_SOURCE)/lib/xmmssocket/socket_common.c \
    $(XMMS_SOURCE)/lib/xmmssocket/socket_unix.c \
    $(XMMS_SOURCE)/xmms/segment_plugin.c \
    $(XMMS_SOURCE)/xmms/log.c \
    $(XMMS_SOURCE)/xmms/magic.c \
    $(XMMS_SOURCE)/xmms/collection.c \
    $(XMMS_SOURCE)/xmms/collsync.c \
    $(XMMS_SOURCE)/xmms/converter_plugin.c \
    $(XMMS_SOURCE)/xmms/compat/signal_unix.c \
    $(XMMS_SOURCE)/xmms/error.c \
    config/xmms2/sample.c \
    $(XMMS_SOURCE)/xmms/visualization/xform.c \
    $(XMMS_SOURCE)/xmms/visualization/object.c \
    $(XMMS_SOURCE)/xmms/visualization/dummy.c \
    $(XMMS_SOURCE)/lib/xmmsvisualization/timestamp.c \
    $(XMMS_SOURCE)/lib/xmmsvisualization/udp.c \
    $(XMMS_SOURCE)/xmms/visualization/format.c \
    $(XMMS_SOURCE)/xmms/visualization/udp.c

LOCAL_CFLAGS := -pthread -D_SEM_SEMUN_UNDEFINED $(DEBUG_FLAG)

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(GMODULE_INCLUDES) $(S4_INCLUDE) $(XMMS_INCLUDES)

LOCAL_SHARED_LIBRARIES := glib-2.0 gmodule-2.0 gthread-2.0
LOCAL_STATIC_LIBRARIES := s4 xmmstypes xmmsutils
LOCAL_MODULE := xmms2
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
