#include "gl_core.h"
#include "api.h"
#include "buffer.h"

#define SCALE_FACTOR 0.1f

void gl_create_object(mesh_t* object) {
    assert(object->vertex_buff != NULL);
    assert(object->index_buff != NULL);

    /* Creating GL Object */
    glGenBuffers(1, &object->vbo); 
    glGenBuffers(1, &object->ebo);
    glGenVertexArrays(1, &object->vao);

    /* Creating a new state for the newly created objects*/
    glBindVertexArray(object->vao);

    /* load texture */
    //TODO: Apply textures
    //texture_t texture = {0};
    //texture->image 
   
    //printf("[RELEASE] Renderer submission for mesh: {%s}\n", object->name);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vertex_t) * object->vertex_buff->size, (obj_vertex_t *)object->vertex_buff->addr, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * object->index_buff->size, (unsigned int*)object->index_buff->addr, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(obj_vertex_t), (void *) offsetof(obj_vertex_t, v));
    glEnableVertexAttribArray(0);
    printf("Finished renderer submission!\n");
}

void gl_init_transform(model_t* model) {
    vec3 position = {0.0f, -0.1f, -0.8f};
    vec3 scale = {SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
    
    model->transform.angle = 90.0f;
    memcpy(model->transform.pos, position, sizeof(position));
    memcpy(model->transform.scale, scale, sizeof(scale));
}

void gl_apply_transform(model_t* model) {
    vec3 axis = {0.0f, 0.1f, 0.0f};
    glm_translate(model->model_matrix, model->transform.pos);
    glm_rotate(model->model_matrix, glm_rad(model->transform.angle) * glfwGetTime(),  axis);
    glm_scale(model->model_matrix, model->transform.scale);
}
