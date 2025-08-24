#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int util_read_file(char *file_name, char **buffer);
int util_dot_pos(char* file);
char* util_extdup(char* obj_file);

#endif
