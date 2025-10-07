#include "buffer.h"

list_t* list_create(list_type_e type) {
    list_t* list = malloc(sizeof(list_t));
    assert(list != NULL);

    list->capacity = LIST_CAPACITY;
    list->size = 0;
    list->type = type;

    switch(list->type) {
        case VERTEX_BUFFER:
            list->bytes = sizeof(vertex_t);
            printf("Creating a VERTEX_BUFFER list\n");
            printf("Size of list in bytes: %zu\n", list->bytes);
            break;
        case INDEX_BUFFER:
            list->bytes = sizeof(unsigned int);
            printf("Creating an INDEX_BUFFER list\n");
            printf("Size of list in bytes: %zu\n", list->bytes);
            break;
        case OBJ_VERTEX_BUFFER:
            list->bytes = sizeof(obj_vertex_t);
            printf("Creating an OBJ_VERTEX_BUFFER list\n");
            printf("Size of list in bytes: %zu\n", list->bytes);
            break;
        default:
            fprintf(stderr, "Invalid list type!\n");
            break; 
    }
   
    assert(list->bytes >= 0);
    list->addr = (void *)malloc(list->bytes * list->capacity);
    assert(list->addr != NULL);
    return list;
}

void list_append(list_t* list, void* data) {
    if(list->size >= list->capacity) {
        int new_capacity = list->capacity * 2;
        void* new_ptr = realloc(list->addr, new_capacity * list->bytes);
        assert(new_ptr != NULL);
        list->addr = new_ptr;
        list->capacity = new_capacity;
    }

    uint8_t* ptr = list->addr + list->size * list->bytes;
    memcpy(ptr, data, list->bytes);
    list->size++;
}

void list_print(list_t* list) {
    switch (list->type) {
        case VERTEX_BUFFER:
            printf("Vertex Buffer List size: %d\n", list->size);
            for (int i = 0; i < list->size; i++) {
                vertex_t vertex = ((vertex_t *)list->addr)[i];
                printf("%d: pos %f, %f, %f\n", i, vertex.pos.x, vertex.pos.y, vertex.pos.z);
                printf("%d: color %f, %f, %f\n", i, vertex.color.x, vertex.color.y, vertex.color.z);
            }
            break;
        case INDEX_BUFFER:
            printf("Index Buffer List size: %d\n", list->size);
            for (int i = 0; i < list->size; i++) {
                unsigned int index = ((unsigned int *)list->addr)[i];
                printf("%d: %d\n", i, index);
            }
            break;
        case OBJ_VERTEX_BUFFER:
            printf("OBJ Vertex Buffer List size: %d\n", list->size);
            for (int i = 0; i < list->size; i++) {
                obj_vertex_t vertex = ((obj_vertex_t *)list->addr)[i];
                printf("%d: v {%f, %f, %f}\n", i, vertex.v.x, vertex.v.y, vertex.v.z);
                printf("%d: vt {%f, %f}\n", i, vertex.vt.x, vertex.vt.y);
                printf("%d: vn {%f, %f, %f}\n", i, vertex.vn.x, vertex.vn.y, vertex.vn.z);
            }
            break;
        default:
            fprintf(stderr, "Invalid list type.\n");
            break;
    }

}

void list_destroy(list_t *list) {
    if(list != NULL) {
        if(list->addr != NULL) {
            free(list->addr);
        }
        
        free(list);
    }
}
