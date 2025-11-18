#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct QNode {
    void* data;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
    int size;
} Queue;


Queue* queue_create();
bool queue_isEmpty(Queue* q);
void queue_push(Queue* q, void* val);
void queue_pop(Queue* q);
void* queue_front(Queue* q);
void* queue_rear(Queue* q);
int queue_size(Queue* q);
void queue_free(Queue* q);

#endif // QUEUE_H