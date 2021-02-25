/*
Rules That Every Red-Black Tree Follows:
1. Every node has a colour either red or black.
2. The root of tree is always black.
3. There are no two adjacent red nodes (A red node cannot have a red parent or
   red child).
4. Every path from a node (including root) to any of its descendant NULL node
   has the same number of black nodes.
*/

/*
REFERENCE:
https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
http://alrightchiu.github.io/SecondRound/red-black-tree-deleteshan-chu-zi-liao-yu-fixupxiu-zheng.html
*/

#include <iostream>
#include <algorithm>
#include <queue>
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

  // element access functions
  TreeNode *search(int key, TreeNode *root);      // called by FixDeletetion()
  TreeNode *getSuccessor(TreeNode *curr);         // called by FixDeletetion()
  bool hasRedChild(TreeNode *curr);               // called by FixDeletetion()

  // modifying functions
  TreeNode *insert(TreeNode *root, TreeNode *newNode);
  TreeNode *deleteNode(TreeNode *root, TreeNode *delNode);
  void leftRotation(TreeNode *curr);
  void rightRotation(TreeNode *curr);
  void FixInsertion(TreeNode *curr);
  void FixDeletion(TreeNode *curr);

  // traversal function
  void inorder(TreeNode *curr);

public:
  RBT(): root(0) {}

  // element access functions
  TreeNode *search(int key);      // called by DeleteRBT()

  // modifying functions
  void insert(int key);
  void deleteNode(int key);

  // traversal function
  void inorder();
  void levelorder();
};

// **************** implementation of element access function ***************
TreeNode *RBT::search(int key) {
  return search(key, root);
}

TreeNode *RBT::search(int key, TreeNode *root) {

  // Base Cases: root(curr node) is null or key is present at root(curr node)
  if(root == NULL || root->key == key)
    return root;

  // Key is smaller than root's key
  if(key < root->key)
    return search(key, root->left);

  // Key is greater than root's key
  else
    return search(key, root->right);
}

TreeNode *RBT::getSuccessor(TreeNode *curr) {
  while(curr && curr->left)
    curr = curr->left;
  return curr;
}

bool RBT::hasRedChild(TreeNode *curr) {
  TreeNode *left = curr->left;
  TreeNode *right = curr->right;

  return (left && left->color == RED) || (right && right->color == RED);
}

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
  TreeNode *newNode = new TreeNode(key);

  // Step 1. Perform the normal BST insertion.
  root = insert(root, newNode);

  // Step 2 & 3
  FixInsertion(newNode);
}

TreeNode* RBT::insert(TreeNode *root, TreeNode *newNode) {

  if(root == NULL)
    return newNode;

  if(newNode->key < root->key) {
    root->left = insert(root->left, newNode);
    root->left->parent = root;
  }
  // Assume the duplication is not allowed in BST
  else if(newNode->key > root->key) {
    root->right = insert(root->right, newNode);
    root->right->parent = root;
  }

  // return the (unchanged) node pointer
  return root;
}

void RBT::FixInsertion(TreeNode *curr) {

  // Case 0: if root is black, there is nothing to fix
  while(curr != root && curr->parent->color == RED) {
    TreeNode *parent = curr->parent;
    TreeNode *grand_parent = curr->parent->parent;

    // Case A: Parent of curr is left child of Grand-parent of curr
    if(parent == grand_parent->left) {
      TreeNode *uncle = grand_parent->right;

      // Case 1: The uncle of curr is also red, only recoloring required
      if(uncle && uncle->color == RED) {
        grand_parent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        curr = grand_parent;
      }
      // Case 2: The uncle of curr is black, rotation required
      else {

        // Case LR: curr is right child of its parent, left-rotation required
        if(curr == parent->right) {
          curr = parent;
          leftRotation(parent);
          parent = curr->parent;
        }

        // Case LL: curr is left child of its parent, right-rotation required
        swap(parent->color, grand_parent->color);
        rightRotation(grand_parent);
      }
    }
    // Case B: Parent of curr is right child of Grand-parent of curr
    else {
      TreeNode *uncle = grand_parent->left;

      // Case 1: The uncle of curr is also red, only recoloring required
      if(uncle && uncle->color == RED) {
        grand_parent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        curr = grand_parent;
      }
      // Case 2: The uncle of curr is black, rotation required
      else {

        // Case RL: curr is left child of its parent, right-rotation required
        if(curr == parent->left) {
          curr = parent;
          rightRotation(curr);
          parent = curr->parent;
        }

        // Case RR: curr is right child of its parent, left-rotation required
        swap(parent->color, grand_parent->color);
        leftRotation(grand_parent);
      }
    }
  }

  // make sure the root is always black
  root->color = BLACK;
}

/*
Concept (Deletion)

1. Perform standard BST delete. When we perform standard delete operation in BST,
   we always end up deleting a node which is either leaf or has only one child.
   Let y be the node to be deleted and x be the child that replaces y.
2. Simple Case: If either x or y is red, we mark the replaced child as black (No
   change in black height). Note that both x and y cannot be red as y is parent
   of x and two consecutive reds are not allowed in red-black tree.
3. If Both u and v are Black.
   a) If sibling s is black and at least one of sibling’s children is "red",
      perform rotation(s). Let the red child of s be r. This case can be divided
      in four subcases depending upon positions of s and r.
     (i)   Left Left Case (s is left child of its parent and r is left child of
           s or both children of s are red)
     (ii)  Left Right Case (s is left child of its parent and r is right child)
     (iii) Right Right Case (s is right child of its parent and r is right
           child of s or both children of s are red)
     (iv)  Right Left Case (s is right child of its parent and r is left child of s)
   b) If sibling is black and its both children are black, perform recoloring,
      and recur for the parent if parent is black.
   c) If sibling is red, perform a rotation to move old sibling up, recolor the
      old sibling and parent. This mainly converts the tree to black sibling case
      (by rotation) and leads to case (a) or (b). This case can be divided in two
      subcases.
      (i)  Left Case (s is left child of its parent). We right rotate the parent p.
      (iI)  Right Case (s is right child of its parent). We left rotate the parent p.
   d) If u is root, make it single black.
*/
void RBT::deleteNode(int key) {
  TreeNode *delNode = search(key);

  if(delNode == NULL) {
    cout << "Key not Found" << endl;
    return;
  }

  TreeNode *y;  // node to be delete
  TreeNode *x;  // child of the node that about to be delete

  // y has at most y child afther the if-else opration
  if(delNode->left == NULL || delNode->right == NULL)
    y = delNode;
  else
    y = getSuccessor(delNode->right);

  // x might be a child of y or x = neel(null) if y has no child
  if(y->left)
    x = y->left;
  else if(y->right)
    x = y->right;
  else {

    // new a temp node as NULL
    x = new TreeNode(INT_MIN);
    x->color = BLACK;
  }

  // x's parent must be the y's parent once y got deleted
  x->parent = y->parent;

  // x is the y's parents' child once y got deleted
  if(y->parent == NULL)
    root = x;
  else if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  // Case 3 of standard BST deletion
  if(y != delNode)
    delNode->key = y->key;

  // store the color of y for later usage and delete memeory of y
  Color color = (Color)y->color;

  delete y;
  y = NULL;

  // Simple case: y is BLACK and x is red
  if(color == BLACK && x->color == RED)
    x->color = BLACK;
  // else if the deleted node is BLACK, fix it up
  else if(color == BLACK)
    FixDeletion(x);

  // delete the temp(NULL) node
  if(x->key == INT_MIN) {
    if(x == x->parent->right)
      x->parent->right = NULL;
    else
      x->parent->left = NULL;
    delete x;
    x = NULL;
  }

}

void RBT::FixDeletion(TreeNode *curr) {

  // Case 0: if curr is RED or root, simply make it black
  while(curr != root && curr->color == BLACK) {

    // we need to delete neel after the rotation and recoloring is done
    TreeNode *temp = NULL;

    // if curr is leftchild
    if(curr == curr->parent->left) {
      TreeNode *sibling = curr->parent->right;

      // Case 1: sibling is RED
      if(sibling->color == RED) {
        sibling->color = BLACK;
        curr->parent->color = RED;
        leftRotation(curr->parent);
        sibling = curr->parent->right;
      }

      // procede to Case 2, 3, 4: sibling is BLACK
      // Case 3 & 4: at least 1 red children
      if(hasRedChild(sibling)) {

        // Case 3: left child is RED
        if(sibling->left != NULL && sibling->left->color == RED) {
          sibling->left->color = BLACK;
          sibling->color = RED;
          rightRotation(sibling);
          sibling = curr->parent->right;
        }

        // After performing Case 3 fixing, it must turn to Case 4
        // Case 4: right child is RED, the other is BLACK
        sibling->color = curr->parent->color;
        curr->parent->color = BLACK;
        leftRotation(curr->parent);

        // After performing Case 4 fixing, the tree must be balanced,
        // for the total number of black node is remain unchange.
        curr = root;
      }
      // Case 2: both child are BLACK
      else {
        sibling->color = RED;
        curr = curr->parent;
      }
    }
    else {
      TreeNode *sibling = curr->parent->right;

      // Case 1: sibling is RED
      if(sibling->color == RED) {
        sibling->color = BLACK;
        curr->parent->color = RED;
        rightRotation(curr->parent);
        sibling = curr->parent->left;
      }

      // procede to Case 2, 3, 4: sibling is BLACK
      // Case 3 & 4: at least 1 red children
      if(hasRedChild(sibling)) {

        // Case 3: left child is RED
        if(sibling->right != NULL && sibling->right->color == RED) {
          sibling->right->color = BLACK;
          sibling->color = RED;
          leftRotation(sibling);
          sibling = curr->parent->left;
        }

        // After performing Case 3 fixing, it must turn to Case 4
        // Case 4: right child is RED, the other is BLACK
        sibling->color = curr->parent->color;
        curr->parent->color = BLACK;
        rightRotation(curr->parent);

        // After performing Case 4 fixing, the tree must be balanced,
        // for the total number of black node is remain unchange.
        curr = root;
      }
      // Case 2: both child are BLACK
      else {
        sibling->color = RED;
        curr = curr->parent;
      }
    }

  }

  // making root BLACK
  curr->color = BLACK;
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

// ***************** implementation of traversal functions *******************
void RBT::inorder() {
  inorder(root);
}

void RBT::inorder(TreeNode *curr) {
  if(curr) {
    inorder(curr->left);
    cout << curr->key << " ";
    inorder(curr->right);
  }
}

void RBT::levelorder() {
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

  RBT tree;

  tree.insert(7);
  tree.insert(3);
  tree.insert(18);
  tree.insert(10);
  tree.insert(22);
  tree.insert(8);
  tree.insert(11);
  tree.insert(26);
  tree.insert(2);
  tree.insert(6);
  tree.insert(13);

  tree.inorder();
  cout << endl;
  tree.levelorder();

  cout << endl << "Deleting 18, 11, 3, 10, 22" << endl;

  tree.deleteNode(18);
  tree.deleteNode(11);
  tree.deleteNode(3);
  tree.deleteNode(10);
  tree.deleteNode(22);

  tree.inorder();
  cout << endl;
  tree.levelorder();

  return 0;
}
