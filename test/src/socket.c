#include "socket.h"

int create_server_socket(int port, int listener, int opt)
{
    int server_socket;
    int res;
    struct sockaddr_in server_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Socket Error\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);    
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if ((res = bind(server_socket, &server_addr, sizeof(server_addr))) == -1)
    {
        printf("Bind Error (%d)\n", res);
        return -1;
    }

    if ((res = listen(server_socket, listener)) == -1)
    {
        printf("Listen Error (%d)\n", res);
        return -1;
    }

    return server_socket;
}

int accept_client_socket(int server_socket)
{
    int client_socket;
    int client_addr_len;
    struct sockaddr_in client_addr;

    client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);

    if (client_socket == -1)
    {
        printf("Accept error\n");
        return -1;
    }

    return client_socket;
}