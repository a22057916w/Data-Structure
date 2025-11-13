#include <stdio.h>
#include <stdlib.h>


void countingsort(int* arr, int arrSize, int exp) {
    int* output = (int*)malloc(sizeof(int) * arrSize);
    int count[10] = {0};

    // store count of occurrences in count[]
    for(int i = 0 ; i < arrSize; i++)
        count[(arr[i] / exp) % 10]++;

    // calaculate prefix sum to preserve stability
    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // build the output array backwards to maintain stability
    for(int i = arrSize - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];  // -1 for 0-based index
        count[digit]--;
    }

    // copy the output array to arr
    for(int i = 0; i < arrSize; i++)
        arr[i] = output[i];
    
    free(output);
}


void radixsort(int* arr, int arrSize) {
    int max = arr[0];

    // find the maximum number to know number of digits
    for(int i = 1; i < arrSize; i++)
        if(arr[i] > max)    
            max = arr[i];

    // Do counting sort for every digit
    for(int exp = 1; max / exp > 0; exp *= 10) 
        countingsort(arr, arrSize, exp);
}

void print_array(int* arr, int arrSize) {
    printf("Array: ");
    for(int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    radixsort(arr, arrSize);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}