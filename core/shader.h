#ifndef SHADER_H 
#define SHADER_H 

#include "api.h"
#include "math.h"

#define INFO_LOG_SIZE 512

typedef struct {
    unsigned int program;
} shader_t;

typedef struct {
    int status;
    char info_log[INFO_LOG_SIZE];
} shader_err_t;

// initialize shaders
int shader_init(char *v, char *f, shader_t *shader);
void shader_compilation_error(GLenum shader_type, char *shader_name, unsigned int shd, shader_err_t *shd_err);    

// read shader file (move to util file? might need this function for later)

// set shader uniforms
void shader_mat4_uniform(GLuint program, char* name, mat4 matrix);
void shader_vec3_uniform(GLuint program, char* name, vec3_t value);
void shader_float_uniform(GLuint program, char* name, float value);

// check for errors

#endif
