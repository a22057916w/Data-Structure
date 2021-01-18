#include <iostream>
#include <string>
#include <stack>
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

    TreeNode *search(int key, TreeNode *root);

    TreeNode *insert(TreeNode *root, TreeNode *newNode)

public:
    BST(): root(0) {};

    TreeNode *search(int key);

    void insert(int key, element);

    void inorder();
};


TreeNode *BST::search(int key) {
  return search(key, root);
}

TreeNode *BST::search(int key, TreeNode *root) {

  // Base Cases: root(curr node) is null or key is present at root(curr node)
  if(root == NULL || root->key = key)
    return root;

  // Key is smaller than root's key
  if(key < root->key)
    return serach(key, root->left);

  // Key is greater than root's key
  else
    return search(key, root->right);
}

void BST::insert(int key, string element) {
  insert(root, new TreeNode(key, element));
}

TreeNode* BST::insert(TreeNode *root, TreeNode *newNode) {

  // If the root is empty or reach the bottom of a leaf
  if(root == NULL)
    return newNode;

  // Key is smaller than root's key
  if(newNode->key <= curr->key)
    root->left  = insert(root->left, newNode);

  // Key is greater than root's key
  else
    root->right = insert(root->right, newNode);

  return root;
}
