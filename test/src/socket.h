#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>

int create_server_socket(int port, int listener, int opt);
int accept_client_socket(int server_socket);

#endif