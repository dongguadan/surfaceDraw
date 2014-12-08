/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <mediaplayer.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */

struct fields_t {
    jfieldID    context;
    jmethodID   post_event;
};
static fields_t fields;
static MediaPlayer* g_mediaplayer;
extern "C" {
int jniRegisterNativeMethods(JNIEnv* env,
                             const char* className,
                             const JNINativeMethod* gMethods,
                             int numMethods)
{
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_ERR;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_ERR;
    }
    return JNI_OK;
}
}

jstring stringFromJNI( JNIEnv* env, jobject thiz)
{
	char str[25];
    sprintf(str, "%d", avcodec_version());
    return env->NewStringUTF(str);
}

jstring avcodecregisterall(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
	avcodec_register_all();
    sprintf(str, "%s", "avcodecregisterall OK");
	return env->NewStringUTF(str);
}

jstring avregisterall(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
	av_register_all();
    sprintf(str, "%s", "av_register_all OK");
	return env->NewStringUTF(str);
}

jstring init(JNIEnv *env)
{
	char str[25] = { 0 };
    sprintf(str, "%s", "init");
	return env->NewStringUTF(str);
}

MediaPlayer* setMediaPlayer(JNIEnv* env, jobject thiz, MediaPlayer* player)
{
	if (player != NULL)
	{
		g_mediaplayer = (MediaPlayer*)player;
	}
}

jstring setup(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
    MediaPlayer* mp = new MediaPlayer();
    if (mp == NULL) {
        sprintf(str, "%s", "setup error");
    	return env->NewStringUTF(str);
    }
    setMediaPlayer(env, thiz, mp);
    sprintf(str, "%s", "setup");
	return env->NewStringUTF(str);
}

jstring release(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
    sprintf(str, "%s", "release");
	return env->NewStringUTF(str);
}

MediaPlayer* getMediaPlayer(JNIEnv* env, jobject thiz)
{
	if (g_mediaplayer != NULL)
	{
		return (MediaPlayer*)g_mediaplayer;
	}
	return NULL;
}

jstring prepare(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    mp->prepare();
    sprintf(str, "%s", "prepare");
	return env->NewStringUTF(str);
}

jstring start(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        sprintf(str, "%s", "start error");
    	return env->NewStringUTF(str);
    }
    mp->start();
    sprintf(str, "%s", "start");
	return env->NewStringUTF(str);
}

jstring stop(JNIEnv *env, jobject thiz)
{
	char str[25] = { 0 };
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        sprintf(str, "%s", "stop error");
    	return env->NewStringUTF(str);
    }
    mp->stop();
    sprintf(str, "%s", "stop");
	return env->NewStringUTF(str);
}

void setDataSourceAndHeaders(
        JNIEnv *env, jobject thiz, jstring path, jobject headers) {
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        return;
    }

    if (path == NULL) {
        return;
    }

    const char *pathStr = env->GetStringUTFChars(path, NULL);
    if (pathStr == NULL) {  // Out of memory
        return;
    }

    status_t opStatus = mp->setDataSource(pathStr);

    // Make sure that local ref is released before a potential exception
    env->ReleaseStringUTFChars(path, pathStr);
}

jstring setDataSource(JNIEnv *env, jobject thiz, jstring path)
{
	char str[25] = { 0 };
	setDataSourceAndHeaders(env, thiz, path, 0);
    sprintf(str, "%s", "setDataSource");
	return env->NewStringUTF(str);
}

jstring setVideoSurface(JNIEnv *env, jobject thiz, jobject jsurface)
{
	char str[50] = { 0 };
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        sprintf(str, "%s", "setVideoSurface error");
    	return env->NewStringUTF(str);
    }
	if (jsurface == NULL ) {
        sprintf(str, "%s", "setVideoSurface error");
    	return env->NewStringUTF(str);
    }
	mp->setVideoSurface(env, jsurface);
    sprintf(str, "%s", "setVideoSurface");
	return env->NewStringUTF(str);
}

static JNINativeMethod methods[] = {
		{ "native_avcodecregisteral",    "()Ljava/lang/String;", (jstring)avcodecregisterall },
		{ "native_avregisteral",         "()Ljava/lang/String;", (jstring)avregisterall },
	    { "native_init",                 "()Ljava/lang/String;", (jstring)init},
	    { "native_setup",                "()Ljava/lang/String;", (jstring)setup},
	    { "native_release",              "()Ljava/lang/String;", (jstring)release},
	    { "native_setDataSource",        "(Ljava/lang/String;)Ljava/lang/String;",     (jstring)setDataSource},
	    { "native_setVideoSurface",      "(Landroid/view/Surface;)Ljava/lang/String;", (jstring)setVideoSurface},
		{ "native_prepare",              "()Ljava/lang/String;", (jstring)prepare},
	    { "native_start",                "()Ljava/lang/String;", (jstring)start},
	    { "native_stop",                 "()Ljava/lang/String;", (jstring)stop},
		{ "native_stringFromJNI",        "()Ljava/lang/String;", (jstring)stringFromJNI },
};//may the underline of the function have problems

int register_android_example_MainActivity(JNIEnv *env) {
	return jniRegisterNativeMethods(env, "com/example/surfacedraw/MainActivity", methods, sizeof(methods) / sizeof(methods[0]));//extern c
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = JNI_ERR;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return JNI_ERR;
    }

    if(register_android_example_MainActivity(env) != JNI_OK) {
        goto end;
    }

    result = JNI_VERSION_1_4;

end:
    return result;
}

