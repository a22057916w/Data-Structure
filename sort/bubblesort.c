#include <stdio.h>
#include <stdbool.h>

// move the largest number to the last in each round of i
void bubblesort(int* arr, int arrSize) {
    for(int i = 0; i < arrSize - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < arrSize - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if(!swapped)
            return;
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    bubblesort(arr, arrSize);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}