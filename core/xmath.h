#ifndef XMATH_H
#define XMATH_H

#include <cglm/cglm.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

typedef struct {
    float x;
    float y;
} vec2_t;

/* Vector3 Functions */
void vec3_add(vec3_t v1, vec3_t v2, vec3_t* dest);
void vec3_sub(vec3_t v1, vec3_t v2, vec3_t* dest);
void vec3_scale(vec3_t v, float scalar, vec3_t* dest);
float vec3_magnitude(vec3_t v);
vec3_t vec3_normalize(vec3_t v);
float vec3_dot(vec3_t v, vec3_t k);

#endif
