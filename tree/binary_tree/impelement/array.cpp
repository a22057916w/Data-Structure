#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int size;
  vector<char> tree;

  // element access function
  char getLeftchild(int index);
  char getRightchild(int index);

  void preorder(int index);

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
  void preorder();

  void insert(char data);
};

// element access function implmentations
char BinaryTree::getLeftchild(int index) {
  if(tree[index])
}

char BinaryTree::getRightchild(int index) {

}

void BinaryTree::levelOrder() {
  for(auto c : tree)
    cout << c << " ";
  cout << endl;
}

void BinaryTree::preorder() {

}

void BinaryTree::preorder() {

}

int main() {
  string s = "-DAFEBRTGQ--V-JL";
  BinaryTree T(s);

  T.levelOrder();

  return 0;
}
