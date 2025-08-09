#include "../../core/xeza.h"
#include <stdio.h>

int main() {
    int status;
    status = xeza_init();

    if (status == XEZA_ERR) {
        fprintf(stderr, "Xeza initialization failed\n");
        return XEZA_ERR;
    }

    window_t window;
    window.height = 800;
    window.width = 600;
    window.title = "Triangle";

    status = xeza_create_window(&window);
    if (status == XEZA_ERR) {
        fprintf(stderr, "Xeza window initialization failed\n");
        return XEZA_ERR;
    }

    color_t color;
    color.r = 0.1f;
    color.g = 0.4f;
    color.b = 0.5f;

    while (!xeza_main_loop(&window)) {
        xeza_window_clear();
        xeza_window_set_color(color);


        xeza_window_poll_events();
        xeza_window_swap_buffers(&window);
    }
    
    return 0;
}
