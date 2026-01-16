#include "android_core/core_lifecycle.h"

#define MAX_LIFECYCLE_EVENTS 64

static CoreLifecycleEvent queue[MAX_LIFECYCLE_EVENTS];
static uint32_t head = 0;
static uint32_t tail = 0;

extern "C" void core_lifecycle_push(const CoreLifecycleEvent* ev)
{
    uint32_t next = (tail + 1) % MAX_LIFECYCLE_EVENTS;
    if (next == head)
        return;

    queue[tail] = *ev;
    tail = next;
}

void core_lifecycle_consume(void)
{
    while (head != tail)
    {
        const CoreLifecycleEvent* ev = &queue[head];

        /* TODO: react to lifecycle event */

        head = (head + 1) % MAX_LIFECYCLE_EVENTS;
    }
}
