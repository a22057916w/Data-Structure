#include <stdio.h>

void hello(int times);   // simple function pointer

int add(int x, int y);
int subtract(int x, int y);
int multiply(int x, int y);
int divide(int x, int y);

int main() {
    // simple function pointer
    void (*funcPtr)(int) = hello;
    funcPtr(3);
    
    // function pointer array
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};

    int x, y, choice;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);
    printf("Choose operation: 0-Add, 1-Subtract, 2-Multiply, 3-Divide: ");
    scanf("%d", &choice);

    int result = operations[choice](x, y);
    printf("Result: %d\n", result);

    return 0;
}

void hello(int times) {
    for (int i = 0; i < times; i++)
        printf("Hello, World!\n");
}

int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y;
}

int multiply(int x, int y) {
    return x * y;
}

int divide(int x, int y) {
    if (y != 0) {
        return x / y;
    } else {
        printf("Error: Division by zero!\n");
        return 0;
    }
}