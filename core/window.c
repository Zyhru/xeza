#include "window.h"
#include "api.h"
#include <GLFW/glfw3.h>

#define TEST_SCALE_FACTOR 0.5f

static void _fb_resize_cb(GLFWwindow* window, int width, int height) {
    glViewport(0,0, width, height);
}

/**
 * @brief Initialize GLFW and glad 
 * 
 * @param  pointer to window 
 * @return void 
 */
void window_init(window_t* window) {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: Failed to initialize GLFW\n");
        exit(1);
    }

    window->width = WINDOW_WIDTH;
    window->height = WINDOW_HEIGHT;
    window->title = "Xeza";
    window->min_version = 3;
    window->max_version = 3;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window->min_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window->max_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->win = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
    if (!window->win) {
        fprintf(stderr, "ERROR: Failed to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }

    // callbacks
    glfwSetFramebufferSizeCallback(window->win, _fb_resize_cb);

    glfwMakeContextCurrent(window->win); // this must be active first, before any gl calls

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "ERROR: Failed to load glad\n");
        glfwTerminate();
        exit(1);
    }
}

/**
 * @brief Initialize GLFW and glad 
 * 
 * @param pointer to window_t
 * @return void 
 */

void window_loop(window_t* self) {
    glEnable(GL_DEPTH_TEST);
    

    while(!glfwWindowShouldClose(self->win)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);

        self->update();
        self->render();
        
        glfwSwapBuffers(self->win);
        glfwPollEvents();
    }

    self->destroy();
}
