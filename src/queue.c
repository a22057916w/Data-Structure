#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue* queue_create() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if(!q) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

bool queue_isEmpty(Queue* q) {
    return q->size == 0;
}

void queue_push(Queue* q, void* val) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    newNode->data = val;
    newNode->next = NULL;
    
    if(queue_isEmpty(q))
        q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

void queue_pop(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is Empty!\n");
        return;
    }

    QNode* temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->size--;
    if(queue_isEmpty(q))
        q->rear = NULL;
}

void* queue_front(Queue* q) {
    return queue_isEmpty(q) ? NULL : q->front->data;
}

void* queue_rear(Queue* q) {
    return queue_isEmpty(q) ? NULL : q->rear->data;
}

int queue_size(Queue* q) {
    return q->size;
}

void queue_free(Queue* q) {
    while(!queue_isEmpty(q)) 
        queue_pop(q);
    free(q);
}