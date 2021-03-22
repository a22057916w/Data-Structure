#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
public:
    MinHeap() {};
    MinHeap(int size) {
      heap.resize(size);
    }

    int parent(int index);
    int left(int index);
    int right(int index);

    int extractMin();
    void decreaseKey(int index, int new_val);

    int getMin();

    void insert(int key);
    void deletKey(int index);
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

int main() {
  return 0;
}
