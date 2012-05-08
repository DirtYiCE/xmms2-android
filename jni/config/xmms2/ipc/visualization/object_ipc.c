/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_query_version (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to query_version (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to query_version");
		return;
	}


	arg->retval = xmmsv_new_int (xmms_visualization_client_query_version ((xmms_visualization_t *) object, &arg->error));
}


static void
__int_xmms_cmd_register (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to register (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to register");
		return;
	}


	arg->retval = xmmsv_new_int (xmms_visualization_client_register ((xmms_visualization_t *) object, &arg->error));
}


static void
__int_xmms_cmd_init_shm (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to init_shm (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to init_shm");
		return;
	}
	gint32 argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in init_shm");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in init_shm");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in init_shm");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in init_shm");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in init_shm");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in init_shm");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in init_shm");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in init_shm");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_visualization_client_init_shm ((xmms_visualization_t *) object, argval0, argval1, &arg->error));
}


static void
__int_xmms_cmd_init_udp (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to init_udp (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to init_udp");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in init_udp");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in init_udp");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in init_udp");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in init_udp");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_visualization_client_init_udp ((xmms_visualization_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_set_property (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to set_property (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_property");
		return;
	}
	gint32 argval0;
	const char * argval1;
	const char * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_property");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_property");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in set_property");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in set_property");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in set_property");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in set_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in set_property");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_visualization_client_set_property ((xmms_visualization_t *) object, argval0, argval1, argval2, &arg->error));
}


static void
__int_xmms_cmd_set_properties (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to set_properties (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_properties");
		return;
	}
	gint32 argval0;
	xmmsv_t * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_properties");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_properties");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_properties");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_properties");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in set_properties");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in set_properties");
		return;
	}
	argval1 = t;

	arg->retval = xmmsv_new_int (xmms_visualization_client_set_properties ((xmms_visualization_t *) object, argval0, argval1, &arg->error));
}


static void
__int_xmms_cmd_shutdown (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to shutdown (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to shutdown");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in shutdown");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in shutdown");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in shutdown");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in shutdown");
		return;
	}

	xmms_visualization_client_shutdown ((xmms_visualization_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}



static void
xmms_visualization_register_ipc_commands (xmms_object_t *visualization_object)
{
	xmms_ipc_object_register (7, visualization_object);

	xmms_object_cmd_add (visualization_object, 32, __int_xmms_cmd_query_version);
	xmms_object_cmd_add (visualization_object, 33, __int_xmms_cmd_register);
	xmms_object_cmd_add (visualization_object, 34, __int_xmms_cmd_init_shm);
	xmms_object_cmd_add (visualization_object, 35, __int_xmms_cmd_init_udp);
	xmms_object_cmd_add (visualization_object, 36, __int_xmms_cmd_set_property);
	xmms_object_cmd_add (visualization_object, 37, __int_xmms_cmd_set_properties);
	xmms_object_cmd_add (visualization_object, 38, __int_xmms_cmd_shutdown);


}

static void
xmms_visualization_unregister_ipc_commands (void)
{


	xmms_ipc_object_unregister (7);
}
