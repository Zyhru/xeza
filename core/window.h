#ifndef WINDOW_H 
#define WINDOW_H 

// TODO: Fix global state

#include "api.h"
#include "input.h"

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
    void (*render)(void);
    void (*update)(void);
    void (*destroy)(void);

} window_t; 

void window_loop(window_t* self);
void window_render();
void window_init(window_t* window);
void window_update();


#endif
