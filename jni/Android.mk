LOCAL_PATH := $(call my-dir)

SOURCE_ROOT := jni
BUILD_SCRIPTS_DIR := $(SOURCE_ROOT)/build-scripts
CONFIG_PATH := $(LOCAL_PATH)/config
ifeq ($(APP_OPTIM),debug)
DEBUG_FLAG := -DDEBUG
else
DEBUG_FLAG := 
endif

include $(BUILD_SCRIPTS_DIR)/Android.mk
