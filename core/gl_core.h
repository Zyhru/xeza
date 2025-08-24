#ifndef GL_CORE_H 
#define GL_CORE_H

#include "buffer.h"

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    list_t* vertex_buff;
    list_t* index_buff; 
} gl_t;

void gl_create_object(gl_t* object);

#endif
