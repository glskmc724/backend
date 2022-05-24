#ifndef SOCKET_H
#define SOCKET_H

#define MAX_PDU_SIZE 1500

int binding(int port, int listener, int opt);
int accepting(int sess);
int recv_stream(int sess, char* buffer);
int send_stream(int sess, char* buffer, int len);

#endif