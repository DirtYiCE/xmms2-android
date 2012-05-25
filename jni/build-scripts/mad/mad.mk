include $(CLEAR_VARS)

MAD_CONFIG := $(LOCAL_PATH)/config/mad

LOCAL_SRC_FILES := \
	$(MAD_SOURCE)/bit.c \
	$(MAD_SOURCE)/decoder.c \
	$(MAD_SOURCE)/fixed.c \
	$(MAD_SOURCE)/frame.c \
	$(MAD_SOURCE)/huffman.c \
	$(MAD_SOURCE)/layer12.c \
	$(MAD_SOURCE)/layer3.c \
	$(MAD_SOURCE)/minimad.c \
	$(MAD_SOURCE)/stream.c \
	$(MAD_SOURCE)/synth.c \
	$(MAD_SOURCE)/timer.c \
	$(MAD_SOURCE)/version.c

LOCAL_CFLAGS := -DFPM_DEFAULT -DHAVE_CONFIG_H -fPIC
LOCAL_C_INCLUDES := $(MAD_CONFIG) $(MAD_INCLUDES)

LOCAL_MODULE := madlib

include $(BUILD_STATIC_LIBRARY)
