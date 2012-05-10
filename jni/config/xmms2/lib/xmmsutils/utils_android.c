/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003-2012 XMMS2 Team
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */

/** @file
 * Miscellaneous internal utility functions.
 */

#include <jni.h>

#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>

#include "xmms_configuration.h"
#include "xmmsc/xmmsc_util.h"
#include "xmmspriv/xmms_plugin.h"
#include "xmmspriv/xmms_config.h"
#include "xmmspriv/xmms_playlist.h"
#include "xmmspriv/xmms_playlist_updater.h"
#include "xmmspriv/xmms_collsync.h"
#include "xmmspriv/xmms_collection.h"
#include "xmmspriv/xmms_signal.h"
#include "xmmspriv/xmms_symlink.h"
#include "xmmspriv/xmms_checkroot.h"
#include "xmmspriv/xmms_thread_name.h"
#include "xmmspriv/xmms_medialib.h"
#include "xmmspriv/xmms_mediainfo.h"
#include "xmmspriv/xmms_output.h"
#include "xmmspriv/xmms_ipc.h"
#include "xmmspriv/xmms_log.h"
#include "xmmspriv/xmms_xform.h"
#include "xmmspriv/xmms_bindata.h"
#include "xmmspriv/xmms_utils.h"

extern JavaVM *global_jvm; 
const char *
android_dir_get (const char *default_dir, char *buf, int len)
{
	JNIEnv *env = NULL;
	if ((*global_jvm)->GetEnv (global_jvm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
		return NULL;
	}

	jclass clazz = (*env)->FindClass (env, "org.xmms2.server.Server");
	jmethodID method = (*env)->GetStaticMethodID (env, clazz, "getConfigDir", "()[C");

	if (method) {
		jboolean is_copy = 1;

		jcharArray dir = (*env)->CallStaticObjectMethod (env, clazz, method);
		jchar *elems = (*env)->GetCharArrayElements (env, dir, &is_copy);
		if (elems) {
			snprintf(buf, len, "%s", elems);
		}

		(*env)->ReleaseCharArrayElements (env, dir, elems, JNI_ABORT);
	}

	return buf;
}

/**
 * Get the absolute path to the user cache dir.
 * @param buf a char buffer
 * @param len the lenght of buf (XMMS_PATH_MAX is a good choice)
 * @return A pointer to buf, or NULL if an error occurred.
**/
const char *
xmms_usercachedir_get (char *buf, int len)
{
    return android_dir_get (USERCACHEDIR, buf, len);
}

/**
 * Get the absolute path to the user config dir.
 *
 * @param buf A char buffer
 * @param len The length of buf (XMMS_PATH_MAX is a good choice)
 * @return A pointer to buf, or NULL if an error occurred.
 */
const char *
xmms_userconfdir_get (char *buf, int len)
{
    return android_dir_get (USERCONFDIR, buf, len);
}

/**
 * Get the fallback connection path (if XMMS_PATH is not accessible)
 *
 * @param buf A char buffer
 * @param len The length of buf (XMMS_PATH_MAX is a good choice)
 * @return A pointer to buf, or NULL if an error occured.
 */
const char *
xmms_fallback_ipcpath_get (char *buf, int len)
{
	struct passwd *pw;

	pw = getpwuid (getuid ());
	if (!pw || !pw->pw_name) {
		return NULL;
	}

	snprintf (buf, len, "unix:///tmp/xmms-ipc-%s", pw->pw_name);

	return buf;
}

/**
 * Sleep for n milliseconds.
 *
 * @param n The number of milliseconds to sleep.
 * @return true when we waited the full time, false otherwise.
 */
bool
xmms_sleep_ms (int n)
{
	struct timespec sleeptime;

	sleeptime.tv_sec = (time_t) (n / 1000);
	sleeptime.tv_nsec = (n % 1000) * 1000000;

	while (nanosleep (&sleeptime, &sleeptime) == -1) {
		if (errno != EINTR) {
			return false;
		}
	}

	return true;
}
