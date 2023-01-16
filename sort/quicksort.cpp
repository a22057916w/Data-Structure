#include <iostream>
#include <algorithm>
using namespace std;

int partition(int *arr, int front, int end) {
  int pivot = arr[end]; // alwasys choose the rightmost number
  int i = front - 1;    // i for the smaller number partition
  int j = front;        // j for the larger number partition

  // check through the array to seperate two partitions
  for(; j < end; j++) {
    if(arr[j] < pivot)
      swap(arr[++i], arr[j]);
  }

  // swap the pivot to the middle of the partitions
  swap(arr[end], arr[i + 1]);

  // get the new pivot(or the middle index to seperate two partitions)
  int mid = i + 1;

  return mid;
}

// recursively divide and conquer
void quickSort(int *arr, int front, int end) {
  if(front < end) {
    int mid = partition(arr, front, end);   // get the index between the two partitions
    quickSort(arr, front, mid - 1);
    quickSort(arr, mid + 1, end);
  }
}


void PrintArray(int *arr, int size){
  for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
  }
  cout << std::endl;
}

int main() {
  int n = 9;
  int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};
  cout << "original:\n";
  PrintArray(arr, n);

  quickSort(arr, 0, n-1);

  cout << "sorted:\n";
  PrintArray(arr, n);
}

/*
reference:
  http://alrightchiu.github.io/SecondRound/comparison-sort-quick-sortkuai-su-pai-xu-fa.html
  https://www.geeksforgeeks.org/when-does-the-worst-case-of-quicksort-occur/
*/
