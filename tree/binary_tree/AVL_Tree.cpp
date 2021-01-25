/*
AVL Tree
AVL tree is a self-balancing Binary Search Tree (BST) where the difference
between heights of left and right subtrees cannot be more than one for all nodes.

Rotattion
Tree rotation is an operation that changes the structure without interfering
with the order of the elements on an AVL tree. It moves one node up in the tree
and one node down. It is used to change the shape of the tree, and to decrease
its height by ""moving smaller subtrees down and larger subtrees up,"" resulting
in improved performance of many tree operations. The direction of a rotation
depends on the side which the tree nodes are shifted upon whilst others say that
it depends on which ""child takes the root’s place.""
This is a C++ Program to Implement AVL Tree.
*/

#include <iostream>
#include <algorithm>
using namespace std;

class AVL_TREE;
class TreeNode {
private:
  TreeNode *left, *right;
  int key;
  int height;
public:
  TreeNode(): left(0), right(0), key(0), height(-1) {};
  TreeNode(int key): left(0), right(0), key(key), height(1) {};

  friend class AVL_TREE;
};

class AVL_TREE {
private:
  TreeNode *root;

  // modifying functions
  TreeNode *insert(TreeNode *root, int key);
  TreeNode *leftRotation(TreeNode *curr);
  TreeNode *rightRotation(TreeNode *curr);

  // capacity functions
  int getHeight(TreeNode *curr);
  int getBalance(TreeNode *curr);

  // traversal function
  void inorder(TreeNode *curr);

public:
  AVL_TREE(): root(0) {};

  // modifying functions
  void insert(int key);

  // traversal function
  void inorder();
  void levelorder();

};

// ***************** Implementation of modifying functions ******************
/*
Concept (Insertion)
1. Perform the normal BST insertion.
2. Check the operation is vailed for the restrictions of AVL from bottom to up.
3. If the tree is balanced, end of the insertion.
4. Else, do the rotation(LL, LR, RR, RL) to make it balanced.

Algorithm (Insertion)
1. Perform the normal BST insertion.
2. The current node must be one of the ancestors of the newly inserted node.
   Update the height of the current node.
3. Get the balance factor (left subtree height – right subtree height) of the
   current node.
4. If balance factor is greater than 1, then the current node is unbalanced and
   we are either in LL case or LR case. To check whether it is LL case or not,
   compare the newly inserted key with the key in left subtree root.
5. If balance factor is less than -1, then the current node is unbalanced and we
   are either in RR case or RL case. To check whether it is RR case or not,
   compare the newly inserted key with the key in right subtree root.
*/
void AVL_TREE::insert(int key) {
  root = insert(root, key);
}

TreeNode *AVL_TREE::insert(TreeNode *root, int key) {

  // Step 1. Perform the normal BST insertion.
  if(root == NULL)
    return new TreeNode(key);
  if(key < root->key)
    root->left = insert(root->left, key);
  else if(key > root->key)
    root->right = insert(root->right, key);
  else          // Assume the duplication is not allowed in BST
    return root;

  // Step 2. Update height of this ancestor node
  root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

  // Step 3. Get the balance factor of this ancestor node to check whether this
  //         node became unbalanced
  int balance = getBalance(root);

  // If this node becomes unbalanced, then
  // there are 4 cases
  if(balance > 1) {
    if(key < root->left->key)       // Case LL
      return rightRotation(root);
    else {                          // Case LR
      root->left = leftRotation(root->left);
      return rightRotation(root);
    }
  }
  else if(balance < -1) {           // Case RR
    if(key > root->right->key)
      return leftRotation(root);
    else {                          // Case RL
      root->right = rightRotation(root->right);
      return leftRotation(root);
    }
  }
  // return the (unchanged) node pointer
  else
    return root;
}

// The tree must satisfy key(y) < key(z) < key(x) either before or after the
// rotation take place
TreeNode *AVL_TREE::rightRotation(TreeNode *x) {
  TreeNode *y = x->left;
  TreeNode *z = y->right;     // z for T2(right subtree of y)

  // Perform rotation
  y->right = x;
  x->left = z;

  // Update heights
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  // Return new root
  return y;
}

// The tree must satisfy key(x) < key(z) < key(y) either before or after the
// rotation take place
TreeNode *AVL_TREE::leftRotation(TreeNode *y) {
  TreeNode *x = y->right;
  TreeNode *z = x->left;    // z for T2(left subtree of x)

  y->left = x;
  x->right = z;

  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

// ****************** implementation of capacity functions *******************
int AVL_TREE::getHeight(TreeNode *curr) {
  if(curr == NULL)
    return 0;

  // we update the heigh of node for every insertions, so we just return the var
  return curr->height;
}

int AVL_TREE::getBalance(TreeNode *curr) {
  if(curr == NULL)
    return 0;
  return getHeight(curr->left) - getHeight(curr->right);
}

// ***************** implementation of traversal functions *******************
void AVL_TREE::inorder() {
  inorder(root);
}

void AVL_TREE::inorder(TreeNode *curr) {
  if(curr) {
    inorder(curr->left);
    cout << curr->element << "(" << curr->key << ") ";
    inorder(curr->right);
  }
}

void AVL_TREE::levelorder() {
  queue<TreeNode*> q;
  q.push(root);

  while(!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();

    cout << curr->element << "(" << curr->key << ") ";

    if(curr->left)
      q.push(curr->left);
    if(curr->right)
      q.push(curr->right);
  }
}

int main() {

  AVL_TREE avl;

  avl.insert(13);
  avl.insert(10);
  avl.insert(15);
  avl.insert(5);
  avl.insert(11);
  avl.insert(4);
  avl.insert(8);
  avl.insert(16);
  avi.inorder();
  cout << endl;

  return 0;
}
