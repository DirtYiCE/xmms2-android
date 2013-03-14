/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>
static void
__int_xmms_cmd_sync (xmms_object_t *object, xmms_object_cmd_arg_t *arg)
{
	if (xmmsv_list_get_size (arg->args) != 0) {
		XMMS_DBG ("Wrong number of arguments to sync (%d)", xmmsv_list_get_size (arg->args));
		xmms_error_set (&arg->error, XMMS_ERROR_INVAL, "Wrong number of arguments to sync");
		return;
	}


	xmms_coll_sync_client_sync ((xmms_coll_sync_t *) object, &arg->error);
	arg->retval = xmmsv_new_none ();
}



static void
xmms_coll_sync_register_ipc_commands (xmms_object_t *coll_sync_object)
{
	xmms_ipc_object_register (11, coll_sync_object);

	xmms_object_cmd_add (coll_sync_object, 32, __int_xmms_cmd_sync);


}

static void
xmms_coll_sync_unregister_ipc_commands (void)
{


	xmms_ipc_object_unregister (11);
}
