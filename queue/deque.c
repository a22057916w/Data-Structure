#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define USE_LINKED_DEQUE
#define USE_CIRCULAR_DEQUE

#ifdef USE_LINKED_DEQUE
// Linked deque implementation

typedef struct Node {
    int data;
    struct Node *next, *prev;
} Node;


typedef struct Deque {
    int size;
    Node *front, *back;
} Deque;


Deque* deque_create() {
    Deque *dq = (Deque*)malloc(sizeof(Deque));
    if(!dq) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dq->front = dq->back = NULL;
    dq->size = 0;

    return dq;
}

bool deque_is_empty(Deque* dq) {
    return dq->size == 0;
}

void deque_push_back(Deque* dq, int val) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = val;
    newNode->next = NULL;
    if(deque_is_empty(dq)) {
        newNode->prev = NULL;
        dq->back = dq->front = newNode;
    }
    else {
        newNode->prev = dq->back;
        dq->back->next = newNode;
        dq->back = newNode;
    }
    dq->size++;
}

void deque_pop_back(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    Node* tmp = dq->back;
    dq->back = dq->back->prev;

    // if dq->back is the only element in the deque
    if(!dq->back)
        dq->front = NULL;
    else
        dq->back->next = NULL;

    free(tmp);
    dq->size--;
}

int deque_get_back(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return -1;
    }
    return dq->back->data;
}

void deque_push_front(Deque* dq, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = val;
    newNode->prev = NULL;
    if(deque_is_empty(dq)) {
        newNode->next = NULL;
        dq->front = dq->back = newNode;
    }
    else {
        newNode->next = dq->front;
        dq->front->prev = newNode;
        dq->front = newNode;
    }
    dq->size++;
}

void deque_pop_front(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    Node* tmp = dq->front;
    dq->front = dq->front->next;

    // if dq->front is the only element in the deque
    if(!dq->front)
        dq->back = NULL;
    else
        dq->front->prev = NULL;
    
    free(tmp);
    dq->size--;
}

int deque_get_front(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return -1;
    }
    return dq->front->data;
}

int deque_get_size(Deque* dq) {
    return dq->size;
}

void deque_print(Deque* dq) {
    Node* curr = dq->front;

    printf("Deque (front to back): ");
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void deque_print_reverse(Deque* dq) {
    Node* curr = dq->back;

    printf("Deque (back to front): ");
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->prev;
    }
    printf("\n");
}

void deque_free(Deque* dq) {
    while(!deque_is_empty(dq)) 
        deque_pop_front(dq);
    free(dq);
}

#endif // USE_LINKED_DEQUE

#ifdef USE_CIRCULAR_DEQUE
// Circular deque implementation would go here

typedef struct Deque {
    int *data;
    int front, back;
    int capacity, size;
} Deque;

Deque* deque_create(int capacity) {
    Deque *dq = (Deque*)malloc(sizeof(Deque));
    if(!dq) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dq->data = (int*)malloc(sizeof(int) * capacity);
    if(!dq->data) {
        fprintf(stderr, "Memory allocation for data failed\n");
        free(dq);
        exit(EXIT_FAILURE);
    }

    dq->front = 0;
    dq->back = 0;
    dq->capacity = capacity;
    dq->size = 0;

    return dq;
}

bool deque_is_empty(Deque* dq) {
    return dq->size == 0;
}

bool deque_is_full(Deque* dq) {
    return dq->size == dq->capacity;
}   

void deque_resize(Deque* dq) {
    int newCapacity = dq->capacity * 2;
    int *newData = (int*)malloc(sizeof(int) * newCapacity);
    if(!newData) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 將原本環狀資料重新「攤平」成線性順序
    for(int i = 0; i < dq->size; i++) 
        newData[i] = dq->data[(dq->front + i) % dq->capacity];

    free(dq->data);

    dq->data = newData;
    dq->capacity = newCapacity;
    dq->front = 0;
    dq->back = dq->size;

    printf("Deque resized: new capacity = %d\n", dq->capacity);
}

void deque_push_back(Deque* dq, int val) {
    if(deque_is_full(dq)) {
        printf("Deque is full.\n");
        return;
    }

    dq->data[dq->back] = val;
    dq->back = (dq->back + 1) % dq->capacity;  
    dq->size++;
}

void deque_pop_back(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    dq->back = (dq->back - 1 + dq->capacity) % dq->capacity;
    dq->size--;
}

int deque_get_back(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return -1;
    }
    int index = (dq->back - 1 + dq->capacity) % dq->capacity;
    return dq->data[index];
}

void deque_push_front(Deque* dq, int val) {
    if(deque_is_full(dq)) {
        printf("Deque is full.\n");
        return;
    }

    dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    dq->data[dq->front] = val;
    dq->size++;
}

void deque_pop_front(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;
}

int deque_get_front(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return -1;
    }
    return dq->data[dq->front];
}

int deque_get_size(Deque* dq) {
    return dq->size;
}

void deque_print(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    printf("Deque (front to back): ");
    for(int i = 0; i < dq->size; i++) {
        int index = (dq->front + i) % dq->capacity;
        printf("%d ", dq->data[index]);
    }
    printf("\n");
}

void deque_print_reverse(Deque* dq) {
    if(deque_is_empty(dq)) {
        printf("The deque is empty.\n");
        return;
    }

    printf("Deque (back to front): ");
    for(int i = 0; i < dq->size; i++) {
        int index = ((dq->back - 1) - i + dq->capacity) % dq->capacity;
        printf("%d ", dq->data[index]);
    }
    printf("\n");
}

void deque_free(Deque* dq) {
    free(dq->data);
    free(dq);
}

#endif // USE_CIRCULAR_DEQUE

int main() {
#ifdef USE_LINKED_DEQUE
   Deque* dq = deque_create();
#else 
    Deque* dq = deque_create(5);    // USE_CIRCULAR_DEQUE
#endif

    printf("=== Test 1: Push Back ===\n");
    deque_push_back(dq, 10);
    deque_push_back(dq, 20);
    deque_push_back(dq, 30);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
           deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));

    printf("=== Test 2: Push Front ===\n");
    deque_push_front(dq, 5);
    deque_push_front(dq, 1);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
           deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));

    printf("=== Test 3: Pop Front ===\n");
    deque_pop_front(dq);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
           deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));

    printf("=== Test 4: Pop Back ===\n");
    deque_pop_back(dq);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
           deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));

    printf("=== Test 5: Mixed Operations ===\n");
    deque_push_front(dq, 100);
    deque_push_back(dq, 200);
    deque_push_front(dq, 300);
    deque_pop_back(dq);
    deque_push_back(dq, 400);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
           deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));

#ifdef USE_CIRCULAR_DEQUE
    printf("=== Test 6: Manual Resize ===\n");
    printf("Before resize: capacity = %d, size = %d\n", dq->capacity, dq->size);

    // 手動呼叫擴張
    deque_resize(dq);

    deque_push_back(dq, 600);
    deque_push_front(dq, 700);

    printf("After resize: capacity = %d, size = %d\n", dq->capacity, dq->size);
    deque_print(dq);
    deque_print_reverse(dq);
    printf("Front=%d, Back=%d, Size=%d\n\n",
        deque_get_front(dq), deque_get_back(dq), deque_get_size(dq));  
#endif

    deque_free(dq);
    printf("\nAll tests completed.\n");

    return 0;
}