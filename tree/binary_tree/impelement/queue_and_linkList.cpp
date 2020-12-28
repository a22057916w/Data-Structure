#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BinaryTree;
class TreeNode {
/*private:
  string str;
  TreeNode *parent;
  TreeNode *leftchild, *rightchild;*/
public:
  string str;
  TreeNode *parent;
  TreeNode *leftchild, *rightchild;

  TreeNode(): parent(0), leftchild(0), rightchild(0), str("") {};
  TreeNode(string s): parent(0), leftchild(0), rightchild(0), str(s) {};

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
    cout << curr->str << " ";
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
    cout << curr->str << " ";
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
    cout << curr->str << " ";
  }
}

void BinaryTree::levelorder() {
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
  // TreeNode instantiation
    TreeNode *nodeA = new TreeNode("A"); TreeNode *nodeB = new TreeNode("B");
    TreeNode *nodeC = new TreeNode("C"); TreeNode *nodeD = new TreeNode("D");
    TreeNode *nodeE = new TreeNode("E"); TreeNode *nodeF = new TreeNode("F");
    TreeNode *nodeG = new TreeNode("G"); TreeNode *nodeH = new TreeNode("H");
    TreeNode *nodeI = new TreeNode("I");

    // construct the Binary Tree
    nodeA->leftchild = nodeB; nodeA->rightchild = nodeC;
    nodeB->leftchild = nodeD; nodeB->rightchild = nodeE;
    nodeE->leftchild = nodeG; nodeE->rightchild = nodeH;
    nodeC->leftchild = nodeF; nodeF->rightchild = nodeI;

    BinaryTree T(nodeA);

    T.preorder();
    cout << endl;
    T.inorder();
    cout << endl;
    T.postorder();
    cout << endl;
    T.levelorder();
    cout << endl;
  return 0;
}
