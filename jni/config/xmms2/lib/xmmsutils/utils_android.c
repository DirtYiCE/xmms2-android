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

extern JavaVM *global_jvm; 
extern jobject server_object;
const char *
android_dir_get (const char *default_dir, char *buf, int len)
{
	JNIEnv *env = NULL;
	if ((*global_jvm)->GetEnv (global_jvm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
		return NULL;
	}

	jclass clazz = (*env)->FindClass (env, "org/xmms2/server/Server");
	jmethodID method = (*env)->GetMethodID (env, clazz, "getConfigDir", "()Ljava/lang/String;");

	if (method) {
		jobject *dir_obj = (*env)->CallObjectMethod (env, server_object, method);
		const char *elems = (*env)->GetStringUTFChars (env, dir_obj, 0);

		if (elems) {
			snprintf(buf, len, "%s/%s", elems, default_dir);
		}

		(*env)->ReleaseStringUTFChars (env, dir_obj, elems);
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
	snprintf (buf, len, "tcp://127.0.0.1:9667");

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
