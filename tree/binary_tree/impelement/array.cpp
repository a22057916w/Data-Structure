#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int size;
  vector<char> tree;

  // element access functions
  int getLeftchild(int index);
  int getRightchild(int index);

  // treversal functions
  void preorder(int index);

public:
  BinaryTree(): size(0) {};

  // levelOrderConsturctor, root start with 1
  BinaryTree(const string str) {
    for(auto c : str) {
      tree.push_back(c);
      size++;
    }
  }

  // treversal functions
  void levelOrder();
  void preorder();

  void insert(char data);
};

// element access function implmentations
int BinaryTree::getLeftchild(int index) {
  if(tree[index] != '-' && (index * 2) < size)
    return index * 2 ;
  else
    return -1;
}

int BinaryTree::getRightchild(int index) {
  if(tree[index] != '-' && (index * 2 + 1) < size)
    return index * 2 + 1;
  else
    return -1;
}

void BinaryTree::levelOrder() {
  for(auto c : tree)
    cout << c << " ";
  cout << endl;
}

void BinaryTree::preorder() {
  preorder(1);
  cout << endl;
}

void BinaryTree::preorder(int curr) {
  if(curr > 0 && tree[curr] != '-') {
    cout << tree[curr] << " ";
    preorder(getLeftchild(curr));
    preorder(getRightchild(curr));
  }
}

int main() {
  string s = "-DAFEBRTGQ--V-JL";
  BinaryTree T(s);

  //T.levelOrder();
  T.preorder();

  return 0;
}
