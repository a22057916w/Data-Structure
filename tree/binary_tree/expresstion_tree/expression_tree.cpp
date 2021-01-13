#include <iostream>
#include <cctype>
#include <stack>
using namespace std;

class ExpressionTree;
class TreeNode {
private:
    char data;
    TreeNode *parent;
    TreeNode *left, *right;
public:
  TreeNode(): parent(0), left(0), right(0), data('\0') {};
  TreeNode(char data): parent(0), left(0), right(0), data(data) {};

  friend class ExpressionTree;
}

class ExpressionTree {
private:
  TreeNode *root;

  ExpressionTree(const string postfix);
  ExpressionTree(const string prefix);

  bool isOperator(const string data);

  void inorder(TreeNode *curr);
  void preorder(TreeNode *curr);
  void postorder(TreeNode *curr);

public:
  ExpressionTree(const string postfix);
  ExpressionTree(const string prefix);

  void inorder();
  void preorder();
  void postorder();
};


// ***************** constructor implementation *****************
ExpressionTree::ExpressionTree(const string postfix) {
  stack<TreeNode *> st;
  TreeNode *opr, *op1, *op2;

  for(int i = 0; i < postfix.size(); i++) {
    if(!isOperator(postfix[i])) {

    }
  }
}


bool ExpressionTree::isOperator(const string d) {
  return (d == "+" || d == "-" || d == "*" || d == "/" || d == "^");
}



int main() {
  return 0;
}
