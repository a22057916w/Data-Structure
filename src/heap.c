#include "heap.h"
#include <stdio.h>
#include <stdlib.h>


// Helper functions
static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline int parent(int i) {
    return (i - 1) / 2;
}
static inline int left(int i) {
    return (i * 2) + 1;
}
static inline int right(int i) {
    return (i * 2) + 2;
}

static void heapify(MaxHeap* h, int index) {
    int l = left(index);
    int r = right(index);

    int greatest = index;
    if(l < h->size && h->data[l] > h->data[index])
        greatest = l;
    if(r < h->size && h->data[r] > h->data[greatest])
        greatest = r;
    if(greatest != index) {
        swap(&h->data[index], &h->data[greatest]);
        heapify(h, greatest);
    }
}

// Heap functions
MaxHeap* heap_create(int capacity) {
    MaxHeap* h = malloc(sizeof(MaxHeap));
    if(!h) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    h->data = malloc(sizeof(int) * capacity);
    if(!h->data) {
        fprintf(stderr, "Memory allocation failed\n");
        free(h);
        exit(EXIT_FAILURE);
    }

    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heap_free(MaxHeap* h) {
    if(h) {
        free(h->data);
        free(h);
    }
}

bool heap_is_empty(MaxHeap* h) {
    return h->size == 0;
}

void heap_insert(MaxHeap* h, int key) {
    if(h->size == h->capacity) {
        printf("Heap overflow: could not insert key\n");
        return;
    }
    
    // insert the new key at the end
    h->data[h->size] = key;
    int i = h->size;

    // fix the max heap property if it is violated
    while(i > 0 && h->data[parent(i)] < h->data[i]) {
        swap(&h->data[parent(i)], &h->data[i]);
        i = parent(i);
    }

    h->size++;
}

bool heap_peak(MaxHeap* h, int* out) {
    if(heap_is_empty(h)) 
        return false;
    
    *out = h->data[0];
    return true;
}

bool heap_extract(MaxHeap* h, int* out) {
    if(heap_is_empty(h)) {
        fprintf(stderr, "Heap underflow: could not extract key\n");
        return false;
    }

    *out = h->data[0];

    // replace root with last element
    h->data[0] = h->data[h->size - 1];
    h->size--;

    // recursively heapify the root and subtrees
    heapify(h, 0);

    return true;
}

void heap_print(MaxHeap* h) {
    if(heap_is_empty(h)) {
        printf("Heap is empty\n");
        return;
    }

    printf("Heap elements: ");
    for(int i = 0; i < h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}