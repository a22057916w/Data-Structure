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

public:
  AVL_TREE(): root(0);

  // modifying functions
  void insert(int key);
};

// ***************** Implementation of modifying functions ******************
/*
Concept (Insertion)
1. Perform the normal BST insertion.
2. Check the operation is vailed for the restrictions of AVL from bottom to up.
3. If the tree is balanced, end of the insertion.
4. Else, do the rotation(LL, LR, RR, RL) to make it balanced.
*/
void insert(int key) {
  root = insert(root, key);
}

TreeNode *insert(TreeNode *root, int key) {

}

int main() {
  return 0;
}
