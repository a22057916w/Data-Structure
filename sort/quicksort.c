#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int front, int end) {
    int pivot = arr[end]; // always choose the rightmost element as pivot
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


void quicksort(int* arr, int front, int end) {
    if(front >= end)
        return;
    
    int pivot = partition(arr, front, end);

    quicksort(arr, front, pivot - 1);
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