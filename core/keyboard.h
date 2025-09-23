#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include "window.h"

#define KEY_COUNT 256

typedef struct {
    bool forward;
    bool backward;
    bool right;
    bool left;
} movement_t;

typedef struct {
    int keys[4];
    movement_t movement;
} keyboard_t;

#endif
