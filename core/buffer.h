#ifndef BUFFER_H 
#define BUFFER_H

#include "api.h"
#include "math.h"

#define LIST_CAPACITY 50

// non-obj object
typedef struct { 
    vec3_t pos;
    vec3_t color;
    //vec2_t texcoords;
} vertex_t;

typedef struct { 
    vec3_t v;
    vec2_t vt;
    vec3_t vn;
} obj_vertex_t;

typedef enum {
    VERTEX_BUFFER,
    OBJ_VERTEX_BUFFER,
    INDEX_BUFFER
} list_type_e;

typedef struct {
    uint8_t* addr;
    int size;
    int capacity;
    size_t bytes;
    list_type_e type;
} list_t;

// ptr
// |
// |
// |---->  buff-> {pos, color} 0
         // buff-> {pos, color} 1
         // buff-> {pos, color} 2
// sizeof(vertex_buffer_t) * size

list_t* list_create(list_type_e type);
void list_append(list_t* list, void* data);
void list_print(list_t* list);
void list_destroy(list_t* list);

#endif
