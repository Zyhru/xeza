#ifndef SHADER_H 
#define SHADER_H 

#include "api.h"

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

// check for errors

#endif
