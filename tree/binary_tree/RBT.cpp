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
  void leftRotation(TreeNode *curr);
  void rightRotation(TreeNode *curr);
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

// The tree must satisfy key(x) < key(y) either before or after the
// rotation take place, subtree rooted with x
void RBT::leftRotation(TreeNode *x) {
  TreeNode *y = x->right;
  x->right = y->left;

  // if y's left child isn't NULL, link the parent and child
  if(y->left)
    y->left->parent = x;
  y->parent = x->parent;

  // if y is originaly root, make x the new root
  if(x->parent== NULL)
    root = y;
  else if(x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;

}

// The tree must satisfy key(x) < key(y) either before or after the
// rotation take place, rotating subtree rooted with y
void RBT::rightRotation(TreeNode *y) {
  TreeNode *x = y->left;
  y->left = x->right;

  // if x's right child isn't NULL, link the parent and child
  if(x->right)
    x->right->parent = y;
  x->parent = y->parent;

  // if y is originaly root, make x the new root
  if(y->parent== NULL)
    root = x;
  else if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  x->right = y;
  y->parent = x;
}

void RBT::FixInsertion(TreeNode *curr) {

  // Case 0: if root is black, there is nothing to fix
  while(curr->parent->color == RED && curr != root) {
    TreeNode *parent = curr->parent;
    TreeNode *gand_parent = curr->parent->parent;

    // Case A: Parent of curr is left child of Grand-parent of curr
    if(parent == grand_parent->left) {
      TreeNode *uncle = grand_parent->right;

      // Case 1: The uncle of curr is also red, only recoloring required
      if(uncle->color == RED) {
        grand_parent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        curr = grand_parent;
      }
      // Case 2: The uncle of curr is black, rotation required
      else {

        // Case LR: curr is right child of its parent, left-rotation required
        if(curr == parent->right) {
          curr = curr->parent;
          leftRotation(curr);
        }

        // Case LL: curr is left child of its parent, right-rotation required
        parent->color = BLACK;
        grand_parent->color = RED;
        rightRotation(grand_parent);
      }
    }
    // Case B: Parent of curr is right child of Grand-parent of curr
    else {
      TreeNode *uncle = grand_parent->left;

      // Case 1: The uncle of curr is also red, only recoloring required
      if(uncle->color == RED) {
        grand_parent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        curr = grand_parent;
      }
      // Case 2: The uncle of curr is black, rotation required
      else {

        // Case RL: curr is left child of its parent, right-rotation required
        if(curr == parent->right) {
          curr = curr->parent;
          rightRotation(curr);
        }

        // Case RR: curr is right child of its parent, left-rotation required
        parent->color = BLACK;
        grand_parent->color = RED;
        leftRotation(grand_parent);
      }
    }
  }

  // make sure the root is always black
  root->color = BLACK;
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
  return 0;
}
