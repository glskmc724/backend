#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define PORT        11111
#define BUFFER_SIZE 2048
#define METHOD_LEN  5

enum METHOD { METHOD_UNKNOWN, METHOD_GET, METHOD_POST };

typedef struct
{
    int socket;
    char tx_stream[BUFFER_SIZE];
    char rx_stream[BUFFER_SIZE];
} stream;


#endif