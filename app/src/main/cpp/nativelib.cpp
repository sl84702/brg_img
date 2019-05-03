#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GLES3/gl31.h>

#include <android/log.h>
#include <stdio.h>
#include <android/bitmap.h>
#include <cstring>
#include <unistd.h>

#define  LOG_TAG    "DEBUG"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_brg_1img_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_brg_1img_MainActivity_hwToConsole(
        JNIEnv *env,
        jobject /* this */,
        jint n1,
        jint n2) {
    std::string hello = "Hello from C++";
    std::fstream fs;
    fs.open ("/Users/o.kulachenko/AndroidStudioProjects/brg_img/app/src/main/res/test.xml", std::fstream::in | std::fstream::out | std::fstream::app);
    fs << " more lorem ipsum";
    fs.close();

    std::string one = "11111111";
    std::string two = "22222222";
    LOGD("n1n1n1n1n1n1: ", n1);

    auto a = 1;
    auto b = 2;
    if (a > b) {
        return env->NewStringUTF(one.c_str());
    }

    if (b > a) {
        return env->NewStringUTF(two.c_str());
    }

    if (b == a) {
        return env->NewStringUTF(hello.c_str());
    }
}


extern "C" JNIEXPORT jint JNICALL
Java_com_example_brg_1img_MainActivity_viewImage(
        JNIEnv *env,
        jobject /* this */,
        jint imageID) {
    LOGD("imageID: %d", imageID);
    return imageID;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_brg_1img_MainActivity_openBitmap(
        JNIEnv *env,
        jobject /* this */,
        jobject bitmap) {
    LOGD("imageID openBitmap: %d", bitmap);
    return bitmap;
}