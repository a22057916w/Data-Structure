#include <stdio.h>
#include <stdlib.h>

// merge arr[front..mid] anr arr[mid+1..end] into arr[front..end]
void merge(int* arr, int front, int mid, int end) {
    int leftSize = mid - front + 1;
    int rightSize = end - mid;

    // create temp arrays
    int* leftArr = (int*)malloc(sizeof(int) * leftSize);
    int* rightArr = (int*)malloc(sizeof(int) * rightSize);

    // copy data to temp arrays
    for(int i = 0; i < leftSize; i++)
        leftArr[i] = arr[front + i];
    for(int i = 0; i < rightSize; i++)
        rightArr[i] = arr[mid + 1 + i];

    // merge the temp arrays back into arr[front..end]
    int i = 0, j = 0;
    while(i < leftSize && j < rightSize) {
        if(leftArr[i] <= rightArr[j])
            arr[front++] = leftArr[i++];
        else
            arr[front++] = rightArr[j++];
    }

    // copy the remaining elements of leftArr or rightArr, if any
    while(i < leftSize)
        arr[front++] = leftArr[i++];
    while(j < rightSize)
        arr[front++] = rightArr[j++];
    
    free(leftArr);
    free(rightArr);
}


void mergesort(int* arr, int front, int end) {
    if(front >= end)
        return;

    int mid = (front + end) >> 1;

    mergesort(arr, front, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, front, mid, end);
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

    mergesort(arr, 0, arrSize - 1);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}