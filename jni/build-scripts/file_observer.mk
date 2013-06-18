include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	file_observer.cpp

LOCAL_MODULE := file_observer
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
