#include "queue.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_EMPTY INT_MIN

void init_queue(queue *queue, int max_size) {
    queue->size        = max_size;
    queue->values      = malloc(sizeof(int)* queue->size);
    queue->num_entries = 0; // starts empty
    queue->head        = 0;
    queue->tail        = 0;
}

void purge_queue(queue *queue) {
    free(queue->values);
}

int is_queue_empty(queue *queue){
    return (queue->num_entries == 0);
}

int is_queue_full(queue *queue){
    return (queue->num_entries == queue->size);
}

int push_to_queue(queue *queue, int value){
    if ( is_queue_full(queue) ){
        return 0;
    }

    queue->values[ queue->tail ] = value;
    queue->tail                  = (queue->tail + 1) % queue->size;
    queue->num_entries++;

    return 1;
}

int pull_from_queue(queue *queue) {
    int result;
    
    if (is_queue_empty(queue)) {
        return QUEUE_EMPTY;
    }

    result      = queue->values[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->num_entries--;

    return result;
}

