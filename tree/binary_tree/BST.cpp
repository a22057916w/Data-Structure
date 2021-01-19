#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class BST;
class TreeNode {
private:
  int key;
  string element;

  TreeNode *parent;
  TreeNode *left, *right;

public:
  TreeNode(): parent(0), left(0), right(0), key(0), element("") {};
  TreeNode(int k, string e): parent(0), left(0), right(0), key(k), element(e) {};

  int getKey() {return key;}
  string getElement() {return element;}

  friend class BST;
};

class BST {
private:
    TreeNode *root;

    // element access
    TreeNode *search(int key, TreeNode *root);
    TreeNode *getSuccessor(TreeNode *curr);

    // modifying function
    TreeNode *insert(TreeNode *root, TreeNode *newNode);
    TreeNode *deleteNode(TreeNode *root, int key);

    // traversal function
    void inorder(TreeNode *curr);

public:
    BST(): root(0) {};

    // element access
    TreeNode *search(int key);

    // modifying function
    void insert(int key, string element);
    void deleteNode(int key);

    // traversal function
    void inorder();
    void levelorder();
};


// ****************** element access function implementation ******************
TreeNode *BST::search(int key) {
  return search(key, root);
}

TreeNode *BST::search(int key, TreeNode *root) {

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

TreeNode *BST::getSuccessor(TreeNode *curr) {
  while(curr && curr->left)
    curr = curr->left;
  return curr;
}

// ********************* modifying function implementation ********************
void BST::insert(int key, string element) {
  root = insert(root, new TreeNode(key, element));
}

TreeNode *BST::insert(TreeNode *root, TreeNode *newNode) {

  // If the root is empty or reach the bottom of a leaf
  if(root == NULL)
    return newNode;

  // Key is smaller than root's key
  if(newNode->key <= root->key)
    root->left  = insert(root->left, newNode);

  // Key is greater than root's key
  else
    root->right = insert(root->right, newNode);

  return root;
}

void BST::deleteNode(int key) {
  root = deleteNode(root, key);
}

TreeNode *BST::deleteNode(TreeNode *root, int key) {

  // base case
  if(root == NULL)
    return root;

  if(key < root->key)
    root->left = deleteNode(root->left, key);

  // If the key to be deleted is greater than the root's key, then it lies in
  // right subtree
  else if(key > root->key)
    root->right = deleteNode(root->right, key);

  // if key is same as root's key, then This is the node to be deleted
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
    TreeNode *temp = getSuccessor(root->right);

    // Copy the inorder successor's content to this node
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }

  // To retrun the result of Csee 3
  return root;
}
// ******************* traversal function implementation **********************
void BST::inorder() {
  inorder(root);
}

void BST::inorder(TreeNode *curr) {
  if(curr) {
    inorder(curr->left);
    cout << curr->element << "(" << curr->key << ") ";
    inorder(curr->right);
  }
}

void BST::levelorder() {
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
  BST T;

  T.insert(8,"龜仙人");
  T.insert(1000,"悟空");
  T.insert(2,"克林");
  T.insert(513,"比克");


  cout << "Inorder Traversal:\n";
  T.inorder();
  cout << endl;
  cout << "Level-order Traversal:\n";
  T.levelorder();
  cout << endl << endl;

  TreeNode *node = T.search(1000);
  if(node != NULL){
      cout << "There is " << node->getElement() << "(" << node->getKey() << ")" << endl;
  }
  else {
      cout << "no element with Key(1000)" << endl;
  }

  node = T.search(73);
  if(node != NULL){
    cout << "There is " << node->getElement() << "(" << node->getKey() << ")" << endl;
  }
  else {
    cout << "no element with Key(73)" << endl;
  }


  cout << "Delete 20" << endl;
  T.deleteNode(1000);
  cout << "Inorder traversal of the modified tree" << endl;
  T.inorder();
  cout << endl;
  cout << "Level-order Traversal:\n";
  T.levelorder();
  cout << endl << endl;

  return 0;
}
