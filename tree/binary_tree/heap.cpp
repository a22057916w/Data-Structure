/*
Reference:
https://www.geeksforgeeks.org/binary-heap/
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
    int element;            // recored the size(elements) of the vector
public:
    MinHeap(int size): element(0) {
      heap.resize(size, INT_MAX);
    }

    // element access
    int parent(int index);
    int left(int index);
    int right(int index);
    int getMin();

    // modifying function
    void insert(int key);
    void deleteKey(int index);
    void decreaseKey(int index, int val);     // called by deleteKey()
    void extractMin();                        // called by deletekey()
    void MinHeapify(int index);               // called by extractMin()
};

// ************************ imp of element access ****************************
int MinHeap::parent(int index) {
  return (index - 1) / 2;
}

int MinHeap::right(int index) {
  return (index * 2) + 2;
}

int MinHeap::left(int index) {
  return (index * 2) + 1;
}

int MinHeap::getMin() {
  return heap[0];
}

// ************************ imp of modifying function *************************
void MinHeap::insert(int key) {
  if(element == heap.size()) {
    cout << "Overflow: Could now insert key" << endl;
    return;
  }

  // First insert the new key at the end
  element++;
  int i = element - 1;
  heap[i] = key;

  // Fix the min heap property if it is violated
  while(i > 0 && heap[parent(i)] > heap[i]) {
    swap(heap[parent(i)], heap[i]);
    i = parent(i);
  }
}

void MinHeap::deleteKey(int index) {
  decreaseKey(index, INT_MIN);
  extractMin();
}

// Decreases value of key at index 'index' to new_val(val). It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int val) {
  heap[i] = val;
  while(i > 0 && heap[parent(i)] > heap[i]) {
    swap(heap[parent(i)], heap[i]);
    i = parent(i);
  }
}

// Method to remove minimum element (or root) from min heap
void MinHeap::extractMin() {
  if(element < 1)
    return;

  heap[0] = heap[element - 1];
  element--;
  MinHeapify(0);
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i) {
  int l = left(i);
  int r = right(i);

  int smallest = i;
  if(l < element && heap[l] < heap[i])
    smallest = l;
  if(r < element && heap[r] < smallest)
    smallest = r;
  if(smallest != i) {
    swap(heap[i], heap[smallest]);
    MinHeapify(smallest);
  }
}

int main() {
  MinHeap h(11);

  h.insert(3);
  h.insert(2);
  h.deleteKey(1);
  h.insert(15);
  h.insert(5);
  h.insert(4);
  h.insert(45);

  h.extractMin();
  cout << h.getMin() << " ";
  h.decreaseKey(2, 1);
  cout << h.getMin();

  return 0;
}
