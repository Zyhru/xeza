#include "gl_core.h"
#include "api.h"
#include "buffer.h"

#define SCALE_FACTOR 0.5f

void gl_create_object(gl_t* object) {
    assert(object->vertex_buff != NULL);
    
   // assert(object->index_buff != NULL);

    //printf("Size of Index Buffer: %d\n", object->index_buff->size);
    //printf("Size of Vertex Buffer: %d\n", object->vertex_buff->size);
   
    gl_init_transform(object);

    /* Creating GL Object */
    glGenBuffers(1, &object->vbo); 
    glGenBuffers(1, &object->ebo); // This is going to generate everytime! Oops..
    glGenVertexArrays(1, &object->vao);

    /* Creating a new state for the newly created objects*/
    glBindVertexArray(object->vao);
   
    #if defined(DEBUG)
    printf("[DEBUG] Renderer submission\n");
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    
    /* Attaching Data to GPU */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * object->vertex_buff->size, (vertex_t *)object->vertex_buff->addr, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * object->index_buff->size, (unsigned int*) object->index_buff->addr, GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, pos));
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, color));
    glEnableVertexAttribArray(1);
   
    #elif defined(RELEASE)
    printf("[RELEASE] Renderer submission\n");
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vertex_t) * object->vertex_buff->size, (obj_vertex_t *)object->vertex_buff->addr, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * object->index_buff->size, (unsigned int*) object->index_buff->addr, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(obj_vertex_t), (void *) offsetof(obj_vertex_t, v));
    glEnableVertexAttribArray(0);
    #endif
}

void gl_init_transform(gl_t* object) {
    vec3 position = {0.0f, 0.0f, -1.0f};
    //vec3 scale = {SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
    object->transform.angle = 90.0f;
  
    memcpy(object->transform.pos, position, sizeof(position));
    //memcpy(object->transform.scale, scale, sizeof(scale));
   
    #if 0
    printf("Model Transform\n");
    printf("Model Position: {%f, %f, %f}\n", object->transform.pos[0],
           object->transform.pos[1], object->transform.pos[2]);
    
    printf("Model Scale: {%f, %f, %f}\n", object->transform.scale[0],
           object->transform.scale[1], object->transform.scale[2]);
    #endif
}

void gl_apply_transform(gl_t *object, mat4* model) {
    vec3 axis = {0.5f, 0.5f, 0.5f};
    glm_translate(*model, object->transform.pos);
    glm_rotate(*model, glm_rad(object->transform.angle) * glfwGetTime(), axis);
    //glm_scale(*model, object->transform.scale);
}
