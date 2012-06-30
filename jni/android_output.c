#include "xmms/xmms_outputplugin.h"
#include "xmms/xmms_log.h"

#include <jni.h>
#include <glib.h>

typedef struct xmms_android_data_St {
	jclass output_class;
	jobject output_object;

	jmethodID write;
	jmethodID open;
	jmethodID close;
	jmethodID flush;
	jmethodID set_format;
	jmethodID latency_get;

	jbyteArray buffer;
} xmms_android_data_t;

static gboolean xmms_android_plugin_setup (xmms_output_plugin_t *output_plugin);
static gboolean xmms_android_new (xmms_output_t *output);
static void xmms_android_destroy (xmms_output_t *output);
static void xmms_android_flush (xmms_output_t *output);
static gboolean xmms_android_open (xmms_output_t *output);
static void xmms_android_close (xmms_output_t *output);
static void xmms_android_write (xmms_output_t *output, gpointer buffer,
                                gint len, xmms_error_t *err);
static gboolean xmms_android_format_set (xmms_output_t *output,
                                         const xmms_stream_type_t *format);
static guint xmms_android_latency_get (xmms_output_t *output);

XMMS_OUTPUT_PLUGIN ("android",
                    "Android output",
                    XMMS_VERSION,
                    "Android output plugin",
                    xmms_android_plugin_setup);

extern JavaVM *global_jvm;
extern jobject server_object;

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

static gboolean
xmms_android_plugin_setup (xmms_output_plugin_t *plugin)
{
	xmms_output_methods_t methods;

	XMMS_OUTPUT_METHODS_INIT (methods);
	methods.new = xmms_android_new;
	methods.destroy = xmms_android_destroy;
	methods.flush = xmms_android_flush;

	methods.open = xmms_android_open;
	methods.close = xmms_android_close;
	methods.format_set = xmms_android_format_set;
	methods.write = xmms_android_write;
	methods.latency_get = xmms_android_latency_get;

	xmms_output_plugin_methods_set (plugin, &methods);

	return TRUE;
}

static xmms_android_data_t *
setup_output()
{
	xmms_android_data_t *data;
	JNIEnv *env = get_env ();
	jmethodID ctor;
	jclass clazz;

	g_return_val_if_fail (env, NULL);
	data = g_new0 (xmms_android_data_t, 1);
	g_return_val_if_fail (data, NULL);

	data->output_class = (*env)->FindClass (env, "org/xmms2/server/plugins/Output");
	if (!(data->output_class)) {
		goto setup_error;
	}
	data->output_class = (*env)->NewGlobalRef (env, data->output_class);

	ctor = (*env)->GetMethodID (env, data->output_class, "<init>", "(Lorg/xmms2/server/Server;)V");
	if (!ctor) {
		goto setup_error;
	}

	data->write = (*env)->GetMethodID (env, data->output_class, "write", "([BI)Z");
	if (!(data->write)) {
		goto setup_error;
	}

	data->open = (*env)->GetMethodID (env, data->output_class, "open", "()Z");
	if (!(data->open)) {
		goto setup_error;
	}

	data->close = (*env)->GetMethodID (env, data->output_class, "close", "()V");
	if (!(data->close)) {
		goto setup_error;
	}

	data->flush = (*env)->GetMethodID (env, data->output_class, "flush", "()V");
	if (!(data->flush)) {
		goto setup_error;
	}

	data->set_format = (*env)->GetMethodID (env, data->output_class, "setFormat", "(III)Z");
	if (!(data->set_format)) {
		goto setup_error;
	}

	data->latency_get = (*env)->GetMethodID (env, data->output_class, "getLatency", "()I");
	if (!(data->set_format)) {
		goto setup_error;
	}

	data->output_object = (*env)->NewObject (env, data->output_class, ctor, server_object);
	if (!(data->output_object)) {
		goto setup_error;
	}
	data->output_object = (*env)->NewGlobalRef (env, data->output_object);

	return data;

setup_error:
	if (data) {
		g_free (data);
	}
	return NULL;
}

static gboolean
xmms_android_new (xmms_output_t *output)
{
	xmms_android_data_t *data;

	g_return_val_if_fail (output, FALSE);
	data = setup_output();
	g_return_val_if_fail (data, FALSE);

	xmms_output_format_add (output, XMMS_SAMPLE_FORMAT_S16, 1, 44100);
	xmms_output_format_add (output, XMMS_SAMPLE_FORMAT_S16, 2, 44100);
	xmms_output_format_add (output, XMMS_SAMPLE_FORMAT_S16, 1, 48000);
	xmms_output_format_add (output, XMMS_SAMPLE_FORMAT_S16, 2, 48000);

	xmms_output_private_data_set (output, data);

	return TRUE;
}

static jbyteArray 
create_buffer (JNIEnv *env, jsize len)
{
	jbyteArray ret = (*env)->NewByteArray (env, len);
	g_return_val_if_fail (ret, NULL);
	return (*env)->NewGlobalRef (env, ret);
}

static void
delete_buffer (JNIEnv *env, jbyteArray buffer)
{
	(*env)->DeleteGlobalRef (env, buffer);
}

static void
destroy_output (xmms_android_data_t *data)
{
	JNIEnv *env = get_env ();
	g_return_if_fail (env);

	(*env)->DeleteGlobalRef (env, data->output_object);
	(*env)->DeleteGlobalRef (env, data->output_class);
	delete_buffer (env, data->buffer);
}

static void
xmms_android_destroy (xmms_output_t *output)
{
	xmms_android_data_t *data;

	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);

	destroy_output (data);

	g_free (data);
}

static void
xmms_android_flush (xmms_output_t *output)
{
	xmms_android_data_t *data;
	JNIEnv *env = get_env ();

	g_return_if_fail (env);
	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);

	(*env)->CallVoidMethod (env, data->output_object, data->flush);
}

static gboolean
xmms_android_open (xmms_output_t *output)
{
	xmms_android_data_t *data;
	JNIEnv *env = get_env ();
	jboolean ret;

	g_return_val_if_fail (env, FALSE);
	g_return_val_if_fail (output, FALSE);

	data = xmms_output_private_data_get (output);
	g_return_val_if_fail (data, FALSE);

	ret = (*env)->CallBooleanMethod (env, data->output_object, data->open);

	return ret;
}

static void 
xmms_android_close (xmms_output_t *output)
{
	xmms_android_data_t *data;
	JNIEnv *env = get_env ();

	g_return_if_fail (env);
	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);

	(*env)->CallVoidMethod (env, data->output_object, data->close);
}

static void
ensure_buffer_size (JNIEnv *env, xmms_android_data_t *data, gint len)
{
	if (!(data->buffer)) {
		data->buffer = create_buffer (env, len);
	} else {
		jsize cur_len = (*env)->GetArrayLength (env, data->buffer);
		
		if (cur_len < len) {
			delete_buffer (env, data->buffer);
			data->buffer = create_buffer (env, len);
		}
	}
}

static void
xmms_android_write (xmms_output_t *output, gpointer buffer, gint len,
                    xmms_error_t *err)
{
	xmms_android_data_t *data;
	JNIEnv *env = get_env ();
	jboolean ret;

	g_return_if_fail (env);
	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);

	ensure_buffer_size (env, data, len);

	g_return_if_fail (data->buffer);
	(*env)->SetByteArrayRegion (env, data->buffer, 0, len, buffer);

	ret = (*env)->CallBooleanMethod (env, data->output_object, data->write, data->buffer, len);

	if (!ret) {
		xmms_error_set (err, XMMS_ERROR_NO_SAUSAGE, "Error writing audio");
	}
}

static gboolean
xmms_android_format_set (xmms_output_t *output, const xmms_stream_type_t *format)
{
	xmms_android_data_t *data;
	xmms_sample_format_t sformat;
	gint channels, srate;
	JNIEnv *env = get_env ();
	jboolean ret;

	g_return_val_if_fail (env, FALSE);
	g_return_val_if_fail (output, FALSE);
	data = xmms_output_private_data_get (output);
	g_return_val_if_fail (data, FALSE);

	sformat = xmms_stream_type_get_int (format, XMMS_STREAM_TYPE_FMT_FORMAT);
	channels = xmms_stream_type_get_int (format, XMMS_STREAM_TYPE_FMT_CHANNELS);
	srate = xmms_stream_type_get_int (format, XMMS_STREAM_TYPE_FMT_SAMPLERATE);

	if (sformat != XMMS_SAMPLE_FORMAT_S16) {
		return FALSE;
	}

	XMMS_DBG ("Setting audio format: %d %dch %dHz", sformat, channels, srate);

	ret = (*env)->CallBooleanMethod (env, data->output_object, data->set_format,
	                                 2, channels, srate);

	return ret;
}

static guint
xmms_android_latency_get (xmms_output_t *output)
{
	xmms_android_data_t *data;
	jint ret = 0;
	JNIEnv *env = get_env();

	g_return_val_if_fail (env, 0);
	g_return_val_if_fail (output, 0);
	data = xmms_output_private_data_get (output);
	g_return_val_if_fail (data, 0);

	ret = (*env)->CallIntMethod (env, data->output_object, data->latency_get);

	return ret;
}
