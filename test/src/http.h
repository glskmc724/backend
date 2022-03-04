#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <string.h>

#define TYPE_LEN 20
#define STATUS_LEN 32
#define HEADER_LEN 1024

enum HTTP_FORMAT { HTTP_PLAIN, HTTP_HTML, HTTP_JPG, HTTP_PNG, HTTP_CSS, HTTP_JS };
enum HTTP_CODE { HTTP_SUCCESS = 200, HTTP_NOT_FOUND = 404, HTTP_SERVER_ERROR = 500 };

int get_content(char* extension);
void create_header(char* header, enum HTTP_CODE code, enum HTTP_FORMAT format, int content_len);

#endif