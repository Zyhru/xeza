#include "shader.h"
#include "api.h"
#include "util/util.h"
#include <stdio.h>


// create shader
// attach shader source 
// compile shader
// TODO: Update logging/print statements
int shader_init(char *v, char *f, shader_t* shader) {
    puts("Initialzing shader");
    shader_err_t shd_err;
    unsigned int v_shader, f_shader;
    char *vertex_buffer, *fragment_buffer;

    if (util_read_file(v, &vertex_buffer)   == -1)  return -1;
    if (util_read_file(f, &fragment_buffer) == -1)  return -1;

    printf("Vertex Shader: %s\n", vertex_buffer);
    printf("Fragment Shader: %s\n", fragment_buffer);

    puts("Compiling vertex shader");
    v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, (const GLchar* const *) &vertex_buffer, NULL);
    glCompileShader(v_shader);
    shader_compilation_error(GL_VERTEX_SHADER, "VERTEX_SHADER", v_shader, &shd_err);
    puts("Compiled vertex shader");
    
    puts("Compiling fragment shader");
    f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, (const GLchar* const *)&fragment_buffer, NULL);
    glCompileShader(f_shader);
    puts("Compiled fragment shader");
    shader_compilation_error(GL_FRAGMENT_SHADER, "FRAGMENT_SHADER", f_shader, &shd_err);

    puts("Creating and linking shader program");
    shader->program = glCreateProgram();
    glAttachShader(shader->program, v_shader);
    glAttachShader(shader->program, f_shader);
    glLinkProgram(shader->program);

    // TODO: Check for linking errors

    // TODO: destroying/free system ?
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
    free(vertex_buffer);
    free(fragment_buffer);
    puts("Finished creating shader.");
    return 0;
}

// TODO: Change error handling
// TODO: Could be that reading the file isn't working correctly. Make sure to view the contents of the shader file buffers
void shader_compilation_error(GLenum shader_type, char *shader_name, unsigned int shd, shader_err_t *shd_err) {
    glGetShaderiv(shd, GL_COMPILE_STATUS, &shd_err->status);
    if (!shd_err->status) {
        switch (shader_type) {
            case GL_VERTEX_SHADER:
                    glGetShaderInfoLog(shd, INFO_LOG_SIZE, NULL, shd_err->info_log);
                    fprintf(stderr, "ERROR: %s failed to compile. %s\n", shader_name, shd_err->info_log); 
                break;
            case GL_FRAGMENT_SHADER:
                    glGetShaderInfoLog(shd, INFO_LOG_SIZE, NULL, shd_err->info_log);
                    fprintf(stderr, "ERROR: %s failed to compile\n %s", shader_name, shd_err->info_log); 
                break;
        }
    }
}

void shader_mat4_uniform(GLuint program, char* name, mat4 matrix) {
    unsigned int location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (float *) matrix);
}

void shader_vec3_uniform(GLuint program, char* name, vec3_t value) {
    unsigned int location = glGetUniformLocation(program, name);
    glUniform3f(location, value.x, value.y, value.z);
}
