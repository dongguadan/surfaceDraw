LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libjnivideo.so
LOCAL_MODULE := libjnivideo
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libjniaudio.so
LOCAL_MODULE := libjniaudio
include $(PREBUILT_SHARED_LIBRARY)
