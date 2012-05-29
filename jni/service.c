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
#include "xmmspriv/xmms_visualization.h"

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
static GTree *xmms_main_client_stats (xmms_object_t *object, xmms_error_t *error);
static GList *xmms_main_client_list_plugins (xmms_object_t *main, gint32 type, xmms_error_t *err);
static void xmms_main_client_hello (xmms_object_t *object, gint protocolver, const gchar *client, xmms_error_t *error);

#include "main_ipc.c"

static void JNICALL start_service (JNIEnv *env, jclass thiz);
static void JNICALL quit (JNIEnv *env, jclass thiz);

static JNINativeMethod methods[] = {
	{"start", "()V", start_service},
	{"quit", "()V", quit}
};

JavaVM *global_jvm;


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
static GTree *
xmms_main_client_stats (xmms_object_t *object, xmms_error_t *error)
{
	GTree *ret;
	gint starttime;

	ret = g_tree_new_full ((GCompareDataFunc) strcmp, NULL,
	                       NULL, (GDestroyNotify) xmmsv_unref);

	starttime = ((xmms_main_t*)object)->starttime;

	g_tree_insert (ret, (gpointer) "version",
	               xmmsv_new_string (XMMS_VERSION));
	g_tree_insert (ret, (gpointer) "uptime",
	               xmmsv_new_int (time (NULL) - starttime));

	return ret;
}

static gboolean
xmms_main_client_list_foreach (xmms_plugin_t *plugin, gpointer data)
{
	xmmsv_t *dict;
	GList **list = data;

	dict = xmmsv_build_dict (
	        XMMSV_DICT_ENTRY_STR ("name", xmms_plugin_name_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("shortname", xmms_plugin_shortname_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("version", xmms_plugin_version_get (plugin)),
	        XMMSV_DICT_ENTRY_STR ("description", xmms_plugin_description_get (plugin)),
	        XMMSV_DICT_ENTRY_INT ("type", xmms_plugin_type_get (plugin)),
	        XMMSV_DICT_END);

	*list = g_list_prepend (*list, dict);

	return TRUE;
}

static GList *
xmms_main_client_list_plugins (xmms_object_t *main, gint32 type, xmms_error_t *err)
{
	GList *list = NULL;
	xmms_plugin_foreach (type, xmms_main_client_list_foreach, &list);
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
	xmms_object_emit_f (XMMS_OBJECT (object),
	                    XMMS_IPC_SIGNAL_QUIT,
	                    XMMSV_TYPE_INT32,
	                    time (NULL)-((xmms_main_t*)object)->starttime);

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

	xmms_log_info("Load successful!");

	global_jvm = vm;

	return JNI_VERSION_1_6;
}

static void JNICALL
quit (JNIEnv *env, jclass thiz)
{
	kill_server (XMMS_OBJECT (mainobj));
}


/**
 * @internal Destroy the main object
 * @param[in] object The object to destroy
 */
static void
xmms_main_destroy (xmms_object_t *object)
{
	xmms_main_t *mainobj = (xmms_main_t *) object;
	xmms_object_cmd_arg_t arg;
	xmms_config_property_t *cv;

	/* stop output */
	xmms_object_cmd_arg_init (&arg);
	arg.args = xmmsv_new_list ();
	xmms_object_cmd_call (XMMS_OBJECT (mainobj->output_object),
	                      XMMS_IPC_CMD_STOP, &arg);
	xmmsv_unref (arg.args);

	g_usleep (G_USEC_PER_SEC); /* wait for the output thread to end */

	xmms_object_unref (mainobj->output_object);
	xmms_object_unref (mainobj->bindata_object);
	xmms_object_unref (mainobj->medialib_object);
	xmms_object_unref (mainobj->playlist_object);
	xmms_object_unref (mainobj->xform_object);
	xmms_object_unref (mainobj->mediainfo_object);
	xmms_object_unref (mainobj->visualization_object);

	xmms_config_save ();

	xmms_config_shutdown ();

	xmms_plugin_shutdown ();

	xmms_main_unregister_ipc_commands ();

	xmms_ipc_shutdown ();

	xmms_log_shutdown ();
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

/**
 * @internal Switch to using another output plugin
 * @param object An object
 * @param data The name of the output plugin to switch to
 * @param userdata The #xmms_main_t object
 */
static void
change_output (xmms_object_t *object, xmmsv_t *_data, gpointer userdata)
{
	xmms_output_plugin_t *plugin;
	xmms_main_t *mainobj = (xmms_main_t*)userdata;
	const gchar *outname;

	if (!mainobj->output_object)
		return;

	outname = xmms_config_property_get_string ((xmms_config_property_t *) object);

	xmms_log_info ("Switching to output %s", outname);

	plugin = (xmms_output_plugin_t *)xmms_plugin_find (XMMS_PLUGIN_TYPE_OUTPUT, outname);
	if (!plugin) {
		xmms_log_error ("Baaaaad output plugin, try to change the output.plugin config variable to something useful");
	} else {
		if (!xmms_output_plugin_switch (mainobj->output_object, plugin)) {
			xmms_log_error ("Baaaaad output plugin, try to change the output.plugin config variable to something useful");
		}
	}
}

void
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

static void JNICALL
start_service (JNIEnv *env, jclass thiz)
{
	xmms_output_plugin_t *o_plugin;
	xmms_config_property_t *cv;
	gchar *uuid = NULL;
	const gchar *outname = NULL;
	const gchar *plugin_path = NULL;
	int loglevel = 0;
	jmethodID method;

	g_thread_init (NULL);

	g_random_set_seed (time (NULL));

	xmms_log_init (loglevel);
	xmms_log_info("starting...");

	xmms_ipc_init ();
	load_config ();

	setup_ipc ();

	jclass clazz = (*env)->GetObjectClass (env, thiz);
	method = (*env)->GetMethodID (env, clazz, "getPluginPath", "()Ljava/lang/String;");
	if (method) {
		jobject *plugins = (*env)->CallObjectMethod (env, thiz, method);
		const char *str = (*env)->GetStringUTFChars (env, plugins, 0);
		plugin_path = g_strdup (str);
		(*env)->ReleaseStringUTFChars (env, plugins, str);
	}

	if (!xmms_plugin_init (plugin_path)) {
		xmms_log_fatal ("plugin init fail");
	}

	mainobj = xmms_object_new (xmms_main_t, xmms_main_destroy);

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
	                                    change_output, mainobj);

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

	/* Save the time we started in order to count uptime */
	mainobj->starttime = time (NULL);

	mainloop = g_main_loop_new (NULL, FALSE);

	g_main_loop_run (mainloop);
}
