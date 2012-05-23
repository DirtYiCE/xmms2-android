include $(CLEAR_VARS)

OGG_CONFIG := $(LOCAL_PATH)/config/ogg

LOCAL_SRC_FILES := \
	$(OGG_SOURCE)/framing.c \
	$(OGG_SOURCE)/bitwise.c

LOCAL_CFLAGS := -DHAVE_CONFIG_H -ffast-math -fsigned-char
LOCAL_C_INCLUDES := $(OGG_INCLUDE) $(OGG_CONFIG)

LOCAL_MODULE := ogglib

include $(BUILD_SHARED_LIBRARY)
