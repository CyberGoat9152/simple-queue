#include "queue.h"
#include <stdio.h>
#include <limits.h>

int main(){
    queue q;

    init_queue(&q, 10);

    push_to_queue(&q, 9);
    push_to_queue(&q, 1);
    push_to_queue(&q, 5);
    push_to_queue(&q, 4);
    push_to_queue(&q, 42);


    int t;
    while( (t=pull_from_queue(&q)) != QUEUE_EMPTY )
    {
        printf(
            "value = %i\n", t
        );
    }
    
}