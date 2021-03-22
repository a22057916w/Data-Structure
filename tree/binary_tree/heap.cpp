#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
    int element;
public:
    MinHeap() {};
    MinHeap(int size): element(0) {
      heap.resize(size, INT_MAX);
    }

    int parent(int index);
    int left(int index);
    int right(int index);
    int getMin();

    // modifying function
    void insert(int key);
    void deletKey(int index);
    void decreaseKey(int index, int val);
    void extractMin();
    void MinHeapify(int index);
};

int MinHeap::parent(int index) {
  return (index - 1) / 2;
}

int MinHeap::right(int index) {
  return (index * 2) + 2;
}

int MinHeap::left(int index) {
  return (index * 2) + 1;
}

// ********************* imp of modifying function *********************
void insert(int key) {
  if(element == heap.size()) {
    cout << Overflow: Could now insert key << endl;
    return;
  }

  // First insert the new key at the end
  element++;
  int i = heap.size() - 1;
  heap[i] = key;

  // Fix the min heap property if it is violated
  while(i > 0 && heap[parent(i)] > heap[i]) {
    swap(heap[parent[i]], heap[i]);
    i = parent(i);
  }
}

void MinHeap::deleteKey(int index) {
  decreaseKey(index, INT_MIN);
  extractMin();
}

// Decreases value of key at index 'index' to new_val(val). It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int index, int val) {
  heap[i] = val;
  while(i > 0 && heap[parent(i)] > heap[i]) {
    swap(heap[parent[i]], heap[i]);
    i = parent(i);
  }
}

// Method to remove minimum element (or root) from min heap
void MinHeap::extractMin() {
  if(element < 1)
    return;

  int root = heap[0];
  heap[0] = heap[element - 1];
  MinHeapify(0);

  return root;
}



int main() {
  return 0;
}
