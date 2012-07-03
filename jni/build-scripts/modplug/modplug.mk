include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	$(MODPLUG_SOURCE)/sndmix.cpp \
	$(MODPLUG_SOURCE)/sndfile.cpp \
	$(MODPLUG_SOURCE)/snd_fx.cpp \
	$(MODPLUG_SOURCE)/snd_flt.cpp \
	$(MODPLUG_SOURCE)/snd_dsp.cpp \
	$(MODPLUG_SOURCE)/fastmix.cpp \
	$(MODPLUG_SOURCE)/mmcmp.cpp \
	$(MODPLUG_SOURCE)/load_xm.cpp \
	$(MODPLUG_SOURCE)/load_wav.cpp \
	$(MODPLUG_SOURCE)/load_umx.cpp \
	$(MODPLUG_SOURCE)/load_ult.cpp \
	$(MODPLUG_SOURCE)/load_stm.cpp \
	$(MODPLUG_SOURCE)/load_s3m.cpp \
	$(MODPLUG_SOURCE)/load_ptm.cpp \
	$(MODPLUG_SOURCE)/load_okt.cpp \
	$(MODPLUG_SOURCE)/load_mtm.cpp \
	$(MODPLUG_SOURCE)/load_mod.cpp \
	$(MODPLUG_SOURCE)/load_med.cpp \
	$(MODPLUG_SOURCE)/load_mdl.cpp \
	$(MODPLUG_SOURCE)/load_it.cpp \
	$(MODPLUG_SOURCE)/load_far.cpp \
	$(MODPLUG_SOURCE)/load_dsm.cpp \
	$(MODPLUG_SOURCE)/load_dmf.cpp \
	$(MODPLUG_SOURCE)/load_dbm.cpp \
	$(MODPLUG_SOURCE)/load_ams.cpp \
	$(MODPLUG_SOURCE)/load_amf.cpp \
	$(MODPLUG_SOURCE)/load_669.cpp \
	$(MODPLUG_SOURCE)/load_j2b.cpp \
	$(MODPLUG_SOURCE)/load_mt2.cpp \
	$(MODPLUG_SOURCE)/load_psm.cpp \
	$(MODPLUG_SOURCE)/load_abc.cpp \
	$(MODPLUG_SOURCE)/load_mid.cpp \
	$(MODPLUG_SOURCE)/load_pat.cpp \
	$(MODPLUG_SOURCE)/modplug.cpp

LOCAL_CFLAGS := -fPIC -DHAVE_CONFIG_H
LOCAL_C_INCLUDES := $(MODPLUG_INCLUDE) $(LOCAL_PATH)/$(MODPLUG_SOURCE)/libmodplug

LOCAL_MODULE := modpluglib 

include $(BUILD_STATIC_LIBRARY)
