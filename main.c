/* 
* Purpose of this file will be to initialize renderer
* Example run: ./xeza cube.obj
* 
*
* TODO: Support of .obj being supported.
* Grab the extension of .obj and check if the extension is equal to obj
* I can start iterating the string at the position of '.' and check save each character after that into a string
* Finally, checking if this string is == to "obj"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "core/gfx.h"

int find_char_index(char *file) {
    int index;

    char* ptr = strchr(file, '.');
    if (!ptr) {
        fprintf(stderr, "failed to find .obj index\n");
        return -1; 
    }

    index = (int)(ptr - file);
    return index;
}

// INFO:
// I was incrementing the original buff pointer by doing (*buff++) and when the buff pointer is returned,
// it is pointing to the address of the null terminated string, which is why I was see no output when trying to 
// print out the buff string. To solve this issue, I save the orginal buff pointer into a temp pointer variable to copy
// characters in a safe manner while keeping the orginal buff pointer.
char* grab_file_extension(char* obj_file) {
    int len = strlen(obj_file);
    int index = find_char_index(obj_file);
    int size = len - index;

    char *buff = malloc(size); 
    assert(buff != NULL);

    char* q = buff;
    char* p = &obj_file[index + 1];

    for (int i = index + 1; i < len; i++) {
        *q++ = *p++; }

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

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: xeza <obj file>\n");
        return -1;
    }
    
    char* obj_file = argv[1];
    char *file_extension = grab_file_extension(obj_file);
    printf("File extension provided: %s\n", file_extension);

    if (strcmp(file_extension, "obj") != 0) {
        fprintf(stderr, "Invalid file extension! Must be of type .obj\n");
        return -1;
    }
    
    // gfx_init(obj_file);
    
    free(file_extension); 
    return 0;
}
