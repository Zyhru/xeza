#include "window.h"
#include "renderer.h"

window_t window;

/**
 * @brief Initialize GLFW and glad 
 * 
 * @param  void 
 * @return void 
 */
void window_init() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: Failed to initialize GLFW\n");
        exit(1);
    }

    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;
    window.title = "Xeza";
    window.min_version = 3;
    window.max_version = 3;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window.min_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window.max_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.win = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (!window.win) {
        fprintf(stderr, "ERROR: Failed to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window.win); // this must be active first, before any gl calls
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "ERROR: Failed to load glad\n");
        glfwTerminate();
        exit(1);
    }
}

/**
 * @brief Initialize GLFW and glad 
 * 
 * @param  a renderer_t struct pointer  
 * @return void 
 */
void window_loop(renderer_t *r) {
    while(!glfwWindowShouldClose(window.win)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);

        renderer_use_shader(r);
        renderer_draw(r);

        glfwSwapBuffers(window.win);
        glfwPollEvents();
    }

    glfwDestroyWindow(window.win);
    glfwTerminate();
}
    
