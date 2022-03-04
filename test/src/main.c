#include "main.h"
#include "socket.h"
#include "parser.h"
#include "http.h"
#include "file.h"

void* http_handle(void* pArg)
{
    stream client = *((stream*)pArg);
    int method;
    char filename[FILENAME_LEN];
    char extension[EXTENSION_LEN];
    char buffer[BUFFER_SIZE];
    char header[HEADER_LEN];
    int content_len;

    recv(client.socket, client.rx_stream, BUFFER_SIZE, 0);

    method = get_method(client.rx_stream);
    get_filename(client.rx_stream, filename);
    if (strlen(filename) == 0)
    {
        sprintf(filename, "index");
    }
    get_extension(filename, extension);
    if (strlen(extension) == 0)
    {
        sprintf(extension, "html");
        strcat(filename, ".");
        strcat(filename, extension);
    }
    content_len = read_content(filename, buffer);
    if (!(content_len < 0))
    {
        create_header(header, HTTP_SUCCESS, HTTP_HTML, content_len);
    }
    else
    {
        // 404 Not Found
        content_len = read_content("404.html", buffer);
        create_header(header, HTTP_NOT_FOUND, HTTP_HTML, content_len);
    }
    sprintf(client.tx_stream, "%s", header);
    strcat(client.tx_stream, buffer);

    send(client.socket, client.tx_stream, BUFFER_SIZE, 0);
    close(socket);
}

int main(void)
{
    stream server;
    stream client;

    server.socket = create_server_socket(PORT, 10, 1);

    if (server.socket == -1)
    {
        return 0;
    }
    else
    {
        pthread_t thread;

        while (1)
        {
            client.socket = accept_client_socket(server.socket);

            if (client.socket == -1)
            {
                continue;
            }
            else
            {
                pthread_create(&thread, NULL, http_handle, &client);
            }
        }
    }
}