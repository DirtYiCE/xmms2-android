/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_get_value (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to get_value (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to get_value");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in get_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in get_value");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in get_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in get_value");
		return;
	}

	gchar * retval = xmms_config_client_get_value ((xmms_config_t *) object, argval0, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_string (retval);
	}
}


static void
__int_xmms_cmd_set_value (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to set_value (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_value");
		return;
	}
	const char * argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_value");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_value");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in set_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in set_value");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in set_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in set_value");
		return;
	}

	xmms_config_client_set_value ((xmms_config_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_register_value (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to register_value (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to register_value");
		return;
	}
	const char * argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in register_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in register_value");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in register_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in register_value");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in register_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in register_value");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in register_value");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in register_value");
		return;
	}

	gchar * retval = xmms_config_client_register_value ((xmms_config_t *) object, argval0, argval1, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_string (retval);
	}
}


static void
__int_xmms_cmd_list_values (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to list_values (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to list_values");
		return;
	}


	GTree * retval = xmms_config_client_list_values ((xmms_config_t *) object, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_dict (retval);
	}
}



static void
xmms_config_register_ipc_commands (xmms_object_t *config_object)
{
	xmms_ipc_object_register (3, config_object);

	xmms_object_cmd_add (config_object, 32, __int_xmms_cmd_get_value);
	xmms_object_cmd_add (config_object, 33, __int_xmms_cmd_set_value);
	xmms_object_cmd_add (config_object, 34, __int_xmms_cmd_register_value);
	xmms_object_cmd_add (config_object, 35, __int_xmms_cmd_list_values);

	xmms_ipc_broadcast_register (config_object, 1);

}

static void
xmms_config_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (1);


	xmms_ipc_object_unregister (3);
}
