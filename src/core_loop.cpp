#include "android_core/core_loop.h"
#include "android_core/core_input.h"
#include "android_core/core_lifecycle.h"

extern void core_input_consume(uint64_t tick);
extern void core_lifecycle_consume(void);

static uint64_t tick_counter = 0;

extern "C" void core_init(void)
{
    tick_counter = 0;
}

extern "C" void core_tick(void)
{
    core_lifecycle_consume();
    core_input_consume(tick_counter);

    tick_counter++;
}

extern "C" void core_render(void)
{
    /* Rendering hook */
}
