#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct MaxHeap {
    int* data;
    int size, capacity;
} MaxHeap;

// allocation and deallocation
MaxHeap* heap_create(int capacity);
void heap_free(MaxHeap* h);

// operations
bool heap_is_empty(MaxHeap* h);
void heap_insert(MaxHeap* h, int key);
bool heap_peak(MaxHeap* h, int* out);
bool heap_extract(MaxHeap* h, int* out);

// display
void heap_print(MaxHeap* h);

#endif // HEAP_H