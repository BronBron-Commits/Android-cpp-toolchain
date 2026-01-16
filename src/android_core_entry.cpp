#include <android/native_activity.h>
#include <android/log.h>
#include <time.h>

#include "android_core/core_abi.h"
#include "android_core/core_platform.h"
#include "android_core/core_loop.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CORE", __VA_ARGS__)

static uint64_t now_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + ts.tv_nsec;
}

extern "C" void core_main(
    ANativeActivity* activity,
    const CorePlatform* platform)
{
    (void)activity;
    (void)platform;

    LOGI("core_main entered");

    core_init();

    uint64_t last_time = now_ns();
    uint64_t accumulator = 0;

    for (;;)
    {
        uint64_t current = now_ns();
        uint64_t delta = current - last_time;
        last_time = current;

        accumulator += delta;

        while (accumulator >= CORE_TICK_NS)
        {
            core_tick();
            accumulator -= CORE_TICK_NS;
        }

        core_render();
    }
}
