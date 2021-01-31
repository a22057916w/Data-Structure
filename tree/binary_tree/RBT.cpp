/*
Rules That Every Red-Black Tree Follows:
1. Every node has a colour either red or black.
2. The root of tree is always black.
3. There are no two adjacent red nodes (A red node cannot have a red parent or
   red child).
4. Every path from a node (including root) to any of its descendant NULL node
   has the same number of black nodes.
*/

#include <iostream>
using namespace std;

// each element in the enum would be assign a value according to the order
enum Color {RED, BLACK};

class RBT;
class TreeNode {
private:
    TreeNode *left, *right;
    TreeNode *parent;
    int key;
    bool color;      // 0: Red, 1: Black

public:
  TreeNode(int key) {
    left = right = parent = NULL;
    this->key = key;
    color = RED;
  }

    friend class RBT;
};

class RBT {
private:
  TreeNode *root;

  // modifying functions
  TreeNode *insert(TreeNode *root, TreeNode *newNode);
  TreeNode *leftRotation(TreeNode *curr);
  TreeNode *rightRotation(TreeNode *curr);
  void fixInsertion(TreeNode *curr);

  // traversal function
  void inorder(TreeNode *curr);

public:
  RBT(): root(0) {}

  // modifying functions
  void insert(int key);

  // traversal function
  void inorder();
  void levelorder();
};

// **************** implementation of modifying functions ********************
/*
Algorithm (Insertion)
Let x be the newly inserted node.

1. Perform standard BST insertion and make the colour of newly inserted nodes as RED.
2. If x is the root, change the colour of x as BLACK (Black height of complete
   tree increases by 1).
3. Do the following if the color of x’s parent is not BLACK and x is not the root.
   a) If x’s uncle is RED (Grandparent must have been black from property 4)
     (i) Change the colour of parent and uncle as BLACK.
     (ii) Colour of a grandparent as RED.
     (iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
    b) If x’s uncle is BLACK, then there can be four configurations for x,
       x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)
      (i) Left Left Case (p is left child of g and x is left child of p)
      (ii) Left Right Case (p is left child of g and x is the right child of p)
      (iii) Right Right Case (Mirror of case i)
      (iv) Right Left Case (Mirror of case ii)
*/
void RBT::insert(int key) {
  TreeNode *newNode = new TreeNode(int key);

  // Step 1. Perform the normal BST insertion.
  root = insert(root, key);

  // Step 2 & 3
  FixInsertion(newNode);
}

TreeNode* RBT::insert(TreeNode *root, TreeNode *newNode) {

  // Step 1. Perform the normal BST insertion.
  if(root == NULL)
    return newNode;
  if(newNode->key < root->key) {
    root->left = insert(root->left, newNode);
    root->left->parent = root;
  }
  if(newNode->key > root->key) {
    root->right = insert(root->right, newNode);
    root->right->parent = root;
  }
  else            // Assume the duplication is not allowed in BST
    return root;
}

void RBT::FixInsertion(TreeNode *curr) {

  // Case 0: if root is black, there is nothing to fix
  while(curr->parent->color == RED && curr != root) {
    TreeNode *parent = curr->parent;
    TreeNode *gand_parent = curr->parent->parent;

    // Case A: Parent of pt is left child of Grand-parent of pt
    if(parent == grand_parent->left) {
      TreeNode *uncle = grand_parent->right;

      // Case 1: The uncle of pt is also red Only Recoloring required
      if(uncle->color == RED) {
        grand_parent->color == RED;
        parent->color == BLACK;
        uncle->color == BLACK;
        curr = grand_parent;
      }
      else {

        // Case LL: pt is left child of its parent, Right-rotation required
        if(curr == parent->left) {
          
        }
      }
    }
  }

  // make sure the root is always black
  root->color = BLACK;
}

int main() {
  return 0;
}
