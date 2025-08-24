#ifndef BUFFER_H 
#define BUFFER_H

#include "api.h"
#include "math.h"

#define LIST_CAPACITY 50

typedef struct { 
    vec3_t pos;
    vec3_t color;
} vertex_t;


typedef enum {
    VERTEX_BUFFER,
    INDEX_BUFFER
} list_type_e;

typedef struct {
    void* buffer;
    int size;
    int capacity;
    list_type_e type;
} list_t;

// ptr
// |
// |
// |---->  buff-> {pos, color} 0
         // buff-> {pos, color} 1
         // buff-> {pos, color} 2
// sizeof(vertex_buffer_t) * size

list_t* buffer_create_list(int size, list_type_e type);
void list_append(list_t* list, void* data);
void list_print(list_t* list);

#endif
