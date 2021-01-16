#include <iostream>
#include <string>
#include <stack>
using namespace std;

class BST;
class TreeNode {
private:
    string data;
    TreeNode *parent;
    TreeNode *left, *right;
public:
  TreeNode(): parent(0), left(0), right(0), data('\0') {};
  TreeNode(string data): parent(0), left(0), right(0), data(data) {};

  friend class BST;
};

class BST {
private:
    TreeNode *root;
public:
    BST()
};
