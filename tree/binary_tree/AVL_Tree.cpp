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
#include <queue>
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

  // element access
  TreeNode *getSuccessor(TreeNode *node);

  // modifying functions
  TreeNode *insert(TreeNode *root, int key);
  TreeNode *deleteNode(TreeNode *root, int key);
  TreeNode *leftRotation(TreeNode *curr);
  TreeNode *rightRotation(TreeNode *curr);

  // capacity functions
  int getHeight(TreeNode *curr);
  int getBalance(TreeNode *curr);

  // traversal function
  void inorder(TreeNode *curr);
  void preorder(TreeNode *curr);

public:
  AVL_TREE(): root(0) {};

  // modifying functions
  void insert(int key);
  void deleteNode(int key);

  // traversal function
  void inorder();
  void preorder();
  void levelorder();

};

// *************** implementation of element access function ****************
TreeNode *AVL_TREE::getSuccessor(TreeNode *node) {
  TreeNode *curr = node;
  while(curr && curr->left)
    curr = curr->left;
  return curr;
}

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

/*
Algorithm (Deletetion)
1. Perform the normal BST deletion.
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
void AVL_TREE::deleteNode(int key) {
  root = deleteNode(root, key);
}

TreeNode *AVL_TREE::deleteNode(TreeNode *root, int key) {

  // Step 1. Perform the normal BST insertion.
  if(root == NULL)
    return root;
  if(key < root->key)
    root->left = deleteNode(root->left, key);
  else if(key > root->key)
    root->right = deleteNode(root->right, key);
  else {

    // Case 1 & Case 2 : node with only one child or no child
    if(root->left == NULL) {
      TreeNode *temp  = root->right;
      root = NULL;
      delete root;
      return temp;
    }
    else if(root->right == NULL) {
      TreeNode *temp  = root->left;
      root = NULL;
      delete root;
      return temp;
    }

    // Case 3: node with two children. Get the inorder successor (smallest in
    // the right subtree)
    else {
      TreeNode *temp = getSuccessor(root->right);

      // Copy the inorder successor's content to this node
      root->key = temp->key;

      // Delete the inorder successor
      root->right = deleteNode(root->right, temp->key);
    }
  }

  // If the tree had only one node , then return
  if(root == NULL)
    return NULL;

  // Step 2. Update height of this ancestor node
  root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

  // Step 3. Get the balance factor of this ancestor node to check whether this
  //         node became unbalanced
  int balance = getBalance(root);

  // If this node becomes unbalanced, then
  // there are 4 cases
  if(balance > 1) {
    if(getBalance(root->left) >= 0)   {     // Case LL
      return rightRotation(root);
    }
    else {                          // Case LR
      root->left = leftRotation(root->left);
      return rightRotation(root);
    }
  }
  else if(balance < -1) {           // Case RR
    if(getBalance(root->right) <= 0)
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

// The tree must satisfy key(x) < key(y) either before or after the
// rotation take place, rotating subtree rooted with y
TreeNode *AVL_TREE::rightRotation(TreeNode *y) {
  TreeNode *x = y->left;
  TreeNode *T2 = x->right;     // right subtree of x

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  // Return new root
  return x;
}

// The tree must satisfy key(x) < key(y) either before or after the
// rotation take place, subtree rooted with x
TreeNode *AVL_TREE::leftRotation(TreeNode *x) {
  TreeNode *y = x->right;
  TreeNode *T2 = y->left;    // left subtree of y

  y->left = x;
  x->right = T2;

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
    cout << curr->key << " ";
    inorder(curr->right);
  }
}

void AVL_TREE::preorder() {
  preorder(root);
}

void AVL_TREE::preorder(TreeNode *curr) {
  if(curr) {
    cout << curr->key << " ";
    preorder(curr->left);
    preorder(curr->right);
  }
}

void AVL_TREE::levelorder() {
  queue<TreeNode*> q;
  q.push(root);

  while(!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();

    cout << curr->key << " ";

    if(curr->left)
      q.push(curr->left);
    if(curr->right)
      q.push(curr->right);
  }
}

int main() {

  AVL_TREE avl;

  avl.insert(9);
  avl.insert(5);
  avl.insert(10);
  avl.insert(0);
  avl.insert(6);
  avl.insert(11);
  avl.insert(-1);
  avl.insert(1);
  avl.insert(2);

  avl.preorder();
  cout << "\n";
  avl.levelorder();
  cout << endl;

  avl.deleteNode(10);
  avl.preorder();
  cout << "\n";
  avl.levelorder();

  return 0;
}

/*
Reference:
  https://hackmd.io/@Zero871015/rJksqh83X?type=view
  https://hackmd.io/@Zero871015/rJksqh83X?type=view
  https://hackmd.io/@Zero871015/rJksqh83X?type=view
*/
