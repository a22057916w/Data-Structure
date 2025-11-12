#include <stdio.h>

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
    int buckets[BUCKET_COUNT][BUCKET_SIZE] = {0};
    int bucketSize[BUCKET_COUNT] = {0};

    for(int i = 0; i < BUCKET_COUNT; i++) {

    }

}

int main() {
    return 0;
}