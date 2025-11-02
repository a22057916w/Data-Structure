#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// 使用者自定義釋放函式
typedef void (*freeFunc)(void*);

typedef struct Queue {
    void **data;    // 存放指標的陣列
    int front;
    int rear;
    int capacity;
    int size;
    freeFunc free_func;
} Queue;

Queue* queue_create(int capacity, freeFunc free_func) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(!q) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    q->data = (void**)malloc(sizeof(void*) * capacity);
    if(!q->data) {
        fprintf(stderr, "Memory allocation for data failed!\n");
        free(q);
        exit(EXIT_FAILURE);
    }

    q->front = 0;
    q->rear = -1;
    q->capacity = capacity;
    q->size = 0;
    q->free_func = free_func;

    return q;
}

bool queue_isEmpty(Queue* q) {
    return q->size == 0;
}

bool queue_isFull(Queue* q) {
    return q->size == q->capacity;
}


void queue_enqueue(Queue* q, void* item) {
    if(queue_isFull(q)) {
        printf("Queue is full!\n");
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

void* queue_dequeue(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }

    void* item = q->data[q->front];
    q->data[q->front] = NULL;
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return item;    
}

void* queue_front(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }

    return q->data[q->front];
}

void* queue_rear(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }

    return q->data[q->rear];
}

int queue_capacity(Queue* q) {
    if(!q) {
        printf("Can not find a valid queue!\n");
        return -1;
    }
    return q->capacity;
}

void queue_free(Queue *q) {
    if(!q) return;

    if(q->free_func) {
        for(int i = 0; i < q->capacity; i++) {
            if(q->data[i]) {
                q->free_func(q->data[i]);    // 使用者定義的釋放方式
                q->data[i] = NULL;
            }
        }
    }

    free(q->data);
    free(q);
}

void queue_print(Queue *q, void(*print_func)(void*)) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue:\n");
    for(int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        print_func(q->data[index]);
    }
    printf("\n");
}


// ==== helpar functions ====
void print_int(void* p) {
    printf("%d ", *(int*)p);
}

void print_string(void* p) {
    printf("%s ", (char*)p);
}



int main() {
    printf("=== Don't free variable in stack. ===\n");
    int a=10, b=20, c=30;
    Queue* q = queue_create(3, NULL); // 自動釋放
    
    queue_enqueue(q, &a);
    queue_enqueue(q, &b);
    queue_enqueue(q, &c);

    queue_print(q, print_int);
    queue_free(q);

    printf("=== Free memory from heap. ===\n");
    Queue* q2 = queue_create(3, free);
    for (int i = 0; i < 3; i++) {
        int* num = malloc(sizeof(int));
        *num = (i + 1) * 10;
        queue_enqueue(q2, num);
    }

    queue_print(q2, print_int);
    queue_free(q2);
    printf("Mwmory has been free from heap.\n\n");

    printf("=== String Queue ===\n");
    Queue* q3 = queue_create(3, free); 

    queue_enqueue(q3, strdup("apple"));
    queue_enqueue(q3, strdup("banana"));
    queue_enqueue(q3, strdup("cherry"));

    queue_print(q3, print_string);
    queue_free(q3);

    return 0;
}