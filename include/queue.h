#ifndef QUEUE_H
#define QUEUE_H
#define QUEUE_EMPTY INT_MIN

typedef struct {
    int *values;
    int head;
    int tail;
    int num_entries;
    int size;
} queue ;

void init_queue(queue *queue, int max_size);
void purge_queue(queue *queue);

int is_queue_empty(queue *queue);
int is_queue_full(queue *queue);

int push_to_queue(queue *queue, int value);
int pull_from_queue(queue *queue);
#endif