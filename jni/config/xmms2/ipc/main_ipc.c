/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_hello (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to hello (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to hello");
		return;
	}
	gint32 argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in hello");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in hello");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in hello");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in hello");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in hello");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in hello");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in hello");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in hello");
		return;
	}

	xmms_main_client_hello ((xmms_object_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_quit (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to quit (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to quit");
		return;
	}


	xmms_main_client_quit ((xmms_object_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_list_plugins (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to list_plugins (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to list_plugins");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in list_plugins");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in list_plugins");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in list_plugins");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in list_plugins");
		return;
	}

	arg->retval = xmms_convert_and_kill_list (xmms_main_client_list_plugins ((xmms_object_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_stats (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to stats (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to stats");
		return;
	}


	GTree * retval = xmms_main_client_stats ((xmms_object_t *) object, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_dict (retval);
	}
}



static void
xmms_main_register_ipc_commands (xmms_object_t *main_object)
{
	xmms_ipc_object_register (1, main_object);

	xmms_object_cmd_add (main_object, 32, __int_xmms_cmd_hello);
	xmms_object_cmd_add (main_object, 33, __int_xmms_cmd_quit);
	xmms_object_cmd_add (main_object, 34, __int_xmms_cmd_list_plugins);
	xmms_object_cmd_add (main_object, 35, __int_xmms_cmd_stats);

	xmms_ipc_broadcast_register (main_object, 12);

}

static void
xmms_main_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (12);


	xmms_ipc_object_unregister (1);
}
