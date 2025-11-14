#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INSERTION_SORT_THRESHOLD 16

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionsort(int* arr, int front, int end) {
    for(int i = front + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;

        while(j >= front && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int median(int* arr, int l, int r) {
    int m = l + (r - l) / 2;

    if(arr[l] > arr[m])
        swap(&arr[l], &arr[m]);
    if(arr[m] > arr[r])
        swap(&arr[m], &arr[r]);
    if(arr[l] > arr[m])
        swap(&arr[l], &arr[m]);

    return arr[m];
}

int lomuto_partition(int* arr, int front, int end) {
    // choose a random pivot and move it to the end
    int pivotIndex = front + (rand() % (end - front + 1)); 
    swap(&arr[pivotIndex], &arr[end]); 

    int pivot = arr[end];
    int i = front - 1;    // index of current smaller element

    // move elements smaller than pivot to the left
    for(int j = front; j < end; j++) {
        if(arr[j] < pivot) {
            swap(&arr[++i], &arr[j]);
        }
    }

    // place pivot in the middle
    swap(&arr[++i], &arr[end]);

    // return pivot index
    return i;   
}

int hoare_patition(int* arr, int front, int end) {
    int pivot = median(arr, front, end);
    int i = front - 1;
    int j = end + 1;

    while(true) {
        do {
            i++;
        } while(arr[i] < pivot);

        do {
            j--;
        } while(arr[j] > pivot);

        if(i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }

    return j;
}


void quicksort(int* arr, int front, int end) {
    if(front >= end)
        return;
    
    if(end - front + 1 <= INSERTION_SORT_THRESHOLD) {
        insertionsort(arr, front, end);
        return;
    }
    
    int pivot = hoare_patition(arr, front, end);

    quicksort(arr, front, pivot);
    quicksort(arr, pivot + 1, end);
}

void print_array(int* arr, int arrSize) {
    printf("Array: ");
    for(int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 2, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    quicksort(arr, 0, arrSize - 1);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}