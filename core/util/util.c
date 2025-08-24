#include "util.h"

int util_dot_pos(char* file) {
    int index;

    char* ptr = strchr(file, '.');
    assert(ptr != NULL);

    index = (int)(ptr - file);
    return index;
}

// INFO:
// I was incrementing the original buff pointer by doing (*buff++) and when the buff pointer is returned,
// it is pointing to the address of the null terminated string, which is why I was see no output when trying to 
// print out the buff string. To solve this issue, I save the orginal buff pointer into a temp pointer variable to copy
// characters in a safe manner while keeping the orginal buff pointer.
char* util_extdup(char* obj_file) {
    int len = strlen(obj_file);
    int index = util_dot_pos(obj_file);
    int size = len - index;

    char* buff = malloc(size); 
    assert(buff != NULL);

    char* q = buff;
    char* p = &obj_file[index + 1];

    for (int i = index + 1; i < len; i++) *q++ = *p++;

    *q++ = '\0';
    return buff;
} 

// INFO: 
// Source: https://stackoverflow.com/questions/10375728/copy-character-from-string-to-another-string-in-c
// This is better since this function has a general purpose
char* substr(char* s, int x, int y) {
    char* ret = malloc(strlen(s) + 1);
    char* p = ret;
    char* q = &s[x]; // s[5]

    assert(ret != NULL);

    while(x < y) {
        *p++ = *q++;
        x++; 
    }

    *p++ = '\0';

    return ret;
}

int util_read_file(char *file_name, char **buffer) {
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stderr, "unable to open file: %s\n", file_name); 
        return -1;
    }

    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    size_t n = size + 1;
    *buffer = malloc(n);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate %zu number of bytes\n", n); 
        fclose(fp);
        return -1;
    }

    fread(*buffer, 1, size, fp);
    (*buffer)[size] = '\0';

    fclose(fp);
    return 0;
}
