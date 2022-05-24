#ifndef HTTP_H
#define HTTP_H

#define MAX_HEADER_LINES 16
#define MAX_HEADER_LEN 128

enum HTTP_METHOD { HTTP_METHOD_NONE = 0,
					HTTP_METHOD_GET, 
					HTTP_METHOD_HEAD, 
					HTTP_METHOD_POST, 
					HTTP_METHOD_PUT, 
					HTTP_METHOD_DELETE, 
					HTTP_METHOD_CONNECT, 
					HTTP_METHOD_OPTIONS, 
					HTTP_METHOD_TRACE, 
					HTTP_METHOD_PATCH };

enum HTTP_TYPE { HTTP_TYPE_NONE = 0,
					HTTP_TYPE_HTML,
					HTTP_TYPE_PHP,
					HTTP_TYPE_ICON,
					HTTP_TYPE_PNG,
					HTTP_TYPE_JPEG, };

char** alloc_http_msg(void);
int create_header(char* header, char* http_ver, char* content_type, int content_len, char* buffer);
int load_req_text(char* buffer, char* file);
int load_req_img(char* buffer, char* file);
int load_req_php(char* buffer, char* file);

#endif
