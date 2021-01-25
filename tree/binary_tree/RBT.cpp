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
#include <string>
using namespace std;

class RBT;
class TreeNode {
private:
    TreeNode *left, *right;
    TreeNode *parent;
    int key;
    int color;      // 0: Red, 1: Black; using type:bool is ok

public:


    friend class RBT;
};

class RBT {
private:
  TreeNode *root;
  TreeNode *neel;   // stands for NIL, in case of IDE identifier error
};

int main() {
  return 0;
}
