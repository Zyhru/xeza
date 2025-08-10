#ifndef XEZA_H
#define XEZA_H

#include "window.h"

#define XEZA_ERR -1

struct xeza_shutdown_state {
    window_t *window;
};

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
} xeza_object;

int xeza_init();
bool xeza_main_loop(window_t *window);
color_t xeza_create_color(float r, float g, float b);

void xeza_shutdown(struct xeza_shutdown_state *shutdown_state);

#endif
