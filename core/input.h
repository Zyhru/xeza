#ifndef INPUT_H 
#define INPUT_H 

#include "api.h"

typedef struct {
    bool forward;
    bool backward;
    bool left;
    bool right;
} input_t;

void input_check(input_t *self, GLFWwindow* window);

#endif // INPUT_H
