#include "gfx.h"
#include "buffer.h"
#include "renderer.h"
#include "state.h"
#include "window.h"

// global state
state_t state;

// TODO: Calculate delta time
float dt;

void update() {
    renderer_use_shader(&state.renderer); // possibly be moved to render?
  
    input_check(&state.input, state.window.win);
    camera_update(&state.input, &state.camera, dt);

    mat4 projection, view, model;

    glm_mat4_identity(projection);
    glm_mat4_identity(view);
    glm_mat4_identity(model);
   
    /* Camera */
    // TODO: Move to camera impl
    vec3 eye = {0.0f, 0.0f, 3.0f}; // starting pos ()
    vec3 center = {0.0f, 0.0f, -1.0f}; // direction
    vec3 up = {0.0f, 1.0f, 0.0f}; // up direction
    // cross_product(up, center) = right (A D)
    
    glm_perspective(glm_rad(45.0f), 640.0f / 480.0f, 0.1f, 100.0f, projection);
    
    // TODO: Move to camera impl
    glm_lookat(up, center, up, view);

    gl_apply_transform(&state.renderer.object, &model);

    mat4 mvp;
    glm_mat4_mul(projection, view, mvp); // model * view -> mvp
    glm_mat4_mul(mvp, model, mvp);
    /* ---------------------------------------------------- */

    shader_mat4_uniform(state.renderer.shd.program, "mvp", mvp);
}

void render() {
    renderer_draw(&state.renderer);
}

void destroy() {
    list_destroy(state.renderer.object.vertex_buff);
    list_destroy(state.renderer.object.index_buff);
}

// TODO: Initialze graphics pipeline
void gfx_init_pipeline(char *obj_file) {
    printf("Initializing Xeza.\n");
    printf("Parsing: %s\n", obj_file);

    // TODO: Parse obj file 
    


    input_t input;

    window_t window;
    window.update = update;
    window.render = render;
    window.destroy = destroy;
    window_init(&window);
    
    
    renderer_t renderer;
    renderer_init(&renderer);

    camera_t camera;
    camera_init(&camera);

    // passing components to global state
    state.camera = camera;
    state.renderer = renderer;
    state.window = window;
    state.input = input;

    window_loop(&state.window);
    printf("Exiting renderer\n");
}
