#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct MaxHeap {
    int* data;
    int size, capacity;
} MaxHeap;

MaxHeap* heap_create();
void heap_free(MaxHeap* h);

bool heap_is_empty(MaxHeap* h);
void heap_insert(MaxHeap* h, int key);
int heap_peak(MaxHeap* h);
void heap_extract(MaxHeap* h);

void heap_print(MaxHeap* h);

#endif // HEAP_H