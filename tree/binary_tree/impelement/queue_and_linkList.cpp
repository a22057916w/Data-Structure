#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BinaryTree;
class TreeNode {
private:
  string str;
  TreeNode *parent;
  TreeNode *leftchild, *rightchild;
public:
  TreeNode(): parent(0), leftchild(0), rightchild(0), s("") {};
  TreeNode(string s): parent(0), leftchild(0), rightchild(0), str(s) {};

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

// traversal functions
void BinaryTree::preorder() {
  TreeNode *curr = root;
  if(curr) {
    cout << curr->str << " ";
    preorder(curr->leftchild);
    preorder(curr->rightchild);
  }
}

void BinaryTree::inorder() {
  TreeNode *curr = root;
  if(curr) {
    preorder(curr->leftchild);
    cout << curr->str << " ";
    preorder(curr->rightchild);
  }
}

void BinaryTree::postorder() {
  TreeNode *curr = root;
  if(curr) {
    preorder(curr->leftchild);
    preorder(curr->rightchild);
    cout << curr->str << " ";
  }
}

void binaryTree::levelorder() {
  queue<TreeNode *> q;
  q.push(root);

  while(!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();
    cout << curr->str << " ";

    if(curr->leftchild != NULL)
      q.push(curr->leftchild);
    if(curr->rightchild != NULL)
      q.push(curr->rightchild);
  }
}


int main() {
  return 0;
}
