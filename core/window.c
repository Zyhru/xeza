#include "window.h"
#include "buffer.h"
#include "renderer.h"
#include "shader.h"
#include <cglm/affine-pre.h>
#include <cglm/mat3x4.h>

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
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

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
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window.win)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);

        renderer_use_shader(r);
       
        /* ---------------------------------------------------- */
                             /* MVP */
        mat4 projection, view, model;
        vec3 eye = {0.0f, 0.0f, 4.0f}; // starting pos
        vec3 center = {0.0f, 0.0f, -1.0f}; // direction
        vec3 up = {0.0f, 1.0f, 3.0f}; // up direction
        
        glm_mat4_identity(projection);
        glm_mat4_identity(view);
        glm_mat4_identity(model);
       
        glm_perspective(glm_rad(45.0f), 640.0f / 480.0f, 0.1f, 100.0f, projection);
       // glm_translate(view, (vec3){0.0f, 0.0f, 2.0f});

        glm_lookat(up, center, up, view);
       
        vec3 axis = {0.5f, 0.5f, 0.5f};
        glm_translate(model, (vec3){0.5f, 1.0f, -5.0f});
        glm_rotate(model, glm_rad(90.0f) * glfwGetTime(), axis);

        mat4 mvp;
        glm_mat4_mul(projection, view, mvp); // model * view -> mvp
        glm_mat4_mul(mvp, model, mvp);

        shader_mat4_uniform(r->shd.program, "mvp", mvp);
        /* ---------------------------------------------------- */

        renderer_draw(r);
        
        glfwSwapBuffers(window.win);
        glfwPollEvents();
    }

    #if 0
    free(r->object.vertex_buff);
    free(r->object.vertex_buff->addr);
    free(r->object.index_buff);
    free(r->object.index_buff->addr);
    #endif

    //list_destroy(r->object.vertex_buff);
    //list_destroy(r->object.index_buff);
    glfwDestroyWindow(window.win);
    glfwTerminate();
}
    
