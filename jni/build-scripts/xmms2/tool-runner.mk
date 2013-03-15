include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    tool-runner.c

LOCAL_LDLIBS := -llog
LOCAL_MODULE := tool-runner

include $(BUILD_EXECUTABLE)
