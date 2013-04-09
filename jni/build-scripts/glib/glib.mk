include $(CLEAR_VARS)

GLIB_DIR := $(GLIB_TOP)/glib

LOCAL_SRC_FILES := \
	$(GLIB_DIR)/libcharset/localcharset.c \
	$(GLIB_DIR)/deprecated/gallocator.c \
	$(GLIB_DIR)/deprecated/gcache.c \
	$(GLIB_DIR)/deprecated/gcompletion.c \
	$(GLIB_DIR)/deprecated/grel.c \
	$(GLIB_DIR)/deprecated/gthread-deprecated.c \
	$(GLIB_DIR)/garray.c \
	$(GLIB_DIR)/gasyncqueue.c \
	$(GLIB_DIR)/gatomic.c \
	$(GLIB_DIR)/gbacktrace.c \
	$(GLIB_DIR)/gbase64.c \
	$(GLIB_DIR)/gbitlock.c \
	$(GLIB_DIR)/gbookmarkfile.c \
	$(GLIB_DIR)/gbytes.c \
	$(GLIB_DIR)/gcharset.c \
	$(GLIB_DIR)/gchecksum.c \
	$(GLIB_DIR)/gconvert.c \
	$(GLIB_DIR)/gdataset.c \
	$(GLIB_DIR)/gdate.c \
	$(GLIB_DIR)/gdatetime.c \
	$(GLIB_DIR)/gdir.c \
	$(GLIB_DIR)/genviron.c \
	$(GLIB_DIR)/gerror.c \
	$(GLIB_DIR)/gfileutils.c \
	config/glib/ggettext.c \
	$(GLIB_DIR)/ghash.c \
	$(GLIB_DIR)/ghmac.c \
	$(GLIB_DIR)/ghook.c \
	$(GLIB_DIR)/ghostutils.c \
	$(GLIB_DIR)/giochannel.c \
	$(GLIB_DIR)/giounix.c \
	$(GLIB_DIR)/gkeyfile.c \
	$(GLIB_DIR)/glib-init.c \
	$(GLIB_DIR)/glib-private.c \
	$(GLIB_DIR)/glist.c \
	$(GLIB_DIR)/gmain.c \
	$(GLIB_DIR)/gmappedfile.c \
	$(GLIB_DIR)/gmarkup.c \
	$(GLIB_DIR)/gmem.c \
	$(GLIB_DIR)/gmessages.c \
	$(GLIB_DIR)/gnode.c \
	$(GLIB_DIR)/goption.c \
	$(GLIB_DIR)/gpattern.c \
	$(GLIB_DIR)/gpoll.c \
	$(GLIB_DIR)/gprimes.c \
	$(GLIB_DIR)/gqsort.c \
	$(GLIB_DIR)/gqueue.c \
	$(GLIB_DIR)/grand.c \
	$(GLIB_DIR)/gregex.c \
	$(GLIB_DIR)/gscanner.c \
	$(GLIB_DIR)/gsequence.c \
	$(GLIB_DIR)/gshell.c \
	$(GLIB_DIR)/gslice.c \
	$(GLIB_DIR)/gslist.c \
	$(GLIB_DIR)/gspawn.c \
	$(GLIB_DIR)/gstdio.c \
	config/glib/gstrfuncs.c \
	$(GLIB_DIR)/gstring.c \
	$(GLIB_DIR)/gstringchunk.c \
	$(GLIB_DIR)/gtestutils.c \
	$(GLIB_DIR)/gthread.c \
	$(GLIB_DIR)/gthreadpool.c \
	$(GLIB_DIR)/gtimer.c \
	$(GLIB_DIR)/gtimezone.c \
	$(GLIB_DIR)/gtrashstack.c \
	$(GLIB_DIR)/gtree.c \
	$(GLIB_DIR)/guniprop.c \
	$(GLIB_DIR)/gutf8.c \
	$(GLIB_DIR)/gunibreak.c \
	$(GLIB_DIR)/gunicollate.c \
	$(GLIB_DIR)/gunidecomp.c \
	$(GLIB_DIR)/gurifuncs.c \
	$(GLIB_DIR)/gutils.c \
	$(GLIB_DIR)/gvariant.c \
	$(GLIB_DIR)/gvariant-core.c \
	$(GLIB_DIR)/gvariant-parser.c \
	$(GLIB_DIR)/gvariant-serialiser.c \
	$(GLIB_DIR)/gvarianttypeinfo.c \
	$(GLIB_DIR)/gvarianttype.c \
	$(GLIB_DIR)/gversion.c \
	$(GLIB_DIR)/gwakeup.c \
	$(GLIB_DIR)/gprintf.c \
	$(GLIB_DIR)/glib-unix.c \
	$(GLIB_DIR)/gthread-posix.c

LOCAL_MODULE := glib-2.0
LOCAL_STATIC_LIBRARIES := pcre iconv

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(ICONV_INCLUDES)

LOCAL_CFLAGS := \
	-DLIBDIR=\"$(libdir)\" \
	-DHAVE_CONFIG_H \
	-DG_LOG_DOMAIN=\"Glib\" \
	-DSUPPORT_UCP \
	-DSUPPORT_UTF8 \
	-DNEWLINE=-1 \
	-DMATCH_LIMIT=10000000 \
	-DMATCH_LIMIT_RECURSION=10000000 \
	-DMAX_NAME_SIZE=32 \
	-DMAX_NAME_COUNT=1000 \
	-DMAX_DUPLENGTH=30000 \
	-DLINK_SIZE=2 \
	-DEBCDIC=0 \
	-DPOSIX_MALLOC_THRESHOLD=10 \
	-DGLIB_COMPILATION \
	$(DEBUG_FLAG)

include $(BUILD_SHARED_LIBRARY)
