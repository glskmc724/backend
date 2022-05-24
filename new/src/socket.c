#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "socket.h"

int create_socket(void)
{
	int sess;
	
	sess = socket(AF_INET, SOCK_STREAM, 0);
	
	return sess;
}

int binding(int port, int listener, int opt)
{
	int sess;
	struct sockaddr_in addr;
	int ret;
	
	if ((sess = create_socket()) != -1)
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port);
		setsockopt(sess, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
		
		if ((ret = bind(sess, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) != -1)
		{
			listen(sess, listener);
			return sess;
		}
	}
	return -1;
}

int accepting(int sess)
{
	int sock;
	int len;
	struct sockaddr_in addr;
	
	len = sizeof(struct sockaddr_in);
	sock = accept(sess, (struct sockaddr*)&addr, &len);
	
	return sock;
}

int recv_stream(int sess, char* buffer)
{
	int len;
	
	len = recv(sess, buffer, MAX_PDU_SIZE, 0);
	buffer[len] = 0;
	
	return len;
}

int send_stream(int sess, char* buffer, int len)
{
	int ret;
	
	ret = send(sess, buffer, len, 0);
	
	return ret;
}