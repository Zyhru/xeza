#include "gfx.h"
#include "gl_core.h"
#include "shader.h"
#include "state.h" // change how this is being included
#include <cglm/mat4.h>

// global state
state_t state;

float delta_time = 0.0f;
float last_frame = 0.0f;

void init(char *obj_file) {
    printf("Initializing Xeza.\n");
    
    renderer_t renderer;

    #if defined(RELEASE)
    model_t model;
    printf("Parsing: %s\n", obj_file);
    if(obj_load(&model, obj_file) == 1) {
        fprintf(stderr, "Failed to load obj file: %s\n", obj_file);
        return;
    }
    
    for(int i = 0; i < model.num_of_meshes; ++i) {
        mesh_t mesh = model.meshes[i];
        glm_mat4_identity(mesh.model_matrix);
    }
    
    renderer.model = model;
    gl_init_transform(&renderer.model);
    #endif

    input_t input = {0};

    window_t window;
    window.update = update;
    window.render = render;
    window.destroy = destroy;
    window_init(&window);
    
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

void update() {
    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    renderer_use_shader(&state.renderer); // possibly be moved to render?
  
    input_check(&state.input, state.window.win);
    camera_update(&state.input, &state.camera, delta_time);

    glm_mat4_identity(state.renderer.model.model_matrix);

    for(int i = 0; i < state.renderer.model.num_of_meshes; ++i) {
        glm_mat4_identity(state.renderer.model.meshes[i].model_matrix);
        glm_mat4_mul(state.renderer.model.model_matrix, state.renderer.model.meshes[i].model_matrix, state.renderer.model.model_matrix);
    }

    gl_apply_transform(&state.renderer.model);

    mat4 mvp;
    glm_mat4_mul(state.camera.perspective, state.camera.view, mvp); // model * view -> mvp
    glm_mat4_mul(mvp, state.renderer.model.model_matrix, mvp);
    shader_mat4_uniform(state.renderer.shd.program, "mvp", mvp);

    // apply the color here
    //shader_vec3_uniform(state.renderer.shd.program, "random_color", state.renderer.object.random_color);
}

void render() {
    #if defined(DEBUG)
    renderer_draw(&state.renderer);
    #elif defined(RELEASE)
    renderer_draw_model(&state.renderer);
    #endif
}

void destroy() {
    model_t model = state.renderer.model;
    for (int i = 0; i < model.num_of_meshes; ++i) {
        list_destroy(model.meshes[i].vertex_buff);
        list_destroy(model.meshes[i].index_buff);
    }

    glfwDestroyWindow(state.window.win);
    glfwTerminate();
    printf("Destroyed everything.\n");
}
