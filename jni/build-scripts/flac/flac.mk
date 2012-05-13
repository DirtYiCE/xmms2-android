include $(CLEAR_VARS)

FLAC_CONFIG := $(LOCAL_PATH)/config/flac

LOCAL_SRC_FILES := \
	$(FLAC_SOURCE)/bitmath.c \
	$(FLAC_SOURCE)/bitreader.c \
	$(FLAC_SOURCE)/bitwriter.c \
	$(FLAC_SOURCE)/cpu.c \
	$(FLAC_SOURCE)/crc.c \
	$(FLAC_SOURCE)/fixed.c \
	$(FLAC_SOURCE)/float.c \
	$(FLAC_SOURCE)/format.c \
	$(FLAC_SOURCE)/lpc.c \
	$(FLAC_SOURCE)/md5.c \
	$(FLAC_SOURCE)/memory.c \
	$(FLAC_SOURCE)/metadata_iterators.c \
	$(FLAC_SOURCE)/metadata_object.c \
	$(FLAC_SOURCE)/stream_decoder.c \
	$(FLAC_SOURCE)/stream_encoder.c \
	$(FLAC_SOURCE)/stream_encoder_framing.c \
	$(FLAC_SOURCE)/window.c

LOCAL_CFLAGS := -DHAVE_CONFIG_H
LOCAL_C_INCLUDES := $(FLAC_INCLUDE) $(FLAC_CONFIG) $(LOCAL_PATH)/$(FLAC_SOURCE)/include

LOCAL_MODULE := flaclib

include $(BUILD_SHARED_LIBRARY)
