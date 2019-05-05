#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GLES3/gl31.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl3ext.h>
#include <GLES/gl.h>
#include <GLES/GL.h>
#include <GLES/glplatform.h>
#include <GLES/glext.h>


#include <android/log.h>
#include <stdio.h>
#include <android/bitmap.h>
#include <cstring>
#include <unistd.h>
#include <scoped_allocator>

#define  LOG_TAG    "DEBUG"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void createContext(void);

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_brg_1img_MainActivity_changeImage(
        JNIEnv *env,
        jobject /* this */,
        jbyteArray image) {

    createContext();

    auto len = env->GetArrayLength(image);
    unsigned char* buf = new unsigned char[len];
    env->GetByteArrayRegion (image, 0, len, reinterpret_cast<jbyte*>(buf));


    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, len, 0, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, len, buf);

    GLint size = 0;
    glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &size);
    if(len != size)
    {
        glDeleteBuffers(1, &ssbo);
        LOGE("SSBO ERROR");
        return NULL;
    }


    return image;

}

void createContext(void) {

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

    LOGI("Create context...");

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
}
