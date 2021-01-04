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

  TreeNode(): parent(0), leftchild(0), rightchild(0), data('x') {};
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

  // consturctor fucntions
  void levelOrderConsturct(stringstream &ss);

  // capacity functions
  int getDepth(TreeNode *curr);           // return the height of the tree

public:
  BinaryTree(): root(0) {};
  BinaryTree(TreeNode *node): root(node) {};
  BinaryTree(const char* str) {
    stringstream ss;
    ss << str;

    root = new TreeNode();    // allocate memory for root
    ss >> root->data;         // assign the firt character to root

    levelOrderConsturct(ss);
  }

  // traversal functions
  void preorder();
  void inorder();
  void postorder();
  void levelorder();

  // modifying functions
  void insertLevelorder(char data);
  void deleteDeepset();
  void deleteKey();

  // capacity functions
  int getSize();            // return the nodes of the tree
  int getDepth();           // return the height of the tree

};

// consturctor functions implmentations
void BinaryTree::levelOrderConsturct(stringstream &ss) {

  // using queue to record the nodes in level order
  // that is, in complete binary tree rules
  queue<TreeNode *> q;
  TreeNode *curr = root;
  char data = 'x';

  while(ss >> data) {
    if(data != 'x') {
      TreeNode *newNode = new TreeNode(data);
      newNode->parent = curr;
      curr->leftchild = newNode;
      q.push(newNode);
    }
    if(!(ss >> data))
      break;
    if(data != 'x') {
        TreeNode *newNode = new TreeNode(data);
        newNode->parent = curr;
        curr->rightchild = newNode;
        q.push(newNode);
    }
    curr = q.front();
    q.pop();
  }
}

// traversal functions implmentations
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
    inorder(curr->leftchild);
    cout << curr->data << " ";
    inorder(curr->rightchild);
  }
}

void BinaryTree::postorder() {
  postorder(root);
  cout << "\n";
}

void BinaryTree::postorder(TreeNode *curr) {
  if(curr) {
    postorder(curr->leftchild);
    postorder(curr->rightchild);
    cout << curr->data << " ";
  }
}

void BinaryTree::levelorder() {

  // using queue to record the nodes in level order
  // that is, in complete binary tree rules
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

// modifying functions implmentations
void BinaryTree::insertLevelorder(char data) {

  // using queue to record the nodes in level order
  // that is, in complete binary tree rules
  queue<TreeNode *> q;
  TreeNode *curr = root;

  while(curr) {
    if(curr->leftchild != NULL)
      q.push(curr->leftchild);
    else {
      TreeNode *newNode = new TreeNode(data);
      newNode->parent = curr;
      curr->leftchild = newNode;
      break;
    }

    if(curr->rightchild != NULL)
      q.push(curr->rightchild);
    else {
      TreeNode *newNode = new TreeNode(data);
      newNode->parent = curr;
      curr->rightchild = newNode;
      break;
    }
    curr = q.front();
    q.pop();
  }
}

void BinaryTree::deleteDeepset() {

}

void BinaryTree::deleteKey() {
  
}

// capacity functions implmentations
int BinaryTree::getSize() {

  // using queue to record the nodes in level order
  // that is, in complete binary tree rules
  queue<TreeNode *> q;
  q.push(root);

  int count = 0;
  while(!q.empty()) {
    count++;

    TreeNode *curr = q.front();
    q.pop();

    if(curr->leftchild != NULL)
      q.push(curr->leftchild);
    if(curr->rightchild != NULL)
      q.push(curr->rightchild);
  }
  return count;
}

int BinaryTree::getDepth() {
  return getDepth(root);
}

int BinaryTree::getDepth(TreeNode *curr) {
  // the idea is find the maxinum between left subtree and right subtree
  // ,then plus the root itself

  if(curr == NULL)
    return 0;
  return max(getDepth(curr->leftchild), getDepth(curr->rightchild)) + 1;
}


int main() {
  const char *a = "A B C D E F x x x G H x I";
  BinaryTree T(a);
  T.inorder();

  T.insertLevelorder('K');
  T.insertLevelorder('L');
  T.insertLevelorder('M');
  T.insertLevelorder('N');
  T.inorder();

  cout << T.getSize() << endl;
  cout << T.getDepth() << endl;

  return 0;
}
