/* This code is automatically generated from foobar. Do not edit. */

#include <xmmsc/xmmsv.h>

static void
xmms_mediainfo_reader_register_ipc_commands (xmms_object_t *mediainfo_reader_object)
{
	xmms_ipc_object_register (8, mediainfo_reader_object);


	xmms_ipc_broadcast_register (mediainfo_reader_object, 13);

	xmms_ipc_signal_register (mediainfo_reader_object, 14);
}

static void
xmms_mediainfo_reader_unregister_ipc_commands (void)
{
	xmms_ipc_broadcast_unregister (13);

	xmms_ipc_signal_unregister (14);

	xmms_ipc_object_unregister (8);
}
