#ifndef SERVER_H
#define SERVER_H
#include "queue.h"

#define BUFFER_SIZE 1024

int start_listening(int port, queue *how_queue);

#endif
