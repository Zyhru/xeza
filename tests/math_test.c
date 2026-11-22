#include "../core/xmath.h"

// Pythagorean theorem
float vec3_magnitude(vec3_t v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

void vec3_add(vec3_t v1, vec3_t v2, vec3_t* dest) {
    dest->x = v1.x + v2.x;
    dest->y = v1.y + v2.y;
    dest->z = v1.z + v2.z;
}

void vec3_sub(vec3_t v1, vec3_t v2, vec3_t* dest) {
    dest->x = v1.x - v2.x;
    dest->y = v1.y - v2.y;
    dest->z = v1.z - v2.z;
}

void vec3_scale(vec3_t v, float scalar, vec3_t *dest) {
    dest->x = v.x * scalar; 
    dest->y = v.y * scalar; 
    dest->z = v.z * scalar; 
}

// v / ||v||
// only care about direction
vec3_t vec3_normalize(vec3_t v) {
    vec3_t k;
    float mag = vec3_magnitude(v);
    v.x /= mag;
    v.y /= mag;
    v.z /= mag; 
    k = v;
    return k;
}

float vec3_dot(vec3_t v, vec3_t k) {
   return v.x * k.x + v.y * k.y + v.z * k.z;
}

// The cross product of v and k produce a third vector
// if both v and k are orthogonal then it produces a 3rd orthogonal
// cross product isn't intuitive
void vec3_cross(vec3_t v, vec3_t k, vec3_t *dest) {
    dest->x = v.y * k.z - v.z * k.y;
    dest->y = v.z * k.x - v.x * k.z;
    dest->z = v.x * k.y - v.y * k.x;
}
