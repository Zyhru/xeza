#include "xeza.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int xeza_init() {
    int res = 0;

    // initialize all components
    res = xeza_context_init();
    printf("res %d\n", res);

    if (res == XEZA_ERR) {
        fprintf(stderr, "Failed to initialize Xeza context\n");
        res = XEZA_ERR;
    }

    return res;
}

bool xeza_main_loop(window_t *w) {
    bool flag = glfwWindowShouldClose(w->win);
    return flag;
}

void xeza_shutdown(struct xeza_shutdown_state *zst) {
    glfwDestroyWindow(zst->window->win);

}
