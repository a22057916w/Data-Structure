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

  friend class BST;
};

class BST {
private:
    TreeNode *root;
public:
    BST()
};
