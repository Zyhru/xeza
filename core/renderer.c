#include "renderer.h"
#include "api.h"
#include "buffer.h"
#include <stdio.h>


// Have some sort of renderer_create_primitive(enum);


//INFO: initializing the shader, camera, texture, and model
void renderer_init(renderer_t* r) {
    puts("Initialzing renderer.");
    shader_t shader;
    int shd_res = shader_init("shaders/vertex.glsl", "shaders/fragment.glsl", &shader);
    if (shd_res == -1) {
        fprintf(stderr, "Failed to initalize shader");
        exit(1);
    }
    
    r->shd = shader; // all thats being copied over is the program
    //gl_create_object(&r->object);
   
    // for testing, we'll have a predefined triangle
    #if 0
    //gl_t triangle;
    triangle.vertex_buff = list_create(3, VERTEX_BUFFER);

    vertex_t v1 = { {0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} };
    vertex_t v2 = { {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} };
    vertex_t v3 = { {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} };
    
    list_append(triangle.vertex_buff, &v1);
    list_append(triangle.vertex_buff, &v2);
    list_append(triangle.vertex_buff, &v3);

    //printf("List size: %d\n", triangle.vertex_buff->size); 
    list_print(triangle.vertex_buff);

    gl_create_object(&triangle);
    #endif
    
    renderer_create_cube(r);
}

void renderer_use_shader(renderer_t *r) {
    glUseProgram(r->shd.program);
}

void renderer_draw(renderer_t* r) {
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

    #ifdef DEBUG
    list_print(r->object.vertex_buff);
    list_print(r->object.index_buff);
    #endif
}


// Idea
// Have a function that will take in a vbo, index buffer usage, and 
// automate the construction of an index buffer.
//
// well it wouldn't work because that's when the idea of different model objects
// come into play.
//
// for the cube just manually write it
