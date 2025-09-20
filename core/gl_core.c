#include "gl_core.h"
#include "api.h"
#include <stdio.h>

void gl_create_object(gl_t* object) {
    assert(object->vertex_buff != NULL);
    assert(object->index_buff != NULL);

    /* Creating GL Object */
    glGenBuffers(1, &object->vbo);
    glGenBuffers(1, &object->ebo);
    glGenVertexArrays(1, &object->vao);

    /* Creating a new state for the newly created objects*/
    glBindVertexArray(object->vao);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    
    printf("Vertex List size: %d\n", object->vertex_buff->size);
    printf("Index List size: %d\n", object->index_buff->size);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * object->vertex_buff->size, (vertex_t *)object->vertex_buff->addr, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * object->index_buff->size, (unsigned int*) object->index_buff->addr, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) offsetof(vertex_t, color));
    glEnableVertexAttribArray(1);
}
