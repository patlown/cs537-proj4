#include "queue.h"


Queue * init_q(int size){
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    if(q == NULL){
        printf("cannot allocate mem\n");
        return NULL;
    }
    q->size = size;
    q->queue_array = (void**)malloc(sizeof(void*)*size);
    q->front = 0;
    q->rear =  0;
    return q;
}



void add(Queue *q,void *string){
    if((q->rear + 1)%q->size == q->front){
        fprintf(stderr,"queue size exceeded!");
        exit(1);
    }

    q->queue_array[q->rear] = string;
    q->rear = (q->rear+1)%q->size;


}



void *pull(Queue *q){
    if(q->rear == q->front){
        return NULL;
    }
    void *ans = q->queue_array[q->front];
    q->front = (q->front+1)%q->size;
    return ans;
}




