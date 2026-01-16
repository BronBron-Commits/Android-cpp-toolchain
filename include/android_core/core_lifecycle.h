#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CORE_LIFECYCLE_NONE = 0,
    CORE_LIFECYCLE_START,
    CORE_LIFECYCLE_STOP,
    CORE_LIFECYCLE_PAUSE,
    CORE_LIFECYCLE_RESUME,
    CORE_LIFECYCLE_SURFACE_CREATED,
    CORE_LIFECYCLE_SURFACE_DESTROYED,
    CORE_LIFECYCLE_SURFACE_RESIZED
} CoreLifecycleEventType;

typedef struct {
    CoreLifecycleEventType type;

    union {
        struct {
            uint32_t width;
            uint32_t height;
        } resize;
    };
} CoreLifecycleEvent;

/*
 * Push lifecycle event into the core.
 * Ordering is preserved.
 */
void core_lifecycle_push(const CoreLifecycleEvent* ev);

#ifdef __cplusplus
}
#endif
