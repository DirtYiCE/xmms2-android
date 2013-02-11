include $(CLEAR_VARS)

MUSEPACK_CONFIG := $(LOCAL_PATH)/config/musepack

LOCAL_SRC_FILES := \
	$(MUSEPACK_SOURCE)/common/crc32.c \
	$(MUSEPACK_SOURCE)/libmpcdec/huffman.c \
	$(MUSEPACK_SOURCE)/libmpcdec/mpc_decoder.c \
	$(MUSEPACK_SOURCE)/libmpcdec/mpc_reader.c \
	$(MUSEPACK_SOURCE)/libmpcdec/streaminfo.c \
	$(MUSEPACK_SOURCE)/libmpcdec/mpc_bits_reader.c \
	$(MUSEPACK_SOURCE)/libmpcdec/mpc_demux.c \
	$(MUSEPACK_SOURCE)/libmpcdec/requant.c \
	$(MUSEPACK_SOURCE)/libmpcdec/synth_filter.c

LOCAL_C_INCLUDES := $(MUSEPACK_INCLUDES)

LOCAL_MODULE := musepacklib

include $(BUILD_STATIC_LIBRARY)

