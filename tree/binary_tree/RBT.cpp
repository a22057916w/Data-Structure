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
