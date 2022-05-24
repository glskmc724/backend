#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "handler.h"
#include "socket.h"
#include "parser.h"
#include "http.h"

char** alloc_http_msg(void);
void get_handler(char** http, char** header, char** request, int lines, int user);

void* handler(void* arg)
{
	int user = (*(int*)arg);
	char stream[MAX_PDU_SIZE];
	int len;
	char** http;
	char** header;
	char** request;
	int lines;
	int method;
	
	len = recv_stream(user, stream);
	http = alloc_http_msg();
	header = alloc_http_msg();
	request = alloc_http_msg();
	lines = parsing(stream, http);
	split_msg(http[0], request);
	method = get_method(request[0]);
	switch (method)
	{
		case HTTP_METHOD_GET:
			get_handler(http, header, request, lines, user);
			break;
		case HTTP_METHOD_POST:
			printf("TEST\n");
			break;
	}
	close(user);
}

void get_handler(char** http, char** header, char** request, int lines, int user)
{
	int req_len;
	char* tx;
	char* buffer;
	char file[MAX_HEADER_LEN];
	char** filename;
	int type;
	int len;
	
	tx = (char*)malloc(sizeof(char) * 10240000);
	buffer = (char*)malloc(sizeof(char) * 10240000);
	printf("%s\n", request[1]);
	if (strlen(request[1]) == 1)
	{
		req_len = load_req_text(buffer, "/index.html");
		len = create_header(tx, request[2], "text/html", req_len, buffer);
	}
	else
	{
		filename = alloc_http_msg();
		split_filename(request[1], filename);
		type = get_type(filename[1]);
		switch (type)
		{
			case HTTP_TYPE_HTML:
				sprintf(file, "/%s.%s", filename[0], filename[1]);
				req_len = load_req_text(buffer, file);
				len = create_header(tx, request[2], "text/html", req_len, buffer);
				break;
			case HTTP_TYPE_PHP:
				sprintf(file, "/%s.%s", filename[0], filename[1]);
				req_len = load_req_php(buffer, file);
				len = create_header(tx, request[2], "text/html", req_len, buffer);
				break;
			case HTTP_TYPE_ICON:
				sprintf(file, "/%s.%s", filename[0], filename[1]);
				req_len = load_req_img(buffer, file);
				len = create_header(tx, request[2], "image/x-icon", req_len, buffer);
				break;
			case HTTP_TYPE_PNG:
				sprintf(file, "/%s.%s", filename[0], filename[1]);
				req_len = load_req_img(buffer, file);
				len = create_header(tx, request[2], "image/png", req_len, buffer);
				break;
			case HTTP_TYPE_JPEG:
				sprintf(file, "/%s.%s", filename[0], filename[1]);
				req_len = load_req_img(buffer, file);
				len = create_header(tx, request[2], "image/jpg", req_len, buffer);
				break;
		}
	}
	if (req_len == -1)
	{
		req_len = load_req_text(buffer, "/404.html");
		len = create_header(tx, request[2], "text/html", req_len, buffer);
	}
	send_stream(user, tx, len);
	free(tx);
	free(buffer);
}

int handling(int user)
{
	pthread_t handle;
	int handle_id;
	
	handle_id = pthread_create(&handle, NULL, handler, (void*)&user);
	
	return handle_id;
}

