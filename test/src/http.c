#include "http.h"

int get_content(char* extension)
{
    if (strcmp(extension, "html") == 0)
    {
        return HTTP_HTML;
    }
    else if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0)
    {
        return HTTP_JPG;
    }
    else if (strcmp(extension, ".png") == 0)
    {
        return HTTP_PNG;
    }
    else if (strcmp(extension, ".css") == 0)
    {
        return HTTP_CSS;
    }
    else if (strcmp(extension, ".js") == 0)
    {
        return HTTP_JS;
    }
    else
    {
        return HTTP_PLAIN;
    }
}

void create_header(char* header, enum HTTP_CODE code, enum HTTP_FORMAT format, int content_len)
{
    char type[TYPE_LEN];
    char status[STATUS_LEN];

    switch (code)
    {
        case HTTP_SUCCESS:
        sprintf(status, "OK");
        break;
        case HTTP_NOT_FOUND:
        sprintf(status, "Not Found");
        break;
        case HTTP_SERVER_ERROR:
        sprintf(status, "Internal Server Error");
        break;
    }

    switch (format)
    {
        case HTTP_HTML:
        sprintf(type, "text/html");
        break;
        case HTTP_JPG:
        sprintf(type, "image/jpeg");
        break;
        case HTTP_PNG:
        sprintf(type, "image/png");
        break;
        case HTTP_CSS:
        sprintf(type, "text/css");
        break;
        case HTTP_JS:
        sprintf(type, "text/javascript");
        break;
        case HTTP_PLAIN:
        sprintf(type, "text/plain");
        break;
    }

    sprintf(header, "HTTP/1.1 %d %s\r\nServer:Iron Web Server\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n", code, status, content_len, type);
}