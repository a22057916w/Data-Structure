#include <stdio.h>

// move the smallest number to the front in each round of i
void selectionSort(int* arr, int arrSize) {
    for(int i = 0; i < arrSize - 1; i++) {
        int min_idx = i;

        for(int j = i + 1; j < arrSize; j++) 
            if(arr[min_idx] > arr[j]) 
                min_idx = j;
        
        if(min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void print_array(int* arr, int arrSize) {
    printf("Array: ");
    for(int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 2};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    printf("arrSize=%d\n", arrSize);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    selectionSort(arr, arrSize);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}