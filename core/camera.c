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
    float distance_traveled = cam->speed * dt;
    if(input->forward) {
        printf("Moving forward!\n");
        glm_normalize(cam->center);
        glm_vec3_scale(cam->center, distance_traveled, cam->center);
        glm_vec3_add(cam->eye, cam->center, cam->eye);
    }
   
    if(input->backward) {
        printf("Moving backward!\n");
        glm_normalize(cam->center);
        glm_vec3_scale(cam->center, cam->speed * dt, cam->center);
        glm_vec3_sub(cam->eye, cam->center, cam->eye);
    }

    if(input->left) {
        printf("Moving left!\n"); 
        vec3 right = {0.0f,0.0f,0.0f};
        glm_cross(cam->up, cam->center, right);
        glm_normalize(right);
        
        glm_vec3_scale(right, distance_traveled, right);
        glm_vec3_add(cam->eye, right, cam->eye);
    }
    
    if(input->right) {
        vec3 right = {0.0f,0.0f,0.0f};
        glm_cross(cam->up, cam->center, right);
        glm_normalize(right);
       
        glm_vec3_scale(right, distance_traveled, right);
        glm_vec3_sub(cam->eye, right, cam->eye);
        printf("Moving right!\n");
    }
}

void camera_update(input_t* input, camera_t* cam, float dt) {
    camera_look_at(cam);
    camera_move_around(input, cam, dt);
}

void camera_look_at(camera_t* cam) {
    glm_mat4_identity(cam->view);
   
    vec3 dir = {0.0f, 0.0f, 0.0f};
    glm_vec3_add(cam->eye, cam->center, dir);
    glm_lookat(cam->eye, dir, cam->up, cam->view);
    
    glm_mat4_identity(cam->perspective);
    glm_perspective(glm_rad(cam->fov), 640.0f / 480.0f, 0.1f, 100.0f, cam->perspective);
}
