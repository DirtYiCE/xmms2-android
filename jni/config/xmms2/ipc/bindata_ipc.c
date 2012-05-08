/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_retrieve (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to retrieve (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to retrieve");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in retrieve");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in retrieve");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in retrieve");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in retrieve");
		return;
	}

	arg->retval = xmms_bindata_client_retrieve ((xmms_bindata_t *) object, argval0, &arg->error);
}


static void
__int_xmms_cmd_add (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to add (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to add");
		return;
	}
	GString * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in add");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in add");
		return;
	}
	if (!xmms_bin_to_gstring (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in add");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in add");
		return;
	}

	gchar * retval = xmms_bindata_client_add ((xmms_bindata_t *) object, argval0, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_string (retval);
	}
}


static void
__int_xmms_cmd_remove (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to remove (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to remove");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in remove");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in remove");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in remove");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in remove");
		return;
	}

	xmms_bindata_client_remove ((xmms_bindata_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_list (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to list (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to list");
		return;
	}


	arg->retval = xmms_convert_and_kill_list (xmms_bindata_client_list ((xmms_bindata_t *) object, &arg->error));
}



static void
xmms_bindata_register_ipc_commands (xmms_object_t *bindata_object)
{
	xmms_ipc_object_register (10, bindata_object);

	xmms_object_cmd_add (bindata_object, 32, __int_xmms_cmd_retrieve);
	xmms_object_cmd_add (bindata_object, 33, __int_xmms_cmd_add);
	xmms_object_cmd_add (bindata_object, 34, __int_xmms_cmd_remove);
	xmms_object_cmd_add (bindata_object, 35, __int_xmms_cmd_list);


}

static void
xmms_bindata_unregister_ipc_commands (void)
{


	xmms_ipc_object_unregister (10);
}
