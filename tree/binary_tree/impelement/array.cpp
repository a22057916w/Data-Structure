#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int size;
  vector<char> tree;

public:
  BinaryTree(): size(0) {);

  // levelOrderConsturctor
  BinaryTree(const string str) {
    for(auto c : str) {
      tree.push_back(c);
      size++;
    }
  }

  void insert(char data);
};

int main() {
  return 0;
}
