# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS

LOCAL_C_INCLUDES += \
    G:/android_project/SurfaceDraw/jni/libffmpeg \
    G:/android_project/SurfaceDraw/jni/libmediaplayer

LOCAL_SRC_FILES += \
    com_example_surfacedraw_MainActivity.cpp

LOCAL_SHARED_LIBRARIES := libjniaudio libjnivideo
LOCAL_STATIC_LIBRARIES := libmediaplayer libpostproc libswscale libavformat libavcodec libavutil
LOCAL_LDLIBS := -llog
LOCAL_MODULE := ffmpeg-jni

include $(BUILD_SHARED_LIBRARY)