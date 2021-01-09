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
  BinaryTree(const vector<char> &tree, int size, int node) {
    this->size = size; this->node = node;

    for(auto c : tree)
      this->tree.push_back(c);
  }
  BinaryTree(): size(0) {};

  // treversal functions
  void levelorder();
  void preorder();
  void inorder();
  void postorder();

  // modifying functions
  void insertLevelorder(char data);
  void deleteKey(char key);
  void swap();
  bool equal(BinaryTree &src);
  BinaryTree copy();

  // capacity functions
  int getCapacity();      // return the size of the array(vector)
  int getDepth();         // return the height of the tree
  int getLeaf();          // return the number of nodes

};

// element access function implementations
int BinaryTree::getLeftchild(int index) {
  if(index * 2 < size)
    return index * 2 ;
  else
    return -1;
}

int BinaryTree::getRightchild(int index) {
  if(index * 2 + 1 < size)
    return index * 2 + 1;
  else
    return -1;
}


// treversal function implementations
void BinaryTree::levelorder() {
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
  while(tree[i++] != '-' && i < size);  // find the empty slot or new space
  i--;

  if(i < size)              // if the tree is not complete, set into empty slot
    tree[i] = data;
  else {                    // if the tree is full, new space
    tree.push_back(data);
    size++;
  }
  node++;
}

void BinaryTree::deleteKey(char key) {
  int keyIndex = 0;         // find the target node
  int lastIndex = 0;        // find the deepest leaf

  for(int i = 0; i < size; i++) {
    if(tree[i] != '-') {
      lastIndex = i;
        if(tree[i] == key)
          keyIndex = i;
    }
    else
      continue;
  }

  if(keyIndex > 0) {
    tree[keyIndex] = tree[lastIndex];
    tree[lastIndex] = '-';
    node--;
  }
}

void BinaryTree::swap() {

  // using the characteristic of the array
  // then using two pointer method to swap the content
  for(int i = 2, j = 3; i < size; i*=2, j=j*2+1 ) {
    int front = i, back = j;
    while(front < back) {
      char tmp = tree[front];
      tree[front++] = tree[back];
      tree[back--] = tmp;
    }
  }
}

bool equal(BinaryTree &src) {
  if(size != src->size || node != src->node)
    return false;

  for(int i = 0; i < size;; i++)
    if(tree[i] != src->tree[i])
      return false;      
  return true;
}

BinaryTree BinaryTree::copy() {
  return BinaryTree(tree, size, node);
}

// capacity function implementations
int BinaryTree::getCapacity() {
  return size;
}

int BinaryTree::getDepth() {
  return getDepth(1);
}

int BinaryTree::getDepth(int curr) {
  if(curr > 0 && tree[curr] != '-')
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

  T.levelorder();
  T.preorder();
  T.inorder();
  T.postorder();

  cout << T.getCapacity() << endl;
  cout << T.getDepth() << endl;
  cout << T.getLeaf() << endl;

  T.swap();
  T.levelorder();
  T.preorder();
  T.inorder();
  T.swap();

  T.insertLevelorder('X');
  T.levelorder();
  T.preorder();

  cout << "\n";

  T.deleteKey('F');
  T.levelorder();
  T.preorder();

  cout << "\n";

  BinaryTree TM = T.copy();
  TM.levelorder();
  TM.preorder();

  return 0;
}
