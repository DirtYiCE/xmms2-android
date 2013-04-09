include $(CLEAR_VARS)

PCRE_DIR := $(GLIB_TOP)/glib/pcre

LOCAL_SRC_FILES := \
	$(PCRE_DIR)/pcre_byte_order.c \
	$(PCRE_DIR)/pcre_chartables.c \
	$(PCRE_DIR)/pcre_compile.c \
	$(PCRE_DIR)/pcre_config.c \
	$(PCRE_DIR)/pcre_dfa_exec.c \
	$(PCRE_DIR)/pcre_exec.c \
	$(PCRE_DIR)/pcre_fullinfo.c \
	$(PCRE_DIR)/pcre_get.c \
	$(PCRE_DIR)/pcre_globals.c \
	$(PCRE_DIR)/pcre_jit_compile.c \
	$(PCRE_DIR)/pcre_newline.c \
	$(PCRE_DIR)/pcre_ord2utf8.c \
	$(PCRE_DIR)/pcre_string_utils.c \
	$(PCRE_DIR)/pcre_study.c \
	$(PCRE_DIR)/pcre_tables.c \
	$(PCRE_DIR)/pcre_valid_utf8.c \
	$(PCRE_DIR)/pcre_xclass.c

LOCAL_MODULE := pcre
LOCAL_C_INCLUDES := $(GLIB_INCLUDES)
LOCAL_CFLAGS := \
	-DG_LOG_DOMAIN=\"GLib-GRegex\" \
	-DSUPPORT_UCP \
	-DSUPPORT_UTF8 \
	-DNEWLINE=-1 \
	-DMATCH_LIMIT=10000000 \
	-DMATCH_LIMIT_RECURSION=8192 \
	-DMAX_NAME_SIZE=32 \
	-DMAX_NAME_COUNT=10000 \
	-DMAX_DUPLENGTH=30000 \
	-DLINK_SIZE=2 \
	-DPOSIX_MALLOC_THRESHOLD=10 \
	-DPCRE_STATIC \
	-DGLIB_COMPILATION \
	$(DEBUG_FLAG)

include $(BUILD_STATIC_LIBRARY)
