#include "shader.h"
#include "api.h"
#include <stdio.h>
#include <stdlib.h>

// create shader
// attach shader source 
// compile shader
int xeza_shader_init(char *v, char *f, shader_t *shader) {
    int res = 0;
    shader_err_t shd_err;
    unsigned int v_shader, f_shader;
    char *vertex_buffer, *fragment_buffer;

    if ((res = xeza_read_file(v, &vertex_buffer))   < 0) return -1;
    if ((res = xeza_read_file(f, &fragment_buffer)) < 0) return -1;
    
    v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, (const char *const *)&vertex_buffer, NULL);
    glCompileShader(v_shader);
    shader_compilation_error(GL_VERTEX_SHADER, "VERTEX_SHADER", v_shader, &shd_err);
    
    f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, (const char *const *)&fragment_buffer, NULL);
    glCompileShader(f_shader);
    shader_compilation_error(GL_FRAGMENT_SHADER, "FRAGMENT_SHADER", f_shader, &shd_err);

    shader->program = glCreateProgram();
    glAttachShader(shader->program, v_shader);
    glAttachShader(shader->program, f_shader);
    glLinkProgram(shader->program);

    // TODO: destroying/free system ?
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
    free(vertex_buffer);
    free(fragment_buffer);
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

int xeza_read_file(char *file_name, char **buffer) {
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stderr, "unable to open file: %s\n", file_name); 
        return -1;  // failed to open file
    }

    // grab the size of the entire file
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    size_t n = size + 1;
    *buffer = malloc(n);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate %zu number of bytes\n", n); 
        fclose(fp);
        return -1;
    }

    fread(*buffer, 1, size, fp);
    (*buffer)[size] = '\0';

    fclose(fp);
    return 0;
}
