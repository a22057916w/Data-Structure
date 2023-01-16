#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 「由上而下」地，以Max Heap的規則(root的數值「大於」兩個child的數值)，調整矩陣。
// takes O(logN)
void MaxHeapify(vector<int> &arr, int root, int size) {
  int left = root * 2, right = root * 2 + 1;
  int largest = -1;       // record the index of the largest key of the three nodes

  if(left < size && arr[left] > arr[root])
    largest = left;
  else
    largest = root;
  if(right < size && arr[right] > arr[root])
    largest = right;

  if(largest != root) {
    swap(arr[largest], arr[root]);
    MaxHeapify(arr, largest, size);   // 調整新的subtree成Max Heap
  }
}

// 對所有「具有child的node」進行MaxHeapify()，也就是位於index(1) index(⌊N/2⌋)的node，
// 就能夠將任意矩陣調整成Max Heap。
void BuildMaxHeap(vector<int> &arr) {
  for(int i = arr.size() / 2; i >= 1; i--)
    MaxHeapify(arr, i, arr.size());
}

// 將最大值(index(1))換到陣列最後一個位置, 然後不管它, 再對陣列進行 MaxHeapify 回復成 Max Heap.
// 重複上述步驟直到剩兩個node可以交換
// takes O(nlogn)
void HeapSort(vector<int> &arr) {
  arr.insert(arr.begin(), 0);       // 把index(0)空出來以建立heap

  BuildMaxHeap(arr);                // array to Max Heap

  int n = arr.size();               // 用n來記錄「目前要處理的矩陣」之長度
  for(int i = n - 1; i >= 2; i--) {
    swap(arr[1], arr[i]);           // 將最大值放到array的最後一個位置
    MaxHeapify(arr, 1, --n);        // 調整「忽略最後一個位置」的矩陣
  }

  arr.erase(arr.begin());           // 將index(0)刪除
}

void PrintArray(vector<int> &array){
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
  vector<int> array = {9, 4, 1, 6, 7, 3, 8, 2, 5};

  cout << "original:\n";
  PrintArray(array);

  HeapSort(array);

  cout << "sorted:\n";
  PrintArray(array);
}

/*
reference:
  http://alrightchiu.github.io/SecondRound/comparison-sort-heap-sortdui-ji-pai-xu-fa.html
  https://www.geeksforgeeks.org/heap-sort/ (Q & A)
*/
