#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int currMin;
    struct Node* next;
} Node;

typedef struct MinStack {
    Node* top;
    int size;
} MinStack;


MinStack* minStack_create() {
    MinStack* s = (MinStack*)malloc(sizeof(MinStack));
    if(!s) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->top = NULL;
    s->size = 0;

    return s;
}

bool minStack_isEmpty(MinStack* s) {
    return s->size == 0;
}

void minStack_push(MinStack* s, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = val;
    if(minStack_isEmpty(s))
        newNode->currMin = val;
    else 
        newNode->currMin = (val < s->top->currMin) ? val : s->top->currMin;

    newNode->next = s->top;
    s->top = newNode;
    s->size++;

}

void minStack_pop(MinStack* s) {
    if(minStack_isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    Node* tmp = s->top;
    s->top = s->top->next;
    free(tmp);
    s->size--;
}

int minStack_top(MinStack* s) {
    if(minStack_isEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Indicate error
    }
    return s->top->data;
}

int minStack_getMin(MinStack* s) {
    if(minStack_isEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Indicate error
    }
    return s->top->currMin;
}

void minStack_print(MinStack* s) {
    if(minStack_isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    Node* curr = s->top;
    printf("Stack elements: ");
    while(curr) {
        printf("[data: %d, currMin: %d] ", curr->data, curr->currMin);
        curr = curr->next;
    }
    printf("\n");
}

void minStack_free(MinStack* s) {
    while(!minStack_isEmpty(s)) {
        minStack_pop(s);
    }
    free(s);
}

int main() {
    MinStack* s = minStack_create();

    printf("=== Push ===\n");
    minStack_push(s, 5);
    minStack_push(s, 3);
    minStack_push(s, 7);
    minStack_push(s, 2);
    minStack_push(s, 8);
    minStack_print(s);
    printf("Current min = %d\n", minStack_getMin(s));

    printf("\n=== Pop ===\n");
    minStack_pop(s);
    minStack_print(s);
    printf("Current min = %d\n", minStack_getMin(s));

    printf("\n=== Push again ===\n");
    minStack_push(s, 1);
    minStack_print(s);
    printf("Current min = %d\n", minStack_getMin(s));

    printf("\n=== Pop all ===\n");
    while (!minStack_isEmpty(s)) {
        printf("Pop %d\n", minStack_top(s));
        minStack_pop(s);
        if (!minStack_isEmpty(s))
            printf("New min = %d\n", minStack_getMin(s));
    }

    minStack_free(s);
    return 0;
}