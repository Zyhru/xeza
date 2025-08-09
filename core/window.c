#include "window.h"
#include "xeza.h"

int xeza_context_init() {
    printf("initializing ctx..\n");
    int res = 0;
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        res = XEZA_ERR;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    printf("loaded glfw..\n");
    return res;
}

int xeza_create_window(window_t *w) {
    int res = 0;

    w->win = glfwCreateWindow(w->width, w->height, w->title, NULL, NULL);
    if (!w->win) {
        fprintf(stderr, "Failed to create glfw window!\n");
        res = XEZA_ERR;
    }

    glfwSetFramebufferSizeCallback(w->win, xeza_framebuffer_size_cb);
    glfwMakeContextCurrent(w->win);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize opengl function pointers!\n");
        res = XEZA_ERR;
    }
    
    return 0;
}

void xeza_window_swap_buffers(window_t *w) {
    glfwSwapBuffers(w->win);
}

void xeza_window_poll_events() {
    glfwPollEvents();
}

void xeza_window_set_color(color_t color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void xeza_window_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void xeza_framebuffer_size_cb(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
}
