#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;


typedef struct Queue {
    Node *front, *rear;
    int size;
} Queue;


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

void queue_push(Queue* q, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
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

    Node* temp = q->front;
    q->front = q->front->next;
    free(temp);

    // Reset rear if the queue becomes empty
    if(q->front == NULL)
        q->rear = NULL;

    q->size--;
}

int queue_front(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->front->data;
}

int queue_rear(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->rear->data;
}

int queue_size(Queue* q) {
    return q->size;
}

void queue_print(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    Node* curr = q->front;
    printf("Queue: ");
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void queue_free(Queue* q) {
    if (!q) return;
    while(!queue_isEmpty(q)) 
        queue_pop(q);
    free(q);
}

int main() {
    Queue* q = queue_create();

    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);
    queue_print(q);

    printf("Front: %d, Rear: %d, Size: %d\n",
           queue_front(q), queue_rear(q), queue_size(q));

    queue_pop(q);
    queue_print(q);

    queue_pop(q);
    queue_pop(q);
    queue_pop(q);  // 多 pop 會出現「Queue is empty!」

    queue_push(q, 99);
    queue_print(q);

    queue_free(q);
    q = NULL;
    return 0;
}