#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

class BinaryTree;
class TreeNode {
private:
  char data;
  TreeNode *parent;
  TreeNode *leftchild, *rightchild;
public:

  TreeNode(): parent(0), leftchild(0), rightchild(0), data('') {};
  TreeNode(char c): parent(0), leftchild(0), rightchild(0), data(c) {};

  friend class BinaryTree;
};

class BinaryTree {
private:
  TreeNode *root;

  // traversal functions
  void preorder(TreeNode *curr);
  void inorder(TreeNode *curr);
  void postorder(TreeNode *curr);
  void levelorder(TreeNode *curr);

public:
  BinaryTree(): root(0) {};
  BinaryTree(TreeNode *node): root(node) {};

  // traversal functions
  void preorder();
  void inorder();
  void postorder();
  void levelorder();
};

// traversal functions
void BinaryTree::preorder() {
  preorder(root);
  cout << "\n";
}

void BinaryTree::preorder(TreeNode *curr) {
  if(curr) {
    cout << curr->data << " ";
    preorder(curr->leftchild);
    preorder(curr->rightchild);
  }
}

void BinaryTree::inorder() {
  inorder(root);
  cout << "\n";
}

void BinaryTree::inorder(TreeNode *curr) {
  if(curr) {
    preorder(curr->leftchild);
    cout << curr->data << " ";
    preorder(curr->rightchild);
  }
}

void BinaryTree::postorder() {
  inorder(root);
  cout << "\n";
}

void BinaryTree::postorder(TreeNode *curr) {
  if(curr) {
    preorder(curr->leftchild);
    preorder(curr->rightchild);
    cout << curr->data << " ";
  }
}

void BinaryTree::levelorder() {
  queue<TreeNode *> q;
  q.push(root);

  while(!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();
    cout << curr->data << " ";

    if(curr->leftchild != NULL)
      q.push(curr->leftchild);
    if(curr->rightchild != NULL)
      q.push(curr->rightchild);
  }
}


int main() {
  const char *a = "A B C D E F x x x G H x I";
  BinaryTree T(a);                // 以level-order規則建立Binary Tree
  T.inorder();      // 以inorder-traversal印出Binary Tree

  T.insertLevelorder('K');
  T.insertLevelorder('L');
  T.insertLevelorder('M');
  T.insertLevelorder('N');
  T.inorder();

  return 0;
}
