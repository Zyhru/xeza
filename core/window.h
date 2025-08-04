#ifndef WINDOW_H 
#define WINDOW_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    const char *name;
    uint8_t width;
    uint8_t height;
    const char *title;
    GLFWwindow *win;
} window_t; 

typedef struct {
    float r;
    float g;
    float b;
} color_t; 

int xeza_context_init();
int xeza_create_window(window_t *w);

void xeza_framebuffer_size_cb(GLFWwindow* window, int width, int height);

void xeza_window_set_color(color_t color);
void xeza_window_clear(); 
void xeza_window_swap_buffers(window_t *window);
void xeza_window_poll_events();

void xeza_shutdown();

#endif
