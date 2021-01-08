#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BinaryTree {
private:
  int size;
  vector<char> tree;

  // element access functions
  int getLeftchild(int index);    // for treversal functions
  int getRightchild(int index);   // for treversal functions

  // treversal functions
  void preorder(int index);
  void inorder(int index);
  void postorder(int index);

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
  void inorder();
  void postorder();

  void insert(char data);
};

// element access function implementations
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

// treversal function implementations
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

void BinaryTree::inorder() {
  inorder(1);
  cout << endl;
}

void BinaryTree::inorder(int curr) {
  if(curr > 0 && tree[curr] != '-') {
    inorder(getLeftchild(curr));
    cout << tree[curr] << " ";
    inorder(getRightchild(curr));
  }
}

void BinaryTree::postorder() {
  postorder(1);
  cout << endl;
}

void BinaryTree::postorder(int curr) {
  if(curr > 0 && tree[curr] != '-') {
    postorder(getLeftchild(curr));
    postorder(getRightchild(curr));
    cout << tree[curr] << " ";
  }
}

int main() {
  string s = "-DAFEBRTGQ--V-JL";
  BinaryTree T(s);

  //T.levelOrder();
  T.preorder();
  T.inorder();
  T.postorder();

  return 0;
}
