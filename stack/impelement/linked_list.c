#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
    int size;
} Stack;

Stack* stack_create() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if(!s) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->top = NULL;
    s->size = 0;
    
    return s;
}

bool stack_isEmpty(Stack *s) {
    return s->top == NULL;
}

void stack_push(Stack *s, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

void stack_pop(Stack *s) {
    if(stack_isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }
    
    Node* tmp = s->top;
    s->top = s->top->next;
    free(tmp);
    s->size--;
}

int stack_top(Stack* s) {
    if(stack_isEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Indicate error
    }
    return s->top->data;
}

void stack_print(Stack* s) {
    if(stack_isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    Node* curr = s->top;
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int stack_size(Stack* s) {
    return s->size;
}

void stack_free(Stack* s) {
    while(!stack_isEmpty(s)) {
        stack_pop(s);
    }
    free(s);
}


int main() {
    Stack* s = stack_create();

    printf("=== Push ===\n");
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_print(s);

    printf("\nTop element: %d\n", stack_top(s));
    printf("Size: %d\n", stack_size(s));

    printf("\n=== Pop ===\n");
    stack_pop(s);
    stack_print(s);
    printf("Top element: %d\n", stack_top(s));
    printf("Size: %d\n", stack_size(s));

    printf("\n=== More Push ===\n");
    stack_push(s, 40);
    stack_push(s, 50);
    stack_print(s);

    printf("\n=== Pop All ===\n");
    while (!stack_isEmpty(s)) {
        printf("Pop: %d\n", stack_top(s));
        stack_pop(s);
    }

    printf("Stack is now empty.\n");
    stack_free(s);
    
    return 0;
}