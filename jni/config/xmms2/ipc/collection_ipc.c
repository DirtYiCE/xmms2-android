/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_get (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to get (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to get");
		return;
	}
	const char * argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in get");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in get");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in get");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in get");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in get");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in get");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in get");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in get");
		return;
	}

	xmmsv_coll_t * retval = xmms_collection_client_get ((xmms_coll_dag_t *) object, argval0, argval1, &arg->error);
	if (retval != NULL) {
		arg->retval = xmmsv_new_coll (retval);
	}
}


static void
__int_xmms_cmd_list (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to list (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to list");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in list");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in list");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in list");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in list");
		return;
	}

	arg->retval = xmms_convert_and_kill_list (xmms_collection_client_list ((xmms_coll_dag_t *) object, argval0, &arg->error));
}


static void
__int_xmms_cmd_save (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to save (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to save");
		return;
	}
	const char * argval0;
	const char * argval1;
	xmmsv_coll_t * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in save");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in save");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in save");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in save");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in save");
		return;
	}
	if (!xmmsv_get_coll (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in save");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in save");
		return;
	}

	xmms_collection_client_save ((xmms_coll_dag_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_remove (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to remove (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to remove");
		return;
	}
	const char * argval0;
	const char * argval1;

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
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in remove");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in remove");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in remove");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in remove");
		return;
	}

	xmms_collection_client_remove ((xmms_coll_dag_t *) object, argval0, argval1, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_find (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to find (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to find");
		return;
	}
	gint32 argval0;
	const char * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in find");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in find");
		return;
	}
	if (!xmmsv_get_int (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in find");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in find");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in find");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in find");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in find");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in find");
		return;
	}

	arg->retval = xmms_convert_and_kill_list (xmms_collection_client_find ((xmms_coll_dag_t *) object, argval0, argval1, &arg->error));
}


static void
__int_xmms_cmd_rename (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 3) {
		XMMS_DBG ("Wrong number of arguments to rename (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to rename");
		return;
	}
	const char * argval0;
	const char * argval1;
	const char * argval2;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in rename");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in rename");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in rename");
		return;
	}
	if (!xmmsv_get_string (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in rename");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in rename");
		return;
	}
	if (!xmmsv_get_string (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in rename");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in rename");
		return;
	}

	xmms_collection_client_rename ((xmms_coll_dag_t *) object, argval0, argval1, argval2, &arg->error);
	arg->retval = xmmsv_new_none ();
}


static void
__int_xmms_cmd_query (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 2) {
		XMMS_DBG ("Wrong number of arguments to query (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to query");
		return;
	}
	xmmsv_coll_t * argval0;
	xmmsv_t * argval1;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in query");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in query");
		return;
	}
	if (!xmmsv_get_coll (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in query");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in query");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in query");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in query");
		return;
	}
	argval1 = t;

	arg->retval = xmms_collection_client_query ((xmms_coll_dag_t *) object, argval0, argval1, &arg->error);
}


static void
__int_xmms_cmd_query_infos (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 6) {
		XMMS_DBG ("Wrong number of arguments to query_infos (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to query_infos");
		return;
	}
	xmmsv_coll_t * argval0;
	gint32 argval1;
	gint32 argval2;
	xmmsv_t * argval3;
	xmmsv_t * argval4;
	xmmsv_t * argval5;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in query_infos");
		return;
	}
	if (!xmmsv_get_coll (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in query_infos");
		return;
	}
	if (!xmmsv_list_get (arg->args, 1, &t)) {
		XMMS_DBG ("Missing arg 1 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 1 in query_infos");
		return;
	}
	if (!xmmsv_get_int (t, &argval1)) {
		XMMS_DBG ("Error parsing arg 1 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 1 in query_infos");
		return;
	}
	if (!xmmsv_list_get (arg->args, 2, &t)) {
		XMMS_DBG ("Missing arg 2 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 2 in query_infos");
		return;
	}
	if (!xmmsv_get_int (t, &argval2)) {
		XMMS_DBG ("Error parsing arg 2 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 2 in query_infos");
		return;
	}
	if (!xmmsv_list_get (arg->args, 3, &t)) {
		XMMS_DBG ("Missing arg 3 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 3 in query_infos");
		return;
	}
	argval3 = t;
	if (!xmmsv_list_get (arg->args, 4, &t)) {
		XMMS_DBG ("Missing arg 4 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 4 in query_infos");
		return;
	}
	argval4 = t;
	if (!xmmsv_list_get (arg->args, 5, &t)) {
		XMMS_DBG ("Missing arg 5 in query_infos");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 5 in query_infos");
		return;
	}
	argval5 = t;

	arg->retval = xmms_collection_client_query_infos ((xmms_coll_dag_t *) object, argval0, argval1, argval2, argval3, argval4, argval5, &arg->error);
}


static void
__int_xmms_cmd_idlist_from_playlist (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	xmmsv_t *t;
	if (xmmsv_list_get_size (arg->args) != 1) {
		XMMS_DBG ("Wrong number of arguments to idlist_from_playlist (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to idlist_from_playlist");
		return;
	}
	const char * argval0;

	if (!xmmsv_list_get (arg->args, 0, &t)) {
		XMMS_DBG ("Missing arg 0 in idlist_from_playlist");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Missing arg 0 in idlist_from_playlist");
		return;
	}
	if (!xmmsv_get_string (t, &argval0)) {
		XMMS_DBG ("Error parsing arg 0 in idlist_from_playlist");
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Error parsing arg 0 in idlist_from_playlist");
		return;
	}

	xmmsv_coll_t * retval = xmms_collection_client_idlist_from_playlist ((xmms_coll_dag_t *) object, argval0, &arg->error);
	if (retval != NULL) {
		arg->retval = xmmsv_new_coll (retval);
	}
}


static void
__int_xmms_cmd_sync (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to sync (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to sync");
		return;
	}


	xmms_collection_client_sync ((xmms_coll_dag_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}



static void
xmms_collection_register_ipc_commands (xmms_object_t *collection_object)
{
	xmms_ipc_object_register (6, collection_object);

	xmms_object_cmd_add (collection_object, 32, __int_xmms_cmd_get);
	xmms_object_cmd_add (collection_object, 33, __int_xmms_cmd_list);
	xmms_object_cmd_add (collection_object, 34, __int_xmms_cmd_save);
	xmms_object_cmd_add (collection_object, 35, __int_xmms_cmd_remove);
	xmms_object_cmd_add (collection_object, 36, __int_xmms_cmd_find);
	xmms_object_cmd_add (collection_object, 37, __int_xmms_cmd_rename);
	xmms_object_cmd_add (collection_object, 38, __int_xmms_cmd_query);
	xmms_object_cmd_add (collection_object, 39, __int_xmms_cmd_query_infos);
	xmms_object_cmd_add (collection_object, 40, __int_xmms_cmd_idlist_from_playlist);
	xmms_object_cmd_add (collection_object, 41, __int_xmms_cmd_sync);

	xmms_ipc_broadcast_register (collection_object, 11);

}

static void
xmms_collection_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (11);


	xmms_ipc_object_unregister (6);
}
