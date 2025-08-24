#ifndef WINDOW_H 
#define WINDOW_H 

#include "api.h"
#include "renderer.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct {
    int width;
    int height;
    const char* title;
    GLFWwindow* win;
    int min_version;
    int max_version;

    // function pointers
    void (*render)(renderer_t* r);
    void (*update)(renderer_t* r);

} window_t; 

void window_loop(renderer_t* r);
void window_render(renderer_t* r);
void window_init();

#endif
