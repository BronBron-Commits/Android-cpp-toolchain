#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct ANativeActivity;
struct CorePlatform;

/*
 * core_main
 *
 * Entry point into the native core runtime.
 * This function must not return.
 */
void core_main(
    struct ANativeActivity* activity,
    const struct CorePlatform* platform
);

#ifdef __cplusplus
}
#endif
