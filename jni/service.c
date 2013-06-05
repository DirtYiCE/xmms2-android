#include <jni.h>

#include <xmms_configuration.h>
#include <xmmsc/xmmsc_util.h>
#include <xmmspriv/xmms_plugin.h>
#include <xmmspriv/xmms_config.h>
#include <xmmspriv/xmms_playlist.h>
#include <xmmspriv/xmms_playlist_updater.h>
#include <xmmspriv/xmms_collsync.h>
#include <xmmspriv/xmms_collection.h>
#include <xmmspriv/xmms_signal.h>
#include <xmmspriv/xmms_symlink.h>
#include <xmmspriv/xmms_checkroot.h>
#include <xmmspriv/xmms_thread_name.h>
#include <xmmspriv/xmms_medialib.h>
#include <xmmspriv/xmms_mediainfo.h>
#include <xmmspriv/xmms_output.h>
#include <xmmspriv/xmms_ipc.h>
#include <xmmspriv/xmms_log.h>
#include <xmmspriv/xmms_xform.h>
#include <xmmspriv/xmms_bindata.h>
#include <xmmspriv/xmms_utils.h>
#include <xmmspriv/xmms_visualization.h>

#include <glib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * Forward declarations of the methods in the main object
 */
static void xmms_main_client_quit (xmms_object_t *object, xmms_error_t *error);
static xmmsv_t *xmms_main_client_stats (xmms_object_t *object, xmms_error_t *error);
static xmmsv_t *xmms_main_client_list_plugins (xmms_object_t *main, gint32 type, xmms_error_t *err);
static void xmms_main_client_hello (xmms_object_t *object, gint protocolver, const gchar *client, xmms_error_t *error);

#include "main_ipc.c"

static void JNICALL start_service (JNIEnv *env, jobject thiz);
static void JNICALL quit (JNIEnv *env, jobject thiz);
static void JNICALL playback_play (JNIEnv *env, jobject thiz);
static void JNICALL playback_pause (JNIEnv *env, jobject thiz);

static JNINativeMethod methods[] = {
	{"start", "()V", start_service},
	{"quit", "()V", quit},
	{"play", "()V", playback_play},
	{"pause", "()V", playback_pause},
};

JavaVM *global_jvm;
jobject server_object;

typedef struct {
	jclass server_class;
	jmethodID plugin_path_get;
	jmethodID server_ready;
	jmethodID browse_root;

	jobject status_handler;
	jmethodID update_status;
} xmms_main_java_cache_t;

/**
 * Main object, when this is unreffed, XMMS2 is quiting.
 */
struct xmms_main_St {
	xmms_object_t object;
	xmms_output_t *output_object;
	xmms_bindata_t *bindata_object;
	xmms_coll_dag_t *colldag_object;
	xmms_medialib_t *medialib_object;
	xmms_playlist_t *playlist_object;
	xmms_coll_sync_t *collsync_object;
	xmms_playlist_updater_t *plsupdater_object;
	xmms_xform_object_t *xform_object;
	xmms_mediainfo_reader_t *mediainfo_object;
	xmms_visualization_t *visualization_object;

	xmms_main_java_cache_t *java_cache;
	time_t starttime;
};

typedef struct xmms_main_St xmms_main_t;

static xmms_main_t *mainobj;

/** This is the mainloop of the xmms2 server */
static GMainLoop *mainloop;

static const gchar *conffile = NULL;

/**
 * This returns the main stats for the server
 */
static xmmsv_t *
xmms_main_client_stats (xmms_object_t *object, xmms_error_t *error)
{
	xmms_main_t *mainobj = (xmms_main_t *) object;
	gint uptime = time (NULL) - mainobj->starttime;

	return xmmsv_build_dict (XMMSV_DICT_ENTRY_STR ("version", XMMS_VERSION),
	                         XMMSV_DICT_ENTRY_INT ("uptime", uptime),
	                         XMMSV_DICT_END);
}

static gboolean
xmms_main_client_list_foreach (xmms_plugin_t *plugin, gpointer data)
{
	xmmsv_t *list, *dict;

	list = (xmmsv_t *) data;

	dict = xmmsv_build_dict (
	        XMMSV_DICT_ENTRY_STR ("name", xmms_plugin_name_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("shortname", xmms_plugin_shortname_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("version", xmms_plugin_version_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("description", xmms_plugin_description_get (plugin)),
	        XMMSV_DICT_ENTRY_INT ("type", xmms_plugin_type_get (plugin)),
	        XMMSV_DICT_END);

	xmmsv_list_append (list, dict);
	xmmsv_unref (dict);

	return TRUE;
}

static xmmsv_t *
xmms_main_client_list_plugins (xmms_object_t *main, gint32 type, xmms_error_t *err)
{
	xmmsv_t *list = xmmsv_new_list ();
	xmms_plugin_foreach (type, xmms_main_client_list_foreach, list);
	return list;
}

/**
 * @internal Function to respond to the 'hello' sent from clients on connect
 */
static void
xmms_main_client_hello (xmms_object_t *object, gint protocolver, const gchar *client, xmms_error_t *error)
{
	if (protocolver != XMMS_IPC_PROTOCOL_VERSION) {
		xmms_log_info ("Client '%s' with bad protocol version (%d, not %d) connected", client, protocolver, XMMS_IPC_PROTOCOL_VERSION);
		xmms_error_set (error, XMMS_ERROR_INVAL, "Bad protocol version");
		return;
	}
	XMMS_DBG ("Client '%s' connected", client);
}

static gboolean
kill_server (gpointer object) {
	xmms_main_t *mainobj = (xmms_main_t *) object;
	gint uptime = time (NULL) - mainobj->starttime;

	xmms_object_emit (XMMS_OBJECT (object),
	                  XMMS_IPC_SIGNAL_QUIT,
	                  xmmsv_new_int (uptime));

	xmms_object_unref (object);

	g_main_loop_quit (mainloop);
}


/**
 * @internal Function to respond to the 'quit' command sent from a client
 */
static void
xmms_main_client_quit (xmms_object_t *object, xmms_error_t *error)
{
	/*
	 * to be able to return from this method
	 * we add a timeout that will kill the server
	 * very "ugly"
	 */
	g_timeout_add (1, kill_server, object);
}

jint
JNI_OnLoad (JavaVM *vm, void *reserved)
{
	JNIEnv *env = NULL;
	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
		return -1;  /* fail */
	}

	jclass clazz = (*env)->FindClass (env, "org/xmms2/server/Server");
	(*env)->RegisterNatives (env, clazz, methods,
	                         sizeof(methods)/sizeof(methods[0]));

	global_jvm = vm;

	return JNI_VERSION_1_6;
}

static void
thread_destroy (gpointer data)
{
	(*global_jvm)->DetachCurrentThread (global_jvm);
}

static JNIEnv *
get_env ()
{
	JNIEnv *ret = NULL;

	if ((*global_jvm)->GetEnv (global_jvm, (void **)&ret, JNI_VERSION_1_6) != JNI_OK) {
		GPrivate *key = g_private_new (thread_destroy);
		g_private_set (key, (gpointer)1);

		(*global_jvm)->AttachCurrentThread (global_jvm, &ret, NULL);
	}

	return ret;
}

static void JNICALL
quit (JNIEnv *env, jclass thiz)
{
	kill_server (XMMS_OBJECT (mainobj));
}

static void JNICALL
playback_play (JNIEnv *env, jobject thiz)
{
	xmms_object_cmd_arg_t arg;
	xmms_object_cmd_arg_init (&arg);
	arg.args = xmmsv_new_list ();
	xmms_object_cmd_call (XMMS_OBJECT (mainobj->output_object),
	                      XMMS_IPC_CMD_START, &arg);
	xmmsv_unref (arg.args);
}

static void JNICALL
playback_pause (JNIEnv *env, jobject thiz)
{
	xmms_object_cmd_arg_t arg;
	xmms_object_cmd_arg_init (&arg);
	arg.args = xmmsv_new_list ();
	xmms_object_cmd_call (XMMS_OBJECT (mainobj->output_object),
	                      XMMS_IPC_CMD_PAUSE, &arg);
	xmmsv_unref (arg.args);
}

/**
 * @internal Destroy the main object
 * @param[in] object The object to destroy
 */
static void
xmms_main_destroy (xmms_object_t *object)
{
	xmms_main_t *mainobj = (xmms_main_t *) object;
	xmms_config_property_t *cv;
	JNIEnv *env = get_env ();

	xmms_object_unref (mainobj->xform_object);
	xmms_object_unref (mainobj->visualization_object);
	xmms_object_unref (mainobj->output_object);
	xmms_object_unref (mainobj->bindata_object);
	xmms_object_unref (mainobj->playlist_object);
	xmms_object_unref (mainobj->colldag_object);
	xmms_object_unref (mainobj->medialib_object);
	xmms_object_unref (mainobj->mediainfo_object);
	xmms_object_unref (mainobj->plsupdater_object);
	xmms_object_unref (mainobj->collsync_object);

	xmms_config_save ();

	xmms_config_shutdown ();

	xmms_plugin_shutdown ();

	xmms_main_unregister_ipc_commands ();

	xmms_ipc_shutdown ();

	xmms_log_shutdown ();

	(*env)->DeleteGlobalRef (env, server_object);
	(*env)->DeleteGlobalRef (env, mainobj->java_cache->status_handler);
	(*env)->DeleteGlobalRef (env, mainobj->java_cache->server_class);
	g_free (mainobj->java_cache);
}

/**
 * @internal Load the xmms2d configuration file. Creates the config directory
 * if needed.
 */
static void
load_config (void)
{
	gchar configdir[XMMS_PATH_MAX];

	if (!conffile) {
		conffile = XMMS_BUILD_PATH ("xmms2.conf");
	}

	g_assert (strlen (conffile) <= XMMS_MAX_CONFIGFILE_LEN);

	if (!xmms_userconfdir_get (configdir, sizeof (configdir))) {
		xmms_log_error ("Could not get path to config dir");
	} else if (!g_file_test (configdir, G_FILE_TEST_IS_DIR)) {
		g_mkdir_with_parents (configdir, 0755);
	}

	xmms_config_init (conffile);
}

static void
setup_ipc ()
{
	xmms_config_property_t *cv;
	gchar default_path[XMMS_PATH_MAX + 16];
	const gchar *ipcpath = NULL;

	xmms_fallback_ipcpath_get (default_path, sizeof (default_path));
	cv = xmms_config_property_register ("core.ipcsocket",
	                                    default_path,
	                                    on_config_ipcsocket_change,
	                                    NULL);

	ipcpath = xmms_config_property_get_string (cv);

	if (!xmms_ipc_setup_server (ipcpath)) {
		xmms_ipc_shutdown ();
		xmms_log_fatal ("IPC failed to init!");
	}
}

static jstring
dict_get_jstring (JNIEnv *env, xmmsv_t *dict, const char *key)
{
	const char *val = NULL;
	jstring tmp;
	xmmsv_dict_entry_get_string (dict, key, &val);
	g_return_val_if_fail (val, NULL);

	tmp = (*env)->NewStringUTF (env, val);
	if (tmp == NULL) {
		return NULL;
	}
	return (*env)->NewLocalRef (env, tmp);
}

static void
status_handler (xmms_object_t *object, xmmsv_t *data, gpointer userdata)
{
	JNIEnv *env = get_env ();
	int32_t status;
	xmms_main_t *m = (xmms_main_t *) userdata;
	xmms_main_java_cache_t *cache = m->java_cache;

	if (!xmmsv_get_int (data, &status)) {
		return;
	}

	(*env)->CallVoidMethod (env, cache->status_handler, cache->update_status, status);
}

static xmms_main_java_cache_t *
create_java_cache (JNIEnv *env, jobject thiz)
{
	xmms_main_java_cache_t *cache;
	jclass clazz = (*env)->GetObjectClass (env, thiz);
	jfieldID handler_id = (*env)->GetFieldID (env, clazz, "statusHandler",
	                                          "Lorg/xmms2/server/StatusHandler;");
	g_return_val_if_fail (clazz, NULL);

	cache = g_new0 (xmms_main_java_cache_t, 1);
	g_return_val_if_fail (cache, NULL);
	
	server_object = (*env)->NewGlobalRef (env, thiz);

	cache->server_class = (*env)->NewGlobalRef (env, clazz);
	cache->plugin_path_get = (*env)->GetMethodID (env, clazz, "getPluginPath",
	                                              "()Ljava/lang/String;");
	cache->server_ready = (*env)->GetMethodID (env, clazz, "serverReady", "()V");
	cache->browse_root = (*env)->GetMethodID (env, clazz, "getBrowseRoot", "()Ljava/lang/String;");

	cache->status_handler = (*env)->NewGlobalRef (env, (*env)->GetObjectField (env, thiz, handler_id));
	clazz = (*env)->GetObjectClass (env, cache->status_handler);
	cache->update_status = (*env)->GetMethodID (env, clazz, "updateStatus", "(I)V");

	return cache;
}

static void JNICALL
start_service (JNIEnv *env, jobject thiz)
{
	xmms_output_plugin_t *o_plugin;
	xmms_config_property_t *cv;
	gchar *uuid = NULL;
	const gchar *outname = NULL;
	gchar *plugin_path = NULL;
	int loglevel = 0;
	xmms_main_java_cache_t *java_cache = create_java_cache (env, thiz);

	if (!java_cache) {
		xmms_log_fatal ("fail!");
		return;
	}

	g_thread_init (NULL);

	g_random_set_seed (time (NULL));

	xmms_log_init (loglevel);

	xmms_ipc_init ();
	load_config ();

	setup_ipc ();

	{
		jobject *plugins = (*env)->CallObjectMethod (env, thiz, java_cache->plugin_path_get);
		const char *str = (*env)->GetStringUTFChars (env, plugins, 0);
		plugin_path = g_strdup (str);
		(*env)->ReleaseStringUTFChars (env, plugins, str);
	}

	if (!xmms_plugin_init (plugin_path)) {
		xmms_log_fatal ("plugin init fail");
	}

	g_free (plugin_path);

	mainobj = xmms_object_new (xmms_main_t, xmms_main_destroy);
	mainobj->java_cache = java_cache;

	mainobj->medialib_object = xmms_medialib_init ();
	mainobj->colldag_object = xmms_collection_init (mainobj->medialib_object);
	mainobj->mediainfo_object = xmms_mediainfo_reader_start (mainobj->medialib_object);
	mainobj->playlist_object = xmms_playlist_init (mainobj->medialib_object,
	                                               mainobj->colldag_object);

	uuid = xmms_medialib_uuid (mainobj->medialib_object);
	mainobj->collsync_object = xmms_coll_sync_init (uuid,
	                                                mainobj->colldag_object,
	                                                mainobj->playlist_object);
	g_free (uuid);
	mainobj->plsupdater_object = xmms_playlist_updater_init (mainobj->playlist_object);

	mainobj->xform_object = xmms_xform_object_init ();
	mainobj->bindata_object = xmms_bindata_init ();

	/* find output plugin. */
	cv = xmms_config_property_register ("output.plugin",
	                                    XMMS_OUTPUT_DEFAULT,
	                                    NULL, NULL);

	outname = xmms_config_property_get_string (cv);
	xmms_log_info ("Using output plugin: %s", outname);
	o_plugin = (xmms_output_plugin_t *) xmms_plugin_find (XMMS_PLUGIN_TYPE_OUTPUT, outname);
	if (!o_plugin) {
		xmms_log_error ("Baaaaad output plugin, try to change the"
		                "output.plugin config variable to something useful");
		return; // TODO: release stuff etc?
	}

	mainobj->output_object = xmms_output_new (o_plugin,
	                                          mainobj->playlist_object,
	                                          mainobj->medialib_object);
	if (!mainobj->output_object) {
		xmms_log_fatal ("Failed to create output object!");
	}

	mainobj->visualization_object = xmms_visualization_new (mainobj->output_object);

	xmms_signal_init (XMMS_OBJECT (mainobj));

	xmms_main_register_ipc_commands (XMMS_OBJECT (mainobj));

	xmms_object_connect (XMMS_OBJECT (mainobj->output_object),
	                     XMMS_IPC_SIGNAL_PLAYBACK_STATUS,
	                     &status_handler, mainobj);

	/* Save the time we started in order to count uptime */
	mainobj->starttime = time (NULL);

	mainloop = g_main_loop_new (NULL, FALSE);

	{
		jstring *root = (*env)->CallObjectMethod (env, thiz, java_cache->browse_root);
		const char *str = (*env)->GetStringUTFChars (env, root, 0);
		xmms_config_property_register ("android.browse_root", str, NULL, NULL);
		(*env)->ReleaseStringUTFChars (env, root, str);
	}

	(*env)->CallVoidMethod (env, thiz, java_cache->server_ready);
	g_main_loop_run (mainloop);
}
