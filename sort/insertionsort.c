#include <stdio.h>

// 插入排序: 將陣列分為已排序區間與未排序區間，從未排序區間取出元素插入到已排序區間的適當位置
void insertionSort(int* arr, int arrSize) {
    // 從陣列的第二個元素開始，因為第一個元素本身已經是排序好的
    for(int i = 1; i < arrSize; i++) {
        int curr = arr[i];
        int j  = i - 1;

        // 將 curr 插入到已排序區間 arr[0..i-1] 的適當位置
        while(j >= 0 && arr[j] > curr) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = curr;
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 2, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");
    print_array(arr, arrSize);

    insertionSort(arr, arrSize);

    printf("After sorting:\n");
    print_array(arr, arrSize);

    return 0;
}