#include "android_core/core_lifecycle.h"
#include "android_core/core_input.h"
#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "android_core/core_abi.h"
#include "android_core/core_platform.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "LOADER", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "LOADER", __VA_ARGS__)

static EGLDisplay egl_display;
static EGLContext egl_context;
static EGLSurface egl_surface;

static int init_egl(ANativeWindow* window, CorePlatform* out)
{
    EGLint major, minor;
    EGLint num_configs;
    EGLConfig config;

    const EGLint config_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_RED_SIZE,        8,
        EGL_GREEN_SIZE,      8,
        EGL_BLUE_SIZE,       8,
        EGL_ALPHA_SIZE,      8,
        EGL_DEPTH_SIZE,      16,
        EGL_NONE
    };

    const EGLint ctx_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (egl_display == EGL_NO_DISPLAY) return 0;

    if (!eglInitialize(egl_display, &major, &minor)) return 0;

    if (!eglChooseConfig(
            egl_display,
            config_attribs,
            &config,
            1,
            &num_configs))
        return 0;

    egl_context = eglCreateContext(
        egl_display,
        config,
        EGL_NO_CONTEXT,
        ctx_attribs);

    if (egl_context == EGL_NO_CONTEXT) return 0;

    egl_surface = eglCreateWindowSurface(
        egl_display,
        config,
        window,
        NULL);

    if (egl_surface == EGL_NO_SURFACE) return 0;

    if (!eglMakeCurrent(
            egl_display,
            egl_surface,
            egl_surface,
            egl_context))
        return 0;

    out->display = egl_display;
    out->context = egl_context;
    out->surface = egl_surface;

    LOGI("EGL initialized (%d.%d)", major, minor);
    return 1;
}

typedef void (*core_entry_fn)(
    ANativeActivity*,
    const CorePlatform*);

void ANativeActivity_onCreate(
    ANativeActivity* activity,
    void* savedState,
    size_t savedStateSize)
{
    (void)savedState;
    (void)savedStateSize;

    LOGI("Native loader starting");

    CorePlatform platform = {};

    if (!init_egl(activity->window, &platform)) {
        LOGE("EGL initialization failed");
        return;
    }

    void* handle = dlopen("libcore.so", RTLD_NOW);
    if (!handle) {
        LOGE("dlopen failed: %s", dlerror());
        return;
    }

    core_entry_fn core_main =
        (core_entry_fn)dlsym(handle, "core_main");

    if (!core_main) {
        LOGE("dlsym failed: %s", dlerror());
        return;
    }

    LOGI("Transferring control to core");
    core_main(activity, &platform);
}
