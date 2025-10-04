#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

int main(void) {
    queue q;
    init_queue(&q, 3);

    assert(is_queue_empty(&q));
    assert(push_to_queue(&q, 1));
    assert(push_to_queue(&q, 2));
    assert(push_to_queue(&q, 3));
    assert(!push_to_queue(&q, 4)); // fila cheia

    assert(pull_from_queue(&q) == 1);
    assert(pull_from_queue(&q) == 2);
    assert(pull_from_queue(&q) == 3);
    assert(pull_from_queue(&q) == QUEUE_EMPTY);

    purge_queue(&q);
    printf("✅ All queue tests passed!\n");
    return 0;
}
