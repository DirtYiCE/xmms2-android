include $(CLEAR_VARS)

SNDFILE_CONFIG := $(LOCAL_PATH)/config/sndfile

LOCAL_SRC_FILES := \
	$(SNDFILE_SOURCE)/common.c \
	$(SNDFILE_SOURCE)/file_io.c \
	$(SNDFILE_SOURCE)/command.c \
	$(SNDFILE_SOURCE)/pcm.c \
	$(SNDFILE_SOURCE)/ulaw.c \
	$(SNDFILE_SOURCE)/alaw.c \
	$(SNDFILE_SOURCE)/float32.c \
	$(SNDFILE_SOURCE)/double64.c \
	$(SNDFILE_SOURCE)/ima_adpcm.c \
	$(SNDFILE_SOURCE)/ms_adpcm.c \
	$(SNDFILE_SOURCE)/gsm610.c \
	$(SNDFILE_SOURCE)/dwvw.c \
	$(SNDFILE_SOURCE)/vox_adpcm.c \
	$(SNDFILE_SOURCE)/interleave.c \
	$(SNDFILE_SOURCE)/strings.c \
	$(SNDFILE_SOURCE)/dither.c \
	$(SNDFILE_SOURCE)/cart.c \
	$(SNDFILE_SOURCE)/broadcast.c \
	$(SNDFILE_SOURCE)/audio_detect.c \
	$(SNDFILE_SOURCE)/ima_oki_adpcm.c \
	$(SNDFILE_SOURCE)/alac.c \
	$(SNDFILE_SOURCE)/chunk.c \
	$(SNDFILE_SOURCE)/ogg.c \
	$(SNDFILE_SOURCE)/chanmap.c \
	$(SNDFILE_SOURCE)/windows.c \
	$(SNDFILE_SOURCE)/id3.c \
	$(SNDFILE_SOURCE)/sndfile.c \
	$(SNDFILE_SOURCE)/aiff.c \
	$(SNDFILE_SOURCE)/au.c \
	$(SNDFILE_SOURCE)/avr.c \
	$(SNDFILE_SOURCE)/caf.c \
	$(SNDFILE_SOURCE)/dwd.c \
	$(SNDFILE_SOURCE)/flac.c \
	$(SNDFILE_SOURCE)/g72x.c \
	$(SNDFILE_SOURCE)/htk.c \
	$(SNDFILE_SOURCE)/ircam.c \
	$(SNDFILE_SOURCE)/macbinary3.c \
	$(SNDFILE_SOURCE)/macos.c \
	$(SNDFILE_SOURCE)/mat4.c \
	$(SNDFILE_SOURCE)/mat5.c \
	$(SNDFILE_SOURCE)/nist.c \
	$(SNDFILE_SOURCE)/paf.c \
	$(SNDFILE_SOURCE)/pvf.c \
	$(SNDFILE_SOURCE)/raw.c \
	$(SNDFILE_SOURCE)/rx2.c \
	$(SNDFILE_SOURCE)/sd2.c \
	$(SNDFILE_SOURCE)/sds.c \
	$(SNDFILE_SOURCE)/svx.c \
	$(SNDFILE_SOURCE)/txw.c \
	$(SNDFILE_SOURCE)/voc.c \
	$(SNDFILE_SOURCE)/wve.c \
	$(SNDFILE_SOURCE)/w64.c \
	$(SNDFILE_SOURCE)/wav_w64.c \
	$(SNDFILE_SOURCE)/wav.c \
	$(SNDFILE_SOURCE)/xi.c \
	$(SNDFILE_SOURCE)/mpc2k.c \
	$(SNDFILE_SOURCE)/rf64.c \
	$(SNDFILE_SOURCE)/ogg_vorbis.c \
	$(SNDFILE_SOURCE)/ogg_speex.c \
	$(SNDFILE_SOURCE)/ogg_pcm.c \
	$(SNDFILE_SOURCE)/ogg_opus.c \
	$(SNDFILE_SOURCE)/GSM610/add.c \
	$(SNDFILE_SOURCE)/GSM610/code.c \
	$(SNDFILE_SOURCE)/GSM610/decode.c \
	$(SNDFILE_SOURCE)/GSM610/gsm_create.c \
	$(SNDFILE_SOURCE)/GSM610/gsm_decode.c \
	$(SNDFILE_SOURCE)/GSM610/gsm_destroy.c \
	$(SNDFILE_SOURCE)/GSM610/gsm_encode.c \
	$(SNDFILE_SOURCE)/GSM610/gsm_option.c \
	$(SNDFILE_SOURCE)/GSM610/long_term.c \
	$(SNDFILE_SOURCE)/GSM610/lpc.c \
	$(SNDFILE_SOURCE)/GSM610/preprocess.c \
	$(SNDFILE_SOURCE)/GSM610/rpe.c \
	$(SNDFILE_SOURCE)/GSM610/short_term.c \
	$(SNDFILE_SOURCE)/GSM610/table.c \
	$(SNDFILE_SOURCE)/G72x/g721.c \
	$(SNDFILE_SOURCE)/G72x/g723_16.c \
	$(SNDFILE_SOURCE)/G72x/g723_24.c \
	$(SNDFILE_SOURCE)/G72x/g723_40.c \
	$(SNDFILE_SOURCE)/G72x/g72x.c \
	$(SNDFILE_SOURCE)/ALAC/ALACBitUtilities.c \
	$(SNDFILE_SOURCE)/ALAC/ag_dec.c \
	$(SNDFILE_SOURCE)/ALAC/ag_enc.c \
	$(SNDFILE_SOURCE)/ALAC/dp_dec.c \
	$(SNDFILE_SOURCE)/ALAC/dp_enc.c \
	$(SNDFILE_SOURCE)/ALAC/matrix_dec.c \
	$(SNDFILE_SOURCE)/ALAC/matrix_enc.c \
	$(SNDFILE_SOURCE)/ALAC/alac_decoder.c \
	$(SNDFILE_SOURCE)/ALAC/alac_encoder.c

LOCAL_CFLAGS := -std=gnu99
LOCAL_C_INCLUDES := $(SNDFILE_CONFIG) $(SNDFILE_INCLUDES) $(LOCAL_PATH)/$(SNDFILE_SOURCE)

LOCAL_MODULE := sndfilelib

include $(BUILD_STATIC_LIBRARY)
