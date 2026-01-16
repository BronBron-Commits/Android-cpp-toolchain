#include "android_core/core_loop.h"

static uint64_t tick_counter = 0;

extern "C" void core_init(void)
{
    tick_counter = 0;
}

extern "C" void core_tick(void)
{
    /* Deterministic simulation step */
    tick_counter++;
}

extern "C" void core_render(void)
{
    /* Rendering hook (optional) */
}
