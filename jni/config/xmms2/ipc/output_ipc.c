/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_start (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to start (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to start");
		return;
	}


	xmms_playback_client_start ((xmms_output_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_stop (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to stop (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to stop");
		return;
	}


	xmms_playback_client_stop ((xmms_output_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_pause (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to pause (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to pause");
		return;
	}


	xmms_playback_client_pause ((xmms_output_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_tickle (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to tickle (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to tickle");
		return;
	}


	xmms_playback_client_tickle ((xmms_output_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_playtime (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to playtime (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to playtime");
		return;
	}


	arg->retval = xmmsv_new_int (xmms_playback_client_playtime ((xmms_output_t *) object, &arg->error));
}


static void
__int_xmms_cmd_seek_ms (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to seek_ms (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to seek_ms");
		return;
	}
	gint32 argval0;
	gint32 argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in seek_ms");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in seek_ms");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in seek_ms");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in seek_ms");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in seek_ms");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in seek_ms");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in seek_ms");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in seek_ms");
		return;
	}

	xmms_playback_client_seek_ms ((xmms_output_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_seek_samples (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to seek_samples (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to seek_samples");
		return;
	}
	gint32 argval0;
	gint32 argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in seek_samples");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in seek_samples");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in seek_samples");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in seek_samples");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in seek_samples");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in seek_samples");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in seek_samples");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in seek_samples");
		return;
	}

	xmms_playback_client_seek_samples ((xmms_output_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_status (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to status (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to status");
		return;
	}


	arg->retval = xmmsv_new_int (xmms_playback_client_status ((xmms_output_t *) object, &arg->error));
}


static void
__int_xmms_cmd_current_id (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to current_id (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to current_id");
		return;
	}


	arg->retval = xmmsv_new_int (xmms_playback_client_current_id ((xmms_output_t *) object, &arg->error));
}


static void
__int_xmms_cmd_volume_set (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to volume_set (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to volume_set");
		return;
	}
	const char * argval0;
	gint32 argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in volume_set");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in volume_set");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in volume_set");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in volume_set");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in volume_set");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in volume_set");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in volume_set");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in volume_set");
		return;
	}

	xmms_playback_client_volume_set ((xmms_output_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_volume_get (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to volume_get (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to volume_get");
		return;
	}


	GTree * retval = xmms_playback_client_volume_get ((xmms_output_t *) object, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_dict (retval);
	}
}



static void
xmms_playback_register_ipc_commands (xmms_object_t *playback_object)
{
	xmms_ipc_object_register (4, playback_object);

	xmms_object_cmd_add (playback_object, 32, __int_xmms_cmd_start);
	xmms_object_cmd_add (playback_object, 33, __int_xmms_cmd_stop);
	xmms_object_cmd_add (playback_object, 34, __int_xmms_cmd_pause);
	xmms_object_cmd_add (playback_object, 35, __int_xmms_cmd_tickle);
	xmms_object_cmd_add (playback_object, 36, __int_xmms_cmd_playtime);
	xmms_object_cmd_add (playback_object, 37, __int_xmms_cmd_seek_ms);
	xmms_object_cmd_add (playback_object, 38, __int_xmms_cmd_seek_samples);
	xmms_object_cmd_add (playback_object, 39, __int_xmms_cmd_status);
	xmms_object_cmd_add (playback_object, 40, __int_xmms_cmd_current_id);
	xmms_object_cmd_add (playback_object, 41, __int_xmms_cmd_volume_set);
	xmms_object_cmd_add (playback_object, 42, __int_xmms_cmd_volume_get);

	xmms_ipc_broadcast_register (playback_object, 2);
	xmms_ipc_broadcast_register (playback_object, 3);
	xmms_ipc_broadcast_register (playback_object, 5);

	xmms_ipc_signal_register (playback_object, 4);
}

static void
xmms_playback_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (2);
	xmms_ipc_broadcast_unregister (3);
	xmms_ipc_broadcast_unregister (5);

	xmms_ipc_signal_unregister (4);

	xmms_ipc_object_unregister (4);
}
