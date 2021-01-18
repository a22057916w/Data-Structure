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

    TreeNode *search(int key, TreeNode *curr);
public:
    BST(): root(0) {};

    TreeNode *search(int key);
    void insert(int key);

    void inorder();
};


TreeNode *BST::search(int key) {
  return search(key, root);
}

TreeNode *BST::search(int key, TreeNode *curr) {

  // Base Cases: root(curr) is null or key is present at root(curr) 
  if(curr == NULL || curr->key = key)
    return curr;

  // Key is greater than root's key
  if(curr->key < key)
    return serach(key, curr->left);

  // Key is smaller than root's key
  else
    return search(key, curr->right);
}
