#ifndef CAMERA_H 
#define CAMERA_H 

#include "api.h"
#include "input.h"

/*
*
* Simulating a camera:
* - Looking Around
* - Moving around 
* Essentially an FPS camera
*
* Camera will have:
* Up Vector
* Direction Vector
* Starting Position
* FOV
*/

#include "math.h"
#include "input.h"

typedef struct {
    float fov;
    vec3 up;
    vec3 eye;
    vec3 center;
    float speed;
    mat4 view;
    mat4 perspective;
} camera_t;

void camera_init(camera_t* cam);
void camera_update(input_t* input, camera_t* self, float dt); // look around and move around will be here
void camera_move_around(input_t* input, camera_t* self, float dt); 
void camera_look_around(float dt); //TODO: Implement look around
void camera_look_at(camera_t* self);

#endif // CAMERA_H
