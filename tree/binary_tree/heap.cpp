#include <iostream>
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
}

int main() {
  return 0;
}
