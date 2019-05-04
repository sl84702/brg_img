#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GLES3/gl31.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES/gl.h>


#include <android/log.h>
#include <stdio.h>
#include <android/bitmap.h>
#include <cstring>
#include <unistd.h>

#define  LOG_TAG    "DEBUG"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_brg_1img_MainActivity_changeImage(
        JNIEnv *env,
        jobject /* this */,
        jobject bitmap) {

    //
    //getting bitmap info:
    //
    LOGD("reading bitmap info...");
    AndroidBitmapInfo info;
    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    LOGD("width:%d height:%d stride:%d", info.width, info.height, info.stride);
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888!");
        return NULL;
    }
    //
    //read pixels of bitmap into native memory :
    //
    LOGD("reading bitmap pixels...");
    void *bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }

    EGLConfig config;
    EGLint numConfigs;

    EGLint    contextAttribs[] =
            {
    #ifdef _OGLES3
                    EGL_CONTEXT_CLIENT_VERSION, 3,
    #else
                    EGL_CONTEXT_CLIENT_VERSION, 2,
    #endif
                    EGL_NONE /* terminator */
            };

    EGLint    configAttribs[] =
            {
                    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                    EGL_RED_SIZE,        8,
                    EGL_GREEN_SIZE,      8,
                    EGL_BLUE_SIZE,       8,
                    EGL_ALPHA_SIZE,      8,
                    EGL_BUFFER_SIZE,     32,
                    EGL_DEPTH_SIZE,      16,
                    EGL_STENCIL_SIZE,    8,
    #ifdef _OGLES3
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
    #else
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    #endif
                    EGL_NONE /* terminator */
            };

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == NULL) {
        LOGE("error get display");
    }

    if ( !eglInitialize(display, NULL, NULL) ) {
        LOGE("error Initialize display");
    }

    if( !eglChooseConfig(display, configAttribs, &config, 1, &numConfigs) ) {
        LOGE("error choose config");
    }


    EGLSurface surface = eglCreatePbufferSurface(display, config, NULL);
    if (surface == NULL) {
        LOGE("error create pbuffer surface");
    }


    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (surface == NULL) {
        LOGE("error create context");
    }

    if ( !eglMakeCurrent(display, surface, surface, context) ) {
        LOGE("error make current");
    }



    return bitmap;

}




