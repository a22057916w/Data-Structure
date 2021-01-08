#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BinaryTree {
private:
  int size, node;
  vector<char> tree;

  // element access functions
  int getLeftchild(int index);
  int getRightchild(int index);

  // treversal functions
  void preorder(int index);
  void inorder(int index);
  void postorder(int index);

  // capacity function
  int getDepth(int index);

public:
  BinaryTree(): size(0) {};

  // levelOrderConsturctor, root start with 1
  BinaryTree(const string str): size(0), node(0) {
    for(auto c : str) {

      // record the amount of leaf
      if(c != '-')
        node++;

      // store the array by vector and record the size of that
      tree.push_back(c);
      size++;
    }
  }

  // treversal functions
  void levelOrder();
  void preorder();
  void inorder();
  void postorder();

  // modifying functions
  void insertLevelorder(char data);

  // capacity functions
  int getCapacity();
  int getDepth();
  int getLeaf();

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
  for(auto c : tree) {
    if(c == '-')
      continue;
    cout << c << " ";
  }
  cout << "\n";
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


// modifying function implementations
void BinaryTree::insertLevelorder(char data) {
  int i = 1;
  while(tree[i++] != '-' && i < size);
  i--;

  if(i < size)
    tree[i] = data;
  else {
    tree.push_back(data);
    size++;
  }
  node++;
}

// capacity function implementations
int BinaryTree::getCapacity() {
  return size;
}

int BinaryTree::getDepth() {
  return getDepth(1);
}

int BinaryTree::getDepth(int curr) {
  if(curr > 0)
    return max(getDepth(getLeftchild(curr)), getDepth(getRightchild(curr))) + 1;
  else
    return 0;
}

int BinaryTree::getLeaf() {
  return node;
}



int main() {
  string s = "-DAFEBRTGQ--V-JL";
  BinaryTree T(s);

  T.levelOrder();
  T.preorder();
  T.inorder();
  T.postorder();

  cout << T.getCapacity() << endl;
  cout << T.getDepth() << endl;
  cout << T.getLeaf() << endl;

  T.insertLevelorder('X');
  T.levelOrder();
  T.preorder();

  return 0;
}
