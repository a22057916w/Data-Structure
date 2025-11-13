#include <stdio.h>
#include <stdlib.h>

#define BUCKET_COUNT 5
#define BUCKET_SIZE 10

void insertionSort(int* arr, int arrSize) {
    for(int i = 1; i < arrSize; i++) {
        int key = arr[i];
        int j  = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketsort(int* arr, int arrSize) {
    int maxVal = -1e9, minVal = 1e9;

    // find min and max
    for(int i = 0; i < arrSize; i++) {
        if(arr[i] > maxVal) maxVal = arr[i];
        if(arr[i] < minVal) minVal = arr[i];
    }

    int buckets[BUCKET_COUNT][BUCKET_SIZE];
    int bucketSize[BUCKET_COUNT];     // track current size of each bucket

    // distribute input array values into buckets
    for(int i = 0; i < arrSize; i++) {
        // normalize value to [0, 1) and map to bucket index
        float norm = (float)(arr[i] - minVal) / (float)(maxVal - minVal + 1);
        int idx = (int)(norm * BUCKET_COUNT);

        if(bucketSize[idx] < BUCKET_SIZE)
            buckets[idx][bucketSize[idx]++] = arr[i];
        else {
            fprintf(stderr, "Bucket-%d is full!\n", idx);
            exit(EXIT_FAILURE);
        }
    }
    
    // sort each bucket
    for(int i = 0; i < BUCKET_COUNT; i++) 
        insertionSort(buckets[i], bucketSize[i]);

    // concatenate buckets back into original array
    int k = 0;
    for(int i = 0; i < BUCKET_COUNT; i++) {
        for(int j = 0; j < bucketSize[i]; j++) {
            arr[k++] = buckets[i][j];
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 2, 5, 78, 56, 43, 89, 15};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("=== BUCKET_COUNT=%d, BUCKET_SIZE=%d ===\n\n", BUCKET_COUNT, BUCKET_SIZE);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    bucketsort(arr, arrSize);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}