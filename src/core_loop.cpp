#include "android_core/core_loop.h"
#include "android_core/core_input.h"
#include "android_core/core_lifecycle.h"

extern void core_input_consume(uint64_t tick);
extern void core_lifecycle_consume(void);

/* example app hooks */
extern "C" void example_reset(void);
extern "C" void example_tick(void);

static uint64_t tick_counter = 0;

extern "C" void core_init(void)
{
    tick_counter = 0;
    example_reset();
}

extern "C" void core_tick(void)
{
    core_lifecycle_consume();
    core_input_consume(tick_counter);

    example_tick();
    tick_counter++;
}

extern "C" void core_render(void)
{
    /* no rendering yet */
}
