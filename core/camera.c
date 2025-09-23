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

void camera_move_around(camera_t* cam, float dt) {
    float velo = cam->speed * dt;

    // 0 = forward 1 = backward 2 = left 3 = right
    //TODO: Forward
    // if forward:
    // move forward

    //TODO: Backward 
    //TODO: Up
    //TODO: Down

}

void camera_update(camera_t* cam, float dt) {
    camera_move_around(cam, dt);
}
