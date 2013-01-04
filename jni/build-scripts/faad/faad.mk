include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(FAAD_SOURCE)/bits.c \
	$(FAAD_SOURCE)/cfft.c \
	$(FAAD_SOURCE)/decoder.c \
	$(FAAD_SOURCE)/drc.c \
	$(FAAD_SOURCE)/drm_dec.c \
	$(FAAD_SOURCE)/error.c \
	$(FAAD_SOURCE)/filtbank.c \
	$(FAAD_SOURCE)/lt_predict.c \
	$(FAAD_SOURCE)/ic_predict.c \
	$(FAAD_SOURCE)/is.c \
	$(FAAD_SOURCE)/mdct.c \
	$(FAAD_SOURCE)/mp4.c \
	$(FAAD_SOURCE)/ms.c \
	$(FAAD_SOURCE)/output.c \
	$(FAAD_SOURCE)/pns.c \
	$(FAAD_SOURCE)/ps_dec.c \
	$(FAAD_SOURCE)/ps_syntax.c \
	$(FAAD_SOURCE)/pulse.c \
	$(FAAD_SOURCE)/specrec.c \
	$(FAAD_SOURCE)/syntax.c \
	$(FAAD_SOURCE)/tns.c \
	$(FAAD_SOURCE)/hcr.c \
	$(FAAD_SOURCE)/huffman.c \
	$(FAAD_SOURCE)/rvlc.c \
	$(FAAD_SOURCE)/ssr.c \
	$(FAAD_SOURCE)/ssr_fb.c \
	$(FAAD_SOURCE)/ssr_ipqf.c \
	$(FAAD_SOURCE)/common.c \
	$(FAAD_SOURCE)/sbr_dct.c \
	$(FAAD_SOURCE)/sbr_e_nf.c \
	$(FAAD_SOURCE)/sbr_fbt.c \
	$(FAAD_SOURCE)/sbr_hfadj.c \
	$(FAAD_SOURCE)/sbr_hfgen.c \
	$(FAAD_SOURCE)/sbr_huff.c \
	$(FAAD_SOURCE)/sbr_qmf.c \
	$(FAAD_SOURCE)/sbr_syntax.c \
	$(FAAD_SOURCE)/sbr_tf_grid.c \
	$(FAAD_SOURCE)/sbr_dec.c

LOCAL_CFLAGS := -fPIC -DHAVE_CONFIG_H -DFIXED_POINT -I$(FAAD_CONFIG)/libfaad -I- -I$(FAAD_CONFIG) -I$(LOCAL_PATH)/$(FAAD_TOP)/include -I$(LOCAL_PATH)/$(FAAD_SOURCE) $(DEBUG_FLAG)

LOCAL_MODULE := faadlib

include $(BUILD_STATIC_LIBRARY)
