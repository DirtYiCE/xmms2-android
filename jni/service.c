#include <jni.h>
#include "xmms_configuration.h"
#include "xmmsc/xmmsc_util.h"
#include "xmmspriv/xmms_plugin.h"
#include "xmmspriv/xmms_config.h"
#include "xmmspriv/xmms_playlist.h"
#include "xmmspriv/xmms_playlist_updater.h"
#include "xmmspriv/xmms_collsync.h"
#include "xmmspriv/xmms_collection.h"
#include "xmmspriv/xmms_signal.h"
#include "xmmspriv/xmms_symlink.h"
#include "xmmspriv/xmms_checkroot.h"
#include "xmmspriv/xmms_thread_name.h"
#include "xmmspriv/xmms_medialib.h"
#include "xmmspriv/xmms_mediainfo.h"
#include "xmmspriv/xmms_output.h"
#include "xmmspriv/xmms_ipc.h"
#include "xmmspriv/xmms_log.h"
#include "xmmspriv/xmms_xform.h"
#include "xmmspriv/xmms_bindata.h"
#include "xmmspriv/xmms_utils.h"

static void JNICALL start_service (JNIEnv *env, jclass thiz);

static JNINativeMethod methods[] = {
	{"start", "()V", start_service}
};

JavaVM *global_jvm;

static const gchar *conffile = NULL;

jint
JNI_OnLoad (JavaVM *vm, void *reserved)
{
	JNIEnv *env = NULL;
	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
		return -1;  /* fail */
	}

	jclass clazz = (*env)->FindClass (env, "org.xmms2.server.Server");
	(*env)->RegisterNatives (env, clazz, methods,
	                         sizeof(methods)/sizeof(methods[0]));

	xmms_log_info("Load successful!");

	global_jvm = vm;

	return JNI_VERSION_1_6;
}

static void JNICALL
start_service (JNIEnv *env, jclass thiz)
{
	gchar configdir[XMMS_PATH_MAX];
	int loglevel = 1;

	g_thread_init (NULL);

	g_random_set_seed (time (NULL));

	xmms_log_init (loglevel);
	xmms_log_info("starting...");

	conffile = XMMS_BUILD_PATH ("xmms2.conf");
	xmms_log_debug("conf file: %s", conffile);

	//xmms_ipc_init ();
}
