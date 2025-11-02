#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
    int *data;
    int top;
    int capacity;
} Stack;

Stack* stack_create(int capacity) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if(!s) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->data = (int*)malloc(sizeof(int) * capacity);
    if(!s->data) {
        fprintf(stderr, "Memory allocation failed\n");
        free(s);
        exit(EXIT_FAILURE);
    }

    s->top = -1;
    s->capacity = capacity;

    return s;
}

bool stack_isEmpty(Stack *s) {
    return s->top == -1;
}

bool stack_isFull(Stack *s) {
    return s->top == s->capacity - 1;
}

void stack_resize(Stack *s) {
    int newCapacity = s->capacity * 2;
    int *newData = (int*)realloc(s->data, sizeof(int) * newCapacity);
    if(!newData) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->data = newData;
    s->capacity = newCapacity;
    printf("Stack resized: new capacity = %d\n", s->capacity);
}

void stack_push(Stack *s, int val) {
    if(stack_isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = val;
}

void stack_pop(Stack *s) {
    if(stack_isEmpty(s)) {
        printf("Stack underflow\n");
        return;
    }
    s->top--;
}

int stack_top(Stack *s) {
    if(stack_isEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Indicate error
    }
    return s->data[s->top];
}

void stack_print(Stack *s) {
    if(stack_isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    for(int i = s->top; i >= 0; i--)
        printf("%d ", s->data[i]);
    printf("\n");
}

void stack_free(Stack *s) {
    free(s->data);
    free(s);
}

int main() {
    Stack* s = stack_create(3);

    printf("=== Push until full ===\n");
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_print(s);

    printf("\n=== Try pushing beyond capacity ===\n");
    stack_push(s, 40); // 會 overflow

    printf("\n=== Manually resize stack ===\n");
    stack_resize(s); // 手動擴充容量
    stack_push(s, 40);
    stack_push(s, 50);
    stack_print(s);

    printf("\n=== Pop elements ===\n");
    stack_pop(s);
    stack_pop(s);
    stack_print(s);

    stack_free(s);
    return 0;
}