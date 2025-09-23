#ifndef STATE_H
#define STATE_H

#include "gfx.h"

typedef struct {
    camera_t camera;
    renderer_t renderer;
    window_t window;
} state_t;

#endif
