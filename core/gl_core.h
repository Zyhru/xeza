#ifndef GL_CORE_H 
#define GL_CORE_H

#include "buffer.h"

typedef struct {
    vec3 pos;
    float angle;
    vec3 scale;
} transform_t;

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    list_t* vertex_buff;
    list_t* index_buff; 
    transform_t transform;
} gl_t;

void gl_create_object(gl_t* object);
void gl_init_transform(gl_t* object);
void gl_apply_transform(gl_t* object, mat4* model);

#endif
