LOCAL_PATH := $(call my-dir)

SOURCE_ROOT := jni
BUILD_SCRIPTS_DIR := $(SOURCE_ROOT)/build-scripts
CONFIG_PATH := $(LOCAL_PATH)/config

include $(BUILD_SCRIPTS_DIR)/Android.mk
