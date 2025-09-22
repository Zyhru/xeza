#include "buffer.h"
#include <stdio.h>

list_t* list_create(list_type_e type) {
    //printf("Creating list of type: %d\n", type);

    list_t* list = malloc(sizeof(list_t));
    assert(list != NULL);

    list->capacity = LIST_CAPACITY;
    list->size = 0;
    list->type = type;

    switch(list->type) {
        case VERTEX_BUFFER:
            list->bytes = sizeof(vertex_t);
            printf("Byte size of list: %zu\n", list->bytes);
            break;
        case INDEX_BUFFER:
            list->bytes = sizeof(unsigned int);
            printf("Size of list: %zu\n", list->bytes);
            break;
        default:
            fprintf(stderr, "Invalid list type!\n");
            break; 
    }
   
    list->addr = (void *)malloc(list->bytes * list->size);
    assert(list->addr != NULL);

    //printf("Successfully created list\n");
    return list;
}

void list_append(list_t* list, void* data) {
    if(list->size >= list->capacity) {
        int new_capacity = list->capacity * 2; // use this new capacity to relloacate memory
        void* new_ptr = realloc(list->addr, new_capacity);
        assert(new_ptr != NULL);
       
        free(list->addr);
        list->addr = new_ptr;
    }

    void* ptr = list->addr + list->size * list->bytes;
    memcpy(ptr, data, list->bytes);
    list->size++; // this should only increase in size if the size is >= cap
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
        default:
            break;
    }

}

void list_destroy(list_t *list) {
    if(list != NULL) {
        free(list->addr);
        free(list);
        //list = NULL;
        //list->addr = NULL;
    }
}
