#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue {
    int* data;
    int front;
    int rear;
    int capacity;

} Queue;

Queue* queue_create(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        fprintf(stderr, "Failed to allocate memory for Queue struct\n");
        exit(EXIT_FAILURE);
    }

    q->data = (int*)malloc(sizeof(int) * capacity);
    if (!q->data) {
        fprintf(stderr, "Failed to allocate memory for Queue data\n");
        free(q);
        exit(EXIT_FAILURE);
    }

    q->front = 0;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}   

bool queue_isFull(Queue* q) {
    return q->rear == q->capacity - 1;
}

bool queue_isEmpty(Queue* q) {
    return q->front > q->rear;
}

void queue_doubleCapacity(Queue* q) {
    q->capacity *= 2;
    int* newData = (int*)malloc(sizeof(int) * q->capacity);
    if (!newData) {
        fprintf(stderr, "Failed to expand queue capacity\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0, j = q->front; j <= q->rear; i++, j++)
        newData[i] = q->data[j];
    
    q->rear = q->rear - q->front;
    q->front = 0;

    free(q->data);
    q->data = newData;
}

void queue_push(Queue* q, int val) {
    if(queue_isFull(q)) {
        printf("Queue is full, double the capacity.\n");
        queue_doubleCapacity(q);
    }

    q->rear++;
    q->data[q->rear] = val;
}

void queue_pop(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is Empty!\n");
        return;
    }

    q->front++;

    // Reset indices when queue becomes empty
    if (q->front > q->rear) {
        q->front = 0;
        q->rear = -1;
    }
}

int queue_front(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->data[q->front];
}

int queue_rear(Queue* q) {
    if(queue_isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
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
    free(q->data);
    q->data = NULL;
    free(q);
}

void queue_print(Queue *q) {
    if(q && !queue_isEmpty(q)) {
        printf("Queue:\n");
        for(int i = q->front; i <= q->rear; i++)
            printf("%d ", q->data[i]);
        printf("\n");
    }
}

int main() {
    // 正常建立 Queue
    Queue *q = queue_create(3);

    printf("\n=== 正常操作 ===\n");
    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);
    queue_pop(q);
    queue_print(q);

    printf("Front: %d, Rear: %d, Capacity: %d\n",
        queue_front(q), queue_rear(q), queue_capacity(q));

    printf("\n=== 觸發擴充 ===\n");
    queue_push(q, 10);
    queue_push(q, 40);
    queue_print(q);

    printf("Front: %d, Rear: %d, Capacity: %d\n",
           queue_front(q), queue_rear(q), queue_capacity(q));

    printf("\n=== 例外測試區 ===\n");

    // 1️⃣ 嘗試從空 Queue 取值
    printf("\n-- 測試空 Queue 取 front --\n");
    Queue *emptyQ = queue_create(2);
    printf("Front: %d\n", queue_front(emptyQ)); // 會印出「Queue is empty!」

    // 2️⃣ 嘗試 pop 空 Queue
    printf("\n-- 測試空 Queue pop --\n");
    queue_pop(emptyQ); // 會印出「Queue is Empty!」

    // 3️⃣ 測試記憶體不足（刻意給超大容量）
    printf("\n-- 測試建立超大 Queue (模擬 malloc 失敗) --\n");
    // ⚠️ 注意：這行會直接 exit(EXIT_FAILURE)，程式會結束
    // 所以實際測試時請註解 / 解註這一段
    // Queue *tooBig = queue_create(1000000000000); 

    // 4️⃣ 測試非法 Queue 指標（NULL）
    printf("\n-- 測試 queue_capacity(NULL) --\n");
    printf("Capacity: %d\n", queue_capacity(NULL)); // 會印出錯誤訊息

    // 5️⃣ 測試 pop 到空的狀態
    printf("\n-- 測試連續 pop 直到空 --\n");
    queue_push(emptyQ, 1);
    queue_push(emptyQ, 2);
    queue_pop(emptyQ);
    queue_pop(emptyQ);
    queue_pop(emptyQ); // 第三次應該印「Queue is Empty!」

    queue_free(emptyQ);
    queue_free(q);

    printf("\n=== 所有測試完成 ===\n");
    return 0;
}

