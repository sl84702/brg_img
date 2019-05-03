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
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
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

    auto a = 1;
    auto b = 2;
    if (a > b) {
        return env->NewStringUTF(one.c_str());
    }

    if (b > a) {
        return env->NewStringUTF(two.c_str());
    }

    return env->NewStringUTF(hello.c_str());
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
//    LOGD("imageID openBitmap: %d", bitmap);


    //
    //getting bitmap info:
    //
    LOGD("reading bitmap info...");
    AndroidBitmapInfo info;
    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    LOGD("width:%d height:%d stride:%d", info.width, info.height, info.stride);
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        LOGE("Bitmap format is not RGBA_8888!");
        return NULL;
    }
    //
    //read pixels of bitmap into native memory :
    //
    LOGD("reading bitmap pixels...");
    void* bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }

    return bitmap;

}