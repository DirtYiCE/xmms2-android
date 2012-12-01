/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_replace (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to replace (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to replace");
		return;
	}
	const char * argval0;
	xmmsv_coll_t * argval1;
	gint32 argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in replace");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in replace");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in replace");
		return;
	}
	if (!xmmsv_get_coll (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in replace");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in replace");
		return;
	}
	if (!xmmsv_get_int (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in replace");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in replace");
		return;
	}

	xmms_playlist_client_replace ((xmms_playlist_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_set_next (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to set_next (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_next");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_next");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_next");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_next");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_next");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_playlist_client_set_next ((xmms_playlist_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_set_next_rel (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to set_next_rel (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to set_next_rel");
		return;
	}
	gint32 argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in set_next_rel");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in set_next_rel");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in set_next_rel");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in set_next_rel");
		return;
	}

	arg->retval = xmmsv_new_int (xmms_playlist_client_set_next_rel ((xmms_playlist_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_add_url (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to add_url (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to add_url");
		return;
	}
	const char * argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in add_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in add_url");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in add_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in add_url");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in add_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in add_url");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in add_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in add_url");
		return;
	}

	xmms_playlist_client_add_url ((xmms_playlist_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_add_collection (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to add_collection (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to add_collection");
		return;
	}
	const char * argval0;
	xmmsv_coll_t * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in add_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in add_collection");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in add_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in add_collection");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in add_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in add_collection");
		return;
	}
	if (!xmmsv_get_coll (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in add_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in add_collection");
		return;
	}

	xmms_playlist_client_add_collection ((xmms_playlist_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_remove_entry (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to remove_entry (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to remove_entry");
		return;
	}
	const char * argval0;
	gint32 argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in remove_entry");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in remove_entry");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in remove_entry");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in remove_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in remove_entry");
		return;
	}

	xmms_playlist_client_remove_entry ((xmms_playlist_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_move_entry (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to move_entry (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to move_entry");
		return;
	}
	const char * argval0;
	gint32 argval1;
	gint32 argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in move_entry");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in move_entry");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in move_entry");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in move_entry");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in move_entry");
		return;
	}
	if (!xmmsv_get_int (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in move_entry");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in move_entry");
		return;
	}

	xmms_playlist_client_move_entry ((xmms_playlist_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_list_entries (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to list_entries (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to list_entries");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in list_entries");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in list_entries");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in list_entries");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in list_entries");
		return;
	}

	arg->retval = xmms_playlist_client_list_entries ((xmms_playlist_t *) object, argval0, &arg->error);
}


static void
__int_xmms_cmd_current_pos (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to current_pos (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to current_pos");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in current_pos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in current_pos");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in current_pos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in current_pos");
		return;
	}

	arg->retval = xmms_playlist_client_current_pos ((xmms_playlist_t *) object, argval0, &arg->error);
}


static void
__int_xmms_cmd_current_active (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to current_active (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to current_active");
		return;
	}


	gchar * retval = xmms_playlist_client_current_active ((xmms_playlist_t *) object, &arg->error);
	if (retval != NULL) {
		arg->retval = xmms_convert_and_kill_string (retval);
	}
}


static void
__int_xmms_cmd_insert_url (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to insert_url (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to insert_url");
		return;
	}
	const char * argval0;
	gint32 argval1;
	const char * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in insert_url");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in insert_url");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in insert_url");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in insert_url");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in insert_url");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in insert_url");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in insert_url");
		return;
	}

	xmms_playlist_client_insert_url ((xmms_playlist_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_insert_collection (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to insert_collection (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to insert_collection");
		return;
	}
	const char * argval0;
	gint32 argval1;
	xmmsv_coll_t * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in insert_collection");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in insert_collection");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in insert_collection");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in insert_collection");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in insert_collection");
		return;
	}
	if (!xmmsv_get_coll (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in insert_collection");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in insert_collection");
		return;
	}

	xmms_playlist_client_insert_collection ((xmms_playlist_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_load (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to load (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to load");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in load");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in load");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in load");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in load");
		return;
	}

	xmms_playlist_client_load ((xmms_playlist_t *) object, argval0, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_radd (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to radd (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to radd");
		return;
	}
	const char * argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in radd");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in radd");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in radd");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in radd");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in radd");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in radd");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in radd");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in radd");
		return;
	}

	xmms_playlist_client_radd ((xmms_playlist_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_rinsert (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to rinsert (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to rinsert");
		return;
	}
	const char * argval0;
	gint32 argval1;
	const char * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in rinsert");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in rinsert");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in rinsert");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in rinsert");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in rinsert");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in rinsert");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in rinsert");
		return;
	}

	xmms_playlist_client_rinsert ((xmms_playlist_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}



static void
xmms_playlist_register_ipc_commands (xmms_object_t *playlist_object)
{
	xmms_ipc_object_register (2, playlist_object);

	xmms_object_cmd_add (playlist_object, 32, __int_xmms_cmd_replace);
	xmms_object_cmd_add (playlist_object, 33, __int_xmms_cmd_set_next);
	xmms_object_cmd_add (playlist_object, 34, __int_xmms_cmd_set_next_rel);
	xmms_object_cmd_add (playlist_object, 35, __int_xmms_cmd_add_url);
	xmms_object_cmd_add (playlist_object, 36, __int_xmms_cmd_add_collection);
	xmms_object_cmd_add (playlist_object, 37, __int_xmms_cmd_remove_entry);
	xmms_object_cmd_add (playlist_object, 38, __int_xmms_cmd_move_entry);
	xmms_object_cmd_add (playlist_object, 39, __int_xmms_cmd_list_entries);
	xmms_object_cmd_add (playlist_object, 40, __int_xmms_cmd_current_pos);
	xmms_object_cmd_add (playlist_object, 41, __int_xmms_cmd_current_active);
	xmms_object_cmd_add (playlist_object, 42, __int_xmms_cmd_insert_url);
	xmms_object_cmd_add (playlist_object, 43, __int_xmms_cmd_insert_collection);
	xmms_object_cmd_add (playlist_object, 44, __int_xmms_cmd_load);
	xmms_object_cmd_add (playlist_object, 45, __int_xmms_cmd_radd);
	xmms_object_cmd_add (playlist_object, 46, __int_xmms_cmd_rinsert);

	xmms_ipc_broadcast_register (playlist_object, 0);
	xmms_ipc_broadcast_register (playlist_object, 6);
	xmms_ipc_broadcast_register (playlist_object, 7);

}

static void
xmms_playlist_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (0);
	xmms_ipc_broadcast_unregister (6);
	xmms_ipc_broadcast_unregister (7);


	xmms_ipc_object_unregister (2);
}
