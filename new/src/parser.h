#ifndef PARSER_H
#define PARSER_H

int parsing(char* stream, char** http);
int split_msg(char* msg, char** split);
void split_filename(char* filename, char** split);
int get_method(char* method);
int get_type(char* type);
void get_header(char** http, char** header, int lines);
void get_message(char** http, char* msg, int lines);

#endif