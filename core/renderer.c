#include "renderer.h"
#include "api.h"
#include "buffer.h"
#include "gl_core.h"
#include <stdio.h>


// Have some sort of renderer_create_primitive(enum);


//INFO: initializing the shader, camera, texture, and model
void renderer_init(renderer_t* r) {
    puts("Initialzing renderer.");
    shader_t shader;

    printf("RENDERER INIT: INDEX BUFFER SIZE = %d\n", r->object.index_buff->size);
    printf("RENDERER INIT: VERTEX BUFFER SIZE = %d\n", r->object.vertex_buff->size);

    #if defined(RELEASE)
    printf("Using obj shaders\n");
    int shd_res = shader_init("shaders/obj_vertex.glsl", "shaders/obj_fragment.glsl", &shader);
    if (shd_res == -1) {
        fprintf(stderr, "Failed to initalize shader");
        exit(1);
    }
   
    renderer_create_obj(r);
    
    #elif defined(DEBUG)
    printf("Using debug shaders\n");
    int shd_res = shader_init("shaders/vertex.glsl", "shaders/fragment.glsl", &shader);
    if (shd_res == -1) {
        fprintf(stderr, "Failed to initalize shader");
        exit(1);
    }

    renderer_create_cube(r);
    #endif
    
    r->shd = shader; 
}

void renderer_use_shader(renderer_t *r) {
    glUseProgram(r->shd.program);
}

void renderer_draw(renderer_t* r) {
    glBindVertexArray(r->object.vao);
    glDrawElements(GL_TRIANGLES, r->object.index_buff->size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void renderer_draw_obj(renderer_t* r) {
    glBindVertexArray(r->object.vao);
    glDrawElements(GL_TRIANGLES, r->object.index_buff->size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void renderer_create_cube(renderer_t* r) {
    gl_t cube;
    cube.vertex_buff = list_create(VERTEX_BUFFER);
    cube.index_buff = list_create(INDEX_BUFFER);
  
    list_append(cube.vertex_buff, &(vertex_t){.pos = {-0.5f,  0.5f,  0.5f}, .color = {0.0f, 1.0f, 0.0f}}); // 0
    list_append(cube.vertex_buff, &(vertex_t){.pos = { 0.5f,  0.5f, -0.5f}, .color = {0.0f, 0.0f, 1.0f}}); // 1
    list_append(cube.vertex_buff, &(vertex_t){.pos = { 0.5f,  0.5f,  0.5f}, .color = {1.0f, 0.0f, 0.0f}}); // 2
    list_append(cube.vertex_buff, &(vertex_t){.pos = {-0.5f, -0.5f, -0.5f}, .color = {0.0f, 1.0f, 0.0f}}); // 3
    list_append(cube.vertex_buff, &(vertex_t){.pos = {-0.5f,  0.5f, -0.5f}, .color = {0.0f, 0.0f, 1.0f}}); // 4 (back-top-left)
    list_append(cube.vertex_buff, &(vertex_t){.pos = { 0.5f, -0.5f, -0.5f}, .color = {1.0f, 0.0f, 0.0f}}); // 5
    list_append(cube.vertex_buff, &(vertex_t){.pos = { 0.5f, -0.5f,  0.5f}, .color = {0.0f, 1.0f, 0.0f}}); // 6
    list_append(cube.vertex_buff, &(vertex_t){.pos = {-0.5f, -0.5f,  0.5f}, .color = {1.0f, 1.0f, 0.0f}}); // 7

    unsigned int index_buffer[] = {
      // Front face  
      0, 2, 6,
      0, 6, 7,

      // Back face   
      4, 1, 5,
      4, 5, 3,

      // Left face   
      3, 4, 0,
      3, 0, 7,

      // Right face  
      1, 5, 6,
      1, 6, 2,

      // Top face
      4, 0, 2,
      4, 2, 1,

      // Bottom face 
      3, 7, 6,
      3, 6, 5
    };

    size_t index_length = sizeof(index_buffer) / sizeof(index_buffer[0]);
    printf("Index Buffer Length: %zu\n", index_length);
    for(size_t i = 0; i < index_length; i++) {
        list_append(cube.index_buff, (unsigned int *)&index_buffer[i]);
    }

    gl_create_object(&cube);
    r->object = cube;

    list_print(r->object.vertex_buff);
    list_print(r->object.index_buff);
}

void renderer_create_obj(renderer_t* r) {
    gl_create_object(&r->object);
}
