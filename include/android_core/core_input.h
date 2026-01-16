#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CORE_INPUT_NONE   = 0,
    CORE_INPUT_TOUCH  = 1,
    CORE_INPUT_BUTTON = 2
} CoreInputType;

typedef struct {
    float x;
    float y;
    uint8_t down;
} CoreTouchInput;

typedef struct {
    uint32_t id;
    uint8_t down;
} CoreButtonInput;

typedef struct {
    uint64_t tick;
    CoreInputType type;

    union {
        CoreTouchInput  touch;
        CoreButtonInput button;
    } data;
} CoreInputEvent;

void core_input_push(const CoreInputEvent* ev);

#ifdef __cplusplus
}
#endif
