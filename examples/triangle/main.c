#include "../../core/xeza.h"
#include "../../core/shader.h"

#include <stdio.h>

int main() {
    int status;
    window_t window;
    shader_t shader;
    color_t color = xeza_create_color(0.1f,0.4f,0.5f);

    status = xeza_init();
    if (status == XEZA_ERR) {
        fprintf(stderr, "Xeza initialization failed\n");
        return XEZA_ERR;
    }

    window.height = 800;
    window.width = 600;
    window.title = "Triangle";

    status = xeza_create_window(&window);
    if (status == XEZA_ERR) {
        fprintf(stderr, "Xeza window initialization failed\n");
        return XEZA_ERR;
    }


    // Initialize shaders
    // TODO: Implement shader core system
    status = xeza_shader_init("../../shaders/vertex.glsl", "../../shaders/fragment.glsl", &shader);
    if (status == XEZA_ERR) {
        fprintf(stderr, "Xeza window initialization failed\n");
        return XEZA_ERR;
    }

    while (!xeza_main_loop(&window)) {
        xeza_window_clear();
        xeza_window_set_color(color);

        //          Shader and Rendering Code
        // ========================================= 
        //                                         |
        //                                         |
        //                                         |
        //                                         |
        // ========================================= 
        
        xeza_window_poll_events();
        xeza_window_swap_buffers(&window);
    }
    
    return 0;
}


// TODO: Create a error handler function or design an error handler system
