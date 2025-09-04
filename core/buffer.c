#include "buffer.h"
#include <stdio.h>

list_t* list_create(int size, list_type_e type) {
    if (size <= 0) return NULL;
    
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
    //printf("Appending: {}\n"); // cant get the data at runtime since it's a void*, compiler doesn't like this
    if(list->size >= list->capacity) {
        int new_capacity = list->capacity * 2; // use this new capacity to relloacate memory
        void* new_ptr = realloc(list->addr, new_capacity);
        assert(new_ptr != NULL);
       
        free(list->addr);
        list->addr = new_ptr;
    }

    // TODO: Attend to this monstrosity
    // Debug the seg fault 
    // Think on how to dynamically append this depending on the type
    // addr + 0 + sizeof(vertex_t)
    void* ptr = list->addr + list->size * list->bytes;
    memcpy(ptr, data, list->bytes);
    list->size++;
    //memcpy(&list->buffer[list->size++], data, sizeof(data));
}

void list_print(list_t* list) {
    switch (list->type) {
        case VERTEX_BUFFER:
            for (int i = 0; i < list->size; i++) {
                vertex_t vertex = ((vertex_t *)list->addr)[i];
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
