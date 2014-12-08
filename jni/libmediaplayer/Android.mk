LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include \
    $(LOCAL_PATH)/../libffmpeg

LOCAL_SRC_FILES += \
    packetqueue.cpp \
    output.cpp \
    mediaplayer.cpp \
    decoder.cpp \
    decoder_audio.cpp \
    decoder_video.cpp \
    thread.cpp

LOCAL_STATIC_LIBRARIES := libpostproc libswscale libavformat libavcodec libavutil
LOCAL_LDLIBS := -llog
LOCAL_MODULE := libmediaplayer

include $(BUILD_STATIC_LIBRARY)
