#include "core/gfx.h"
#include "core/util/util.h"

#define CLI_ARGUMENT_ONE 1

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: xeza <obj file>\n");
        return -1;
    }
    
    char* obj_file = argv[CLI_ARGUMENT_ONE];
    char* file_ext = util_extdup(obj_file); // extracting extension
    
    if (strcmp(file_ext, "obj") != 0) {
        fprintf(stderr, "Invalid file extension! Must be of type .obj\n");
        return -1;
    }
    
    gfx_init_pipeline(obj_file);
    
    free(file_ext); 
    return 0;
}
