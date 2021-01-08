#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int size;
  vector<char> tree;

public:
  BinaryTree(): size(0) {};

  // levelOrderConsturctor
  BinaryTree(const string str) {
    for(auto c : str) {
      tree.push_back(c);
      size++;
    }
  }

  // treversal function
  void levelOrder();

  void insert(char data);
};

void BinaryTree::levelOrder() {
  for(auto c : tree)
    cout << c << " ";
  cout << endl;
}

int main() {
  string s = "ABCDEFGHI";
  BinaryTree T(s);

  T.levelOrder();

  return 0;
}
