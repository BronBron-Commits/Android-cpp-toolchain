#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Fixed-timestep parameters */
enum {
    CORE_TICK_HZ = 60,
    CORE_TICK_NS = 1000000000ull / CORE_TICK_HZ
};

/*
 * Called once before the loop starts
 */
void core_init(void);

/*
 * Advance simulation by exactly one tick.
 * Must be deterministic.
 */
void core_tick(void);

/*
 * Optional render hook.
 * No simulation allowed here.
 */
void core_render(void);

#ifdef __cplusplus
}
#endif
