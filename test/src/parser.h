#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <stdlib.h>

#define FILENAME_LEN 128
#define EXTENSION_LEN 16

int get_method(char* buffer);
void get_filename(char* buffer, char* filename);
char* get_extension(char* filename, char* ext);

#endif