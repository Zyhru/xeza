#include "core/gfx.h"
#include "core/util/util.h"

#define CLI_ARGUMENT_ONE 1

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: xeza <obj file>\n");
        return -1;
    }
   
    #if defined(RELEASE)
    printf("RELEASE MODE\n");
    char* obj_file = argv[CLI_ARGUMENT_ONE];
    char* file_ext = util_extdup(obj_file); // extracting extension
    
    if (strcmp(file_ext, "obj") != 0) {
        fprintf(stderr, "Invalid file extension! Must be of type .obj\n");
        return -1;
    }

    // does .obj file exists
    if(access(obj_file, F_OK) == -1) {
        fprintf(stderr, "%s does not exist.\n", obj_file);
        return -1;
    }
    
    init(obj_file);
    free(file_ext); 
    #elif defined(DEBUG)
    printf("DEBUG MODE\n");
    init(NULL);
    #endif
    
    return 0;
}
