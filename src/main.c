#include "queue.h"
#include "server.h"
#include <stdio.h>
#include <limits.h>

int main(){
    queue q;

    init_queue(&q, 10);

    start_listening(9152, &q);

}