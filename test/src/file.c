#include "file.h"

int read_content(char* filename, char* buffer)
{
    FILE* fp;
    char c;
    int idx = 0;
    char path[PATH_LEN] = "pages/";
    
    strcat(path, filename);
    fp = fopen(path, "r");

    if (fp != NULL)
    {
        while ((c = fgetc(fp)) != EOF)
        {
            buffer[idx++] = c;
        }
        return idx;
    }
    else
    {
        return -1;
    }
}