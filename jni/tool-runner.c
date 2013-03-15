#include <android/log.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *
load_lib (const char *lib)
{
    void *handle = dlopen (lib, RTLD_NOW | RTLD_GLOBAL);
    if (!handle)
    {
        __android_log_print (ANDROID_LOG_ERROR, "tool-runner", "dlopen (%s): %s", lib, strerror(errno));
    }

    return handle;
}

typedef int (*func)(int, char**);

int
main (int argc, char **argv)
{
    char path[4096];
    int ret = EXIT_FAILURE;
    void *handle;
    func m;

    if (argc < 4) {
        __android_log_print (ANDROID_LOG_ERROR, "tool-runner", "too few arguments");
        return EXIT_FAILURE;
    }
    snprintf (path, 4096, "%s/libglib-2.0.so", argv[1]);
    load_lib (path);
    snprintf (path, 4096, "%s/libgthread-2.0.so", argv[1]);
    load_lib (path);
    snprintf (path, 4096, "%s/lib%s.so", argv[1], argv[2]);
    handle = load_lib (path);
    if (!handle) {
        return EXIT_FAILURE;
    }
    *(void**)(&m) = dlsym (handle, "main");
    ret = m(2, argv+2);

    return ret;
}
