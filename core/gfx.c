#include "gfx.h"

// TODO: Initialze graphics pipeline
void gfx_init_pipeline(char *obj_file) {
    printf("Initializing Xeza.\n");
    printf("Parsing: %s\n", obj_file);

    // TODO: Parse obj file 

    window_init();
    
    renderer_t renderer;
    renderer_init(&renderer);
    
    window_loop(&renderer);

    free(renderer.object.vertex_buff);
    free(renderer.object.index_buff);
}
