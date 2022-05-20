#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "http.h"

char** alloc_http_msg(void)
{	
	char** header;
	
	header = (char**)malloc(sizeof(char*) * MAX_HEADER_LINES);
	for (int i = 0; i < MAX_HEADER_LINES; i++)
	{
		header[i] = (char*)malloc(sizeof(char) * MAX_HEADER_LEN);
		memset(header[i], 0, MAX_HEADER_LEN);
	}
	
	return header;
}

int create_header(char* header, char* http_ver, char* content_type, int content_len, char* buffer)
{
	int len;
	sprintf(header, "\
%s 200 OK\r\n\
Content-Type: %s\r\n\
Content-Length: %d\r\n\
\r\n\
",\
	http_ver, content_type, content_len);	
	len = strlen(header);
	memcpy(header + len, buffer, content_len);
	
	return len + content_len;
}

int load_req_text(char* buffer, char* file)
{
    FILE* fp;
    char c;
    int idx = 0;
    char path[MAX_HEADER_LEN] = "pages/";
    
    strcat(path, file);
    fp = fopen(path, "rb");

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

int load_req_img(char* buffer, char* file)
{
    FILE* fp;
    char c;
    int idx = 0;
    char path[MAX_HEADER_LEN] = "pages/";
    
    strcat(path, file);
    fp = fopen(path, "rb");

    if (fp != NULL)
    {
        while (!(feof(fp)))
        {
			c = fgetc(fp);
            buffer[idx++] = c;
        }
        return idx;
    }
    else
    {
        return -1;
    }
}