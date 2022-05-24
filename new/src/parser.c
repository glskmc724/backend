#include <stdio.h>
#include <string.h>

#include "http.h"

int parsing(char* stream, char** http)
{
	char* tok;
	int lines;
	
	lines = 0;
	tok = strtok(stream, "\r\n");
	while (tok != NULL)
	{
		strcpy(http[lines++], tok);
		tok = strtok(NULL, "\r\n");
	}
	
	return lines;
}

int get_method(char* method)
{
	if (strncmp(method, "GET", 3) == 0)
	{
		return HTTP_METHOD_GET;
	}
	else if (strncmp(method, "HEAD", 4) == 0)
	{
		return HTTP_METHOD_HEAD;
	}
	else if (strncmp(method, "POST", 4) == 0)
	{
		return HTTP_METHOD_POST;
	}
	else if (strncmp(method, "PUT", 3) == 0)
	{
		return HTTP_METHOD_PUT;
	}
	else if (strncmp(method, "DELETE", 6) == 0)
	{
		return HTTP_METHOD_DELETE;
	}
	else if (strncmp(method, "CONNECT", 7) == 0)
	{
		return HTTP_METHOD_CONNECT;
	}
	else if (strncmp(method, "OPTIONS", 7) == 0)
	{
		return HTTP_METHOD_OPTIONS;
	}
	else if (strncmp(method, "TRACE", 5) == 0)
	{
		return HTTP_METHOD_TRACE;
	}
	else if (strncmp(method, "PATCH", 5) == 0)
	{
		return HTTP_METHOD_PATCH;
	}
	else
	{
		return HTTP_METHOD_NONE;
	}	
}

int get_type(char* type)
{
	if (strncmp(type, "html", 4) == 0)
	{
		return HTTP_TYPE_HTML;
	}
	else if (strncmp(type, "php", 3) == 0)
	{
		return HTTP_TYPE_PHP;
	}
	else if (strncmp(type, "ico", 3) == 0)
	{
		return HTTP_TYPE_ICON;
	}
	else if (strncmp(type, "png", 3) == 0)
	{
		return HTTP_TYPE_PNG;
	}
	else if (strncmp(type, "jpg", 3) == 0)
	{
		return HTTP_TYPE_JPEG;
	}
}

int split_msg(char* msg, char** split)
{
	char* tok;
	int cnt; 
	
	cnt = 0;
	tok = strtok(msg, " ");
	while (tok != NULL)
	{
		strcpy(split[cnt++], tok);
		tok = strtok(NULL, " ");
	}
	
	return cnt;
}

void split_filename(char* filename, char** split)
{
	char* tok;
	strcpy(split[0], strtok(filename, "."));
	tok = strtok(NULL, " ");
	if (tok == NULL)
	{
		strcpy(split[1], "html");
	}
	else
	{
		strcpy(split[1], tok);
	}
}

void get_header(char** http, char** header, int lines)
{
	for (int i = 0; i < lines - 1; i++)
	{
		strcpy(header[i], http[i + 1]);
	}
	
	for (int i = 0; i < lines - 1; i++)
	{
		printf("%s\n", header[i]);
	}
}

void get_message(char** http, char* msg, int lines)
{
	strcpy(msg, http[lines - 1]);
}
