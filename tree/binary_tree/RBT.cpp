#include <iostream>
#include <string>
using namespace std;

class RBT;
class TreeNode {
private:
    TreeNode *left, *right;
    TreeNode *parent;

    int key, color;

public:


    friend class RBT;
};

class RBT {
private:
  TreeNode *root;
};

int main() {
  return 0;
}
