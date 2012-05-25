include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(TREMOR_SOURCE)/res012.c \
	$(TREMOR_SOURCE)/floor0.c \
	$(TREMOR_SOURCE)/block.c \
	$(TREMOR_SOURCE)/mapping0.c \
	$(TREMOR_SOURCE)/sharedbook.c \
	$(TREMOR_SOURCE)/codebook.c \
	$(TREMOR_SOURCE)/synthesis.c \
	$(TREMOR_SOURCE)/mdct.c \
	$(TREMOR_SOURCE)/floor1.c \
	$(TREMOR_SOURCE)/vorbisfile.c \
	$(TREMOR_SOURCE)/window.c \
	$(TREMOR_SOURCE)/info.c \
	$(TREMOR_SOURCE)/registry.c

LOCAL_CFLAGS := -fPIC -DLITTLE_ENDIAN=1 -DBYTE_ORDER=1
LOCAL_C_INCLUDES := $(OGG_INCLUDE) $(LOCAL_PATH)/$(TREMOR_SOURCE)

LOCAL_STATIC_LIBRARIES := ogglib
LOCAL_MODULE := tremorlib

include $(BUILD_STATIC_LIBRARY)
