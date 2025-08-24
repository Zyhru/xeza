#include "buffer.h"
#include <stdio.h>

list_t* buffer_create_list(int size, list_type_e type) {
    if (size <= 0) return NULL;

    list_t* list = malloc(sizeof(list_t));
    assert(list != NULL);

    list->capacity = LIST_CAPACITY;
    list->size = size;
    list->type = type;

    size_t size_of_list;
    // check to see what type and return the size of the type
    switch(list->type) {
        case VERTEX_BUFFER:
            size_of_list = sizeof(vertex_t);
            printf("Size of list: %zu\n", size_of_list);
            break;
        case INDEX_BUFFER:
            size_of_list = sizeof(unsigned int);
            printf("Size of list: %zu\n", size_of_list);
            break;
        default:
            fprintf(stderr, "Invalid list type!\n");
            break; 
    }
   
    list->buffer = (void *)malloc(size_of_list * list->size);
    assert(list->buffer != NULL);

    return list;
}

void list_append(list_t* list, void* data) {
    if(list->size >= list->capacity) {
        int new_capacity = list->capacity * 2; // use this new capacity to relloacate memory
        void* new_ptr = realloc(list->buffer, new_capacity);
       
        assert(new_ptr != NULL);
        free(list->buffer);
        
        list->buffer = new_ptr;
    }

    memcpy(&list->buffer[list->size++], data, sizeof(data));
}

void list_print(list_t* list) {
    switch (list->type) {
        case VERTEX_BUFFER:
            for (int i = 0; i < list->size; i++) {
                vertex_t vertex = ((vertex_t *)list->buffer)[i];
                printf("%d: pos %f, %f, %f\n", i, vertex.pos.x, vertex.pos.y, vertex.pos.z);
                printf("%d: color %f, %f, %f\n", i, vertex.color.x, vertex.color.y, vertex.color.z);
            }
            break;
        case INDEX_BUFFER:
            // TODO: Fill this in
            break;
        default:
            break;
    }

}
