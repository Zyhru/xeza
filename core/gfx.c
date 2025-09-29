#include "gfx.h"
#include "state.h"

// global state
state_t state;

float delta_time = 0.0f;
float last_frame = 0.0f;

void update() {
    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    

    renderer_use_shader(&state.renderer); // possibly be moved to render?
  
    input_check(&state.input, state.window.win);
    camera_update(&state.input, &state.camera, delta_time);

    mat4 model;
    glm_mat4_identity(model);
    gl_apply_transform(&state.renderer.object, &model);

    mat4 mvp;
    glm_mat4_mul(state.camera.perspective, state.camera.view, mvp); // model * view -> mvp
    glm_mat4_mul(mvp, model, mvp);
    shader_mat4_uniform(state.renderer.shd.program, "mvp", mvp);
}

void render() {
    renderer_draw(&state.renderer);
}

void destroy() {
    list_destroy(state.renderer.object.vertex_buff);
    list_destroy(state.renderer.object.index_buff);
    glfwDestroyWindow(state.window.win);
    glfwTerminate();
    printf("Freeing all renderer resources\n");
}

void init(char *obj_file) {
    printf("Initializing Xeza.\n");
    printf("Parsing: %s\n", obj_file);

    // TODO: Parse obj file 
    //INFO: Currently debugging to understand how tinyobj-loader-c works
    //gl_t obj_model;
    //obj_load(&obj_model, obj_file);

    input_t input = {0};

    window_t window;
    window.update = update;
    window.render = render;
    window.destroy = destroy;
    window_init(&window);
    
    renderer_t renderer;
    //renderer.object = obj_model;
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
