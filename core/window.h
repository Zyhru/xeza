#ifndef WINDOW_H 
#define WINDOW_H 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int width;
    int height;
    const char *title;
    GLFWwindow *win;
} window_t; 

// TODO: Move to utils class
// Possibly have preset colors that are supported e.g
// RED BLUE GREEN VIOLET MAGENTA BLACK WHITE
// makes it easier, rather than typing floating numbers
typedef struct {
    // color enum
    // if color enum = black
    // set rgb to black
    float r;
    float g;
    float b;
} color_t; 

int xeza_context_init();

int xeza_init();
int xeza_create_window(window_t *w);

void xeza_framebuffer_size_cb(GLFWwindow* window, int width, int height);

void xeza_window_set_color(color_t color);
void xeza_window_clear(); 
void xeza_window_swap_buffers(window_t *window);
void xeza_window_poll_events();

#endif
