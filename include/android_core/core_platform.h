#pragma once

#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif

struct CorePlatform {
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
};

#ifdef __cplusplus
}
#endif
