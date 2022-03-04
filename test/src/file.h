#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>

#define PATH_LEN 256

int read_content(char* filename, char* buffer);

#endif