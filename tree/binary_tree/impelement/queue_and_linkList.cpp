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

  // modifying functions
  void deleteDeepest(TreeNode *delNode);        // for deleteKey() in public
  void copy(TreeNode *curr, TreeNode *newNode); // for copy() in public
  void swap(TreeNode *curr);                    // for swap() in public
  bool equal(TreeNode *sor, TreeNode *tar)

  // capacity functions
  int getDepth(TreeNode *curr);           // return the height of the tree
  int getLeaf(TreeNode *curr);            // return the number of the leaf

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
  void deleteKey(char key);
  void swap();
  bool equal(TreeNode *target);
  BinaryTree copy();

  // capacity functions
  int getSize();            // return the nodes of the tree
  int getDepth();           // return the height of the tree
  int getLeaf();            // return the number of the leaf

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

void BinaryTree::deleteKey(char key) {
  // The idea is, starting at root, find the deepest and rightmost node in
  // binary tree and the node which we want to delete. And replace the deepest
  // rightmost node’s data with node to be deleted.
  // Then delete the deepest rightmost node.

  // check special case for root
  if(root == NULL)
    return;
  if(root->leftchild == NULL && root->rightchild == NULL && root->data == key)
    root = NULL;

  // using queue to record the nodes in level order
  // that is, in complete binary tree rules
  queue<TreeNode *> q;
  q.push(root);

  TreeNode *curr;       // iterating to the deepest leaf
  TreeNode *keyNode;    // to find the target node

  while(!q.empty()) {
    curr = q.front();
    q.pop();

    if(curr->data == key)
      keyNode = curr;

    if(curr->leftchild != NULL)
      q.push(curr->leftchild);
    if(curr->rightchild != NULL)
      q.push(curr->rightchild);
  }

  if(keyNode != NULL) {
    char data = curr->data;
    deleteDeepest(curr);
    keyNode->data = data;
  }
}

void BinaryTree::deleteDeepest(TreeNode *delNode) {

  // There would be no condition where father == NULL
  // since we chech the situation in the caller function.
  TreeNode *father = delNode->parent;

  if(father->rightchild == delNode)
    father->rightchild = NULL;
  else
    father->leftchild = NULL;

  delNode = NULL;
  delete delNode;
}

void BinaryTree::swap() {
  if(root == NULL)
    return;
  else
    swap(root);
}

void BinaryTree::swap(TreeNode *curr) {
  // The task is to swap sibling nodes of every level except the root.
  // We start with bottom-up by recursion

  if(curr) {
    swap(curr->leftchild);
    swap(curr->rightchild);

    TreeNode *temp = curr->leftchild;
    curr->leftchild = curr->rightchild;
    curr->rightchild = temp;
  }
}

bool BinaryTree::equal(TreeNode *target) {
  return equal(root, target);
}

bool BinaryTree::equal(TreeNode *s, TreeNode *t) {
  if(s == NULL && t == NULL)
    return true;
  else if(s != NULL && t != NULL) {
    if(s->data != t->data)
      return false;
    else if(equal(s->leftchild, t->leftchild))
      return equal(s->rightchild, t->rightchild);
    else
      return false;
  }
}

BinaryTree BinaryTree::copy() {
  // using recursion to copy left subtree and right subtree

  BinaryTree mir(new TreeNode());

  if(root == NULL)
    return mir;
  else
    copy(root, mir.root);

  return mir;
}

void BinaryTree::copy(TreeNode *curr, TreeNode *newNode) {
  if(curr == NULL)
    return;
  else {
    newNode->data = curr->data;
    if(curr->leftchild) {
      newNode->leftchild = new TreeNode();
      newNode->leftchild->parent = newNode;
    }
    if(curr->rightchild) {
      newNode->rightchild = new TreeNode();
      newNode->rightchild->parent = newNode;
    }

    copy(curr->leftchild, newNode->leftchild);
    copy(curr->rightchild, newNode->rightchild);
  }
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
  // the idea is find the maxinum between left subtree and right subtree,
  // then plus the root itself

  if(curr == NULL)
    return 0;
  return max(getDepth(curr->leftchild), getDepth(curr->rightchild)) + 1;
}

int BinaryTree::getLeaf() {
  return getLeaf(root);
}

int BinaryTree::getLeaf(TreeNode *curr) {
  // The idea is, if node is NULL then return 0.
  // Else if left and right child nodes are NULL return 1.
  // Else recursively calculate Leaf count of left subtree + Leaf count of right

  if(curr == NULL)
    return 0;

  if(curr->leftchild == NULL && curr->rightchild == NULL)
    return 1;
  else
    return getLeaf(curr->leftchild) + getLeaf(curr->rightchild);
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
  cout << T.getLeaf() << endl;

  T.deleteKey('L');
  T.inorder();

  T.swap();
  T.inorder();
  T.preorder();
  T.swap();

  BinaryTree TM = T.copy();
  TM.inorder();

  TM.deleteKey('A');
  TM.inorder();

  return 0;
}
