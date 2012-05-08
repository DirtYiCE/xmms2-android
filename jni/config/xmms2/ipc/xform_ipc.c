/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_browse (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to browse (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to browse");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in browse");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in browse");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in browse");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in browse");
		return;
	}

	arg->retval = xmms_convert_and_kill_list (xmms_xform_client_browse ((xmms_xform_object_t *) object, argval0, &arg->error));
}



static void
xmms_xform_register_ipc_commands (xmms_object_t *xform_object)
{
	xmms_ipc_object_register (9, xform_object);

	xmms_object_cmd_add (xform_object, 32, __int_xmms_cmd_browse);


}

static void
xmms_xform_unregister_ipc_commands (void)
{


	xmms_ipc_object_unregister (9);
}
