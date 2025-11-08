#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "buffer.h"
#include "gl_core.h"

typedef struct {
    shader_t shd;
    model_t model;
} renderer_t;

// we are initializing the shader, camera, texture, and model?
void renderer_init(renderer_t* r);

/* draw */
void renderer_draw(renderer_t* r);
void renderer_draw_model(renderer_t* r);
void renderer_use_shader(renderer_t *r);

/* create */
void renderer_create_cube(renderer_t *r);
void renderer_create_obj(renderer_t* r);

/*
*
    *
    *
    * INFO: 
    * This file will contain handle each compoenent of the Xeza renderer.
    * Such as the: 
    * - Shaders
    * - Textures
    * - Drawing
    * - Updating
    * - Camera 
    */ 

#endif
