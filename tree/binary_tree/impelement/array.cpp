#include <iostream>
#include <sstream>
using namespace std;

class BinaryTree {
private:
  int capacity;
  char *tree;

  void doubleCapacity();
public:
  BinaryTree(): capacity(10) {
      tree = new char[capacity];
  }
  BinaryTree(const char *str) {
    streamstring ss;
    ss << str;
  }

  void insert(char data);
};

int main() {
  return 0;
}
