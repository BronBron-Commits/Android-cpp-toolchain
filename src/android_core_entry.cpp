#include <android/native_activity.h>
#include <android/log.h>
#include <time.h>

#include "android_core/core_abi.h"
#include "android_core/core_platform.h"
#include "android_core/core_loop.h"

extern "C" uint64_t example_get(void);

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

    core_init();

    uint64_t last_time = now_ns();
    uint64_t acc = 0;
    uint64_t last_log_tick = 0;

    for (;;)
    {
        uint64_t cur = now_ns();
        uint64_t dt = cur - last_time;
        last_time = cur;
        acc += dt;

        while (acc >= CORE_TICK_NS)
        {
            core_tick();
            acc -= CORE_TICK_NS;
        }

        if (example_get() - last_log_tick >= CORE_TICK_HZ)
        {
            last_log_tick = example_get();
            LOGI("stable counter = %llu",
                 (unsigned long long)example_get());
        }
    }
}
