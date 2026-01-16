#include "android_core/core_input.h"

#define MAX_INPUT_EVENTS 256

static CoreInputEvent queue[MAX_INPUT_EVENTS];
static uint32_t head = 0;
static uint32_t tail = 0;

extern "C" void core_input_push(const CoreInputEvent* ev)
{
    uint32_t next = (tail + 1) % MAX_INPUT_EVENTS;
    if (next == head)
        return; /* drop if full */

    queue[tail] = *ev;
    tail = next;
}

void core_input_consume(uint64_t tick)
{
    while (head != tail)
    {
        CoreInputEvent* ev = &queue[head];
        if (ev->tick > tick)
            break;

        /* TODO: dispatch to simulation */

        head = (head + 1) % MAX_INPUT_EVENTS;
    }
}
