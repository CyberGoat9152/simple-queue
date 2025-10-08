#ifndef QUEUE_H
#define QUEUE_H
#define QUEUE_EMPTY "EMPTY"

typedef struct {
    char** values;
    int head;
    int tail;
    int num_entries;
    int size;
} queue ;

void init_queue(queue *queue, int max_size);
void purge_queue(queue *queue);

int is_queue_empty(queue *queue);
int is_queue_full(queue *queue);

int push_to_queue(queue *queue, char* value);
char* pull_from_queue(queue *queue);
#endif