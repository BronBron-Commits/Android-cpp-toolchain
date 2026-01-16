#include <stdint.h>

static uint64_t counter = 0;

extern "C" void example_reset(void)
{
    counter = 0;
}

extern "C" void example_tick(void)
{
    counter++;
}

extern "C" uint64_t example_get(void)
{
    return counter;
}
