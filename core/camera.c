#include "camera.h"

void camera_init(camera_t* cam) {
    cam->fov = 45.0f;
    cam->speed = 1.5f;

    
    cam->eye[0] = 0.0f;
    cam->eye[1] = 0.0f;
    cam->eye[2] = 3.0f;

    cam->center[0] = 0.0f;
    cam->center[1] = 0.0f;
    cam->center[2] = -1.0f;

    cam->up[0] = 0.0f;
    cam->up[1] = 1.0f;
    cam->up[2] = 0.0f;
}

void camera_move_around(input_t *input, camera_t* cam, float dt) {
    float velo = cam->speed * dt;
    
    if(input->forward) {
        printf("Moving forward!\n");
    }
   
    if(input->backward) {
        printf("Moving backward!\n");
    }

    if(input->left) {
        printf("Moving left!\n");
    }
    
    if(input->right) {
        printf("Moving right!\n");
    }

    
    //TODO: Forward 
    //TODO: Backward 
    //TODO: Up
    //TODO: Down

}

void camera_update(input_t* input, camera_t* cam, float dt) {
    camera_move_around(input, cam, dt);
}
