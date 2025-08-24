#include "gl_core.h"

void gl_create_object(gl_t* object) {
    assert(object->vertex_buff != NULL);
    assert(object->index_buff != NULL);

    glGenBuffers(1, &object->vbo);
    glGenBuffers(1, &object->ebo);
    glGenVertexArrays(1, &object->vao);

    glBindVertexArray(object->vao);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * object->vertex_buff->size, (vertex_t *)object->vertex_buff->buffer, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, color));
    glEnableVertexAttribArray(1);
}

