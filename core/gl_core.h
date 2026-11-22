#ifndef GL_CORE_H 
#define GL_CORE_H

#include "buffer.h"
//#include "texture.h"

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
    vec3_t random_color;
    mat4 model_matrix;
    //texture_t texture;
} mesh_t;

typedef struct { 
    mesh_t* meshes;
    size_t num_of_meshes;
    mat4 model_matrix;
    transform_t transform;
} model_t;

void gl_create_object(mesh_t* object);
void gl_init_transform(model_t* model);
void gl_apply_transform(model_t* model);

// Draws a straight line from one to another in the world, in one color
void gl_debug_line(vec3_t p1, vec3_t p2, vec3_t color, unsigned int *vao);

//mat4 gl_lt_to_mt(transform_t* t1, transform_t* t2);

#endif
