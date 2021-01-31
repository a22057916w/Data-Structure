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
  TreeNode *neel;   // stands for NIL, in case of IDE identifier error
};

int main() {
  return 0;
}
