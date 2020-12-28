#include <iostream>
#include <string>
using namespace std;

class BinaryTree;
class TreeNode {
private:
  string s;
  TreeNode *parent;
  TreeNode *leftchild, *rightchild;
public:
  TreeNode(): parent(0), leftchild(0), rightchild(0), s("") {};
  TreeNode(string str): parent(0), leftchild(0), rightchild(0), s(str) {};

  friend class TreeNode;
};

class BinaryTree {
private:
  TreeNode *root;
public:
  BinaryTree(): root(0) {};
  BinaryTree(TreeNode *node): root(node) {};

  // traversal functions
  void preorder();
  void inorder();
  void postorder();
  void levelorder();
};

void BinaryTree::preorder() {
  TreeNode *curr = root;
  if(curr) {
    cout << curr->s << " ";
    preorder(curr->leftchild);
    preorder(curr->rightchild);
  }
}

void BinaryTree::inorder() {
  TreeNode *curr = root;
  if(curr) {
    preorder(curr->leftchild);
    cout << curr->s << " ";
    preorder(curr->rightchild);
  }
}

void BinaryTree::postorder() {
  TreeNode *curr = root;
  if(curr) {
    preorder(curr->leftchild);
    preorder(curr->rightchild);
    cout << curr->s << " ";
  }
}




int main() {
  return 0;
}
