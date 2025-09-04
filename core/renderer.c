#include "renderer.h"
#include "buffer.h"
#include <stdio.h>

//INFO: initializing the shader, camera, texture, and model
void renderer_init(renderer_t* r) {
    puts("Initialzing renderer.");
    shader_t shader;
    gl_t triangle;
    int shd_res = shader_init("shaders/vertex.glsl", "shaders/fragment.glsl", &shader);
    if (shd_res == -1) {
        fprintf(stderr, "Failed to initalize shader");
        exit(1);
    }

    // for testing, we'll have a predefined triangle
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
    
    // will this save correctly?
    // this is okay since both lists are allocated on the heap
    r->object = triangle; // values and pointers are copied
    r->shd = shader; // all thats being copied over is the program
}

void renderer_use_shader(renderer_t *r) {
    glUseProgram(r->shd.program);
}

void renderer_draw(renderer_t* r) {
    glBindVertexArray(r->object.vao);
    glDrawArrays(GL_TRIANGLES, 0, r->object.vertex_buff->size);
    glBindVertexArray(0);
}
