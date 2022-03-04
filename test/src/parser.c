#include "main.h"
#include "parser.h"

void istrtok(char* buffer, char* dest, char ch, char* least)
{
    int idx;
    int len;
    static char* last = NULL;

    if (buffer != NULL)
    {
        last = buffer;
        len = strlen(buffer);
    }
    else
    {
        len = strlen(last);
    }

    for (idx = 0; idx < len; idx++)
    {
        if (last[idx] == ch)
        {
            strncpy(dest, last, idx);
            last += (idx + 1);
            if (least != NULL)
            {
                strncpy(least, last, len - idx);
            }
            break;
        }
    }

    if (dest != NULL)
    {
        dest[idx] = 0;
    }
}

int get_method(char* buffer)
{
    int len;
    char method[METHOD_LEN];
    istrtok(buffer, method, ' ', NULL);
    if (strcmp(method, "GET") == 0)
    {
        return METHOD_GET;
    }
    else if (strcmp(method, "POST") == 0)
    {
        return METHOD_POST;
    }
    else
    {
        return METHOD_UNKNOWN;
    }
}

void get_filename(char* buffer, char* filename)
{
    int len;
    istrtok(buffer, filename, ' ', NULL);
    istrtok(NULL, filename, ' ', NULL);
    len = strlen(filename);
    for (int i = 1; filename[i] != 0; i++)
    {
        filename[i - 1] = filename[i];
    }
    filename[len - 1] = 0;
}

char* get_extension(char* filename, char* ext)
{
    int len;
    char name[FILENAME_LEN];
    istrtok(filename, name, '.', ext);
}