#include <iostream>
using namespace std;

class ExpressionTree;
class TreeNode {
private:
    char data;
    TreeNode *parent;
    TreeNode *left, *right;
public:
  TreeNode(): parent(0), left(0), right(0), data('\0') {};
}

int main() {
  return 0;
}
