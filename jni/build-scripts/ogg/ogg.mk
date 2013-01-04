include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(OGG_SOURCE)/framing.c \
	$(OGG_SOURCE)/bitwise.c

LOCAL_CFLAGS := -DHAVE_CONFIG_H -ffast-math -fsigned-char $(DEBUG_FLAG)
LOCAL_C_INCLUDES := $(OGG_INCLUDE) $(OGG_CONFIG)

LOCAL_MODULE := ogglib

include $(BUILD_STATIC_LIBRARY)
