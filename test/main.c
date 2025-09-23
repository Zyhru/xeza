#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR -1

typedef struct {
    int x;
} foo_t;

typedef struct {
    foo_t bar;
} test_t;

void testing(test_t* t) {
    foo_t foo;
    foo.x = 10;
    t->bar = foo;
}


void f(int *ptr) {
    printf("Value of ptr is %d\n", *ptr);
}

int read_file(char **buffer) {
    FILE *fp = fopen("../shaders/vertex.glsl", "rb");
    if (!fp) {
        printf("Failed to open shader file\n");       
        return -1;
    }

    // grab the size of the buffer by moving the fp to the end
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // allocate mem for the buffer based on the size
    *buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "allocation for file buffer failed!\n");
        return -1;
    }

    // buffer size = 190
    // 0 - 189

    // read the entire file
    fread(*buffer, 1, size, fp); // sizeof(*buffer) will return 1 since the size of a character is 1byte?
    (*buffer)[size] = '\0';
    printf("we did it!\n");

    return 0;
}

int main() {
    test_t test;
    printf("%d\n", test.bar.x);
    testing(&test);
    printf("%d\n", test.bar.x);

    return 0;
}
