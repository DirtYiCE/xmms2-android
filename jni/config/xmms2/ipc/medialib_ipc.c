/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_get_info (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to get_info (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to get_info");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in get_info");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in get_info");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in get_info");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in get_info");
		return;
	}

	GTree * retval = xmms_medialib_client_get_info ((xmms_medialib_t *) object, argval0, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_dict (retval);
	}
}


static void
__int_xmms_cmd_import_path (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to import_path (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to import_path");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in import_path");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in import_path");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in import_path");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in import_path");
		return;
	}

	xmms_medialib_client_import_path ((xmms_medialib_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_rehash (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to rehash (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to rehash");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in rehash");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in rehash");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in rehash");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in rehash");
		return;
	}

	xmms_medialib_client_rehash ((xmms_medialib_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_get_id (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to get_id (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to get_id");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in get_id");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in get_id");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in get_id");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in get_id");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_medialib_client_get_id ((xmms_medialib_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_remove_entry (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to remove_entry (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to remove_entry");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in remove_entry");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in remove_entry");
		return;
	}

	xmms_medialib_client_remove_entry ((xmms_medialib_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_set_property_string (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 4) {
		XMMS_DBG ("Wrong number of arguments to set_property_string (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_property_string");
		return;
	}
	gint32 argval0;
	const char * argval1;
	const char * argval2;
	const char * argval3;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_property_string");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_property_string");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in set_property_string");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in set_property_string");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in set_property_string");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in set_property_string");
		return;
	}
	if (!xmmsv_list_get (arg->args, 3, &t)) {
		XMMS_DBG ("Missing arg 3 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 3 in set_property_string");
		return;
	}
	if (!xmmsv_get_string (t, &argval3)) {
		XMMS_DBG ("Error parsing arg 3 in set_property_string");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 3 in set_property_string");
		return;
	}

	xmms_medialib_client_set_property_string ((xmms_medialib_t *) object, argval0, argval1, argval2, argval3, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_set_property_int (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 4) {
		XMMS_DBG ("Wrong number of arguments to set_property_int (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_property_int");
		return;
	}
	gint32 argval0;
	const char * argval1;
	const char * argval2;
	gint32 argval3;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_property_int");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_property_int");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in set_property_int");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in set_property_int");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in set_property_int");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in set_property_int");
		return;
	}
	if (!xmmsv_list_get (arg->args, 3, &t)) {
		XMMS_DBG ("Missing arg 3 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 3 in set_property_int");
		return;
	}
	if (!xmmsv_get_int (t, &argval3)) {
		XMMS_DBG ("Error parsing arg 3 in set_property_int");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 3 in set_property_int");
		return;
	}

	xmms_medialib_client_set_property_int ((xmms_medialib_t *) object, argval0, argval1, argval2, argval3, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_remove_property (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to remove_property (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to remove_property");
		return;
	}
	gint32 argval0;
	const char * argval1;
	const char * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in remove_property");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in remove_property");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in remove_property");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in remove_property");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in remove_property");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in remove_property");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in remove_property");
		return;
	}

	xmms_medialib_client_remove_property ((xmms_medialib_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_move_entry (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to move_entry (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to move_entry");
		return;
	}
	gint32 argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in move_entry");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in move_entry");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in move_entry");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in move_entry");
		return;
	}

	xmms_medialib_client_move_entry ((xmms_medialib_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_add_entry (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to add_entry (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to add_entry");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in add_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in add_entry");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in add_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in add_entry");
		return;
	}

	xmms_medialib_client_add_entry ((xmms_medialib_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}



static void
xmms_medialib_register_ipc_commands (xmms_object_t *medialib_object)
{
	xmms_ipc_object_register (5, medialib_object);

	xmms_object_cmd_add (medialib_object, 32, __int_xmms_cmd_get_info);
	xmms_object_cmd_add (medialib_object, 33, __int_xmms_cmd_import_path);
	xmms_object_cmd_add (medialib_object, 34, __int_xmms_cmd_rehash);
	xmms_object_cmd_add (medialib_object, 35, __int_xmms_cmd_get_id);
	xmms_object_cmd_add (medialib_object, 36, __int_xmms_cmd_remove_entry);
	xmms_object_cmd_add (medialib_object, 37, __int_xmms_cmd_set_property_string);
	xmms_object_cmd_add (medialib_object, 38, __int_xmms_cmd_set_property_int);
	xmms_object_cmd_add (medialib_object, 39, __int_xmms_cmd_remove_property);
	xmms_object_cmd_add (medialib_object, 40, __int_xmms_cmd_move_entry);
	xmms_object_cmd_add (medialib_object, 41, __int_xmms_cmd_add_entry);

	xmms_ipc_broadcast_register (medialib_object, 8);
	xmms_ipc_broadcast_register (medialib_object, 9);
	xmms_ipc_broadcast_register (medialib_object, 10);

}

static void
xmms_medialib_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (8);
	xmms_ipc_broadcast_unregister (9);
	xmms_ipc_broadcast_unregister (10);


	xmms_ipc_object_unregister (5);
}
