#ifndef CAMERA_H 
#define CAMERA_H 

#include "api.h"
#include "keyboard.h"

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

// TODO: Calculate the right vector (cross product of up and direction)
// TODO: Delta time 
//

#include "math.h"

typedef struct {
    float fov;
    vec3 up;
    vec3 eye;
    vec3 center;
    float speed;
} camera_t;

void camera_init(camera_t* cam);

// lookat matrix
void camera_update(camera_t* cam, float dt); // look around and move around will be here
void camera_move_around(camera_t* cam, float dt); 
void camera_look_around(float dt); //TODO: Implement look around

#endif // CAMERA_H
