#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

typedef struct Queue Queue;
struct Queue{
    int size;
    void **queue_array;
    int front;
    int rear;

};

void add(Queue *q,void *string);
void *pull(Queue *q);
Queue * init_q(int size);
#endif
