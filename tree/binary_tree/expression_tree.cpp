#include <iostream>
#include <cctype>
#include <stack>
using namespace std;

class ExpressionTree;
class TreeNode {
private:
    string data;
    TreeNode *parent;
    TreeNode *left, *right;
public:
  TreeNode(): parent(0), left(0), right(0), data('\0') {};
  TreeNode(string data): parent(0), left(0), right(0), data(data) {};

  friend class ExpressionTree;
};

class ExpressionTree {
private:
  TreeNode *root;


  TreeNode *ExpressionTreeByPrefix(const string postfix);
  TreeNode *ExpressionTreeByPostfix(const string prefix);

  bool isOperator(const string data);

  void inorder(TreeNode *curr);
  void preorder(TreeNode *curr);
  void postorder(TreeNode *curr);

public:
  ExpressionTree(const string str, string exp);

  void inorder();
  void preorder();
  void postorder();
};


// ************************ constructor implementation ************************
ExpressionTree::ExpressionTree(const string str, string exp) {
  if(exp == "post")
    root = ExpressionTreeByPostfix(str);
  else if(exp == "pre")
    root = ExpressionTreeByPrefix(str);
}


TreeNode *ExpressionTree::ExpressionTreeByPostfix(const string postfix) {
  stack<TreeNode *> st;
  TreeNode *opr, *op1, *op2;

  for(int i = 0; i < postfix.size(); i++) {
    string op = "";
    op += postfix[i];

    if(!isOperator(op)) {
      op1 = new TreeNode(op);
      st.push(op1);
    }
    else {
      opr = new TreeNode(op);

      op1 = st.top();
      st.pop();
      op2 = st.top();
      st.pop();

      opr->left = op2;
      opr->right = op1;

      st.push(opr);
    }
  }

  TreeNode *et = st.top();
  st.pop();

  return et;
}

TreeNode *ExpressionTree::ExpressionTreeByPrefix(const string prefix) {
  stack<TreeNode *> st;
  TreeNode *opr, *op1, *op2;

  for(int i = prefix.size() - 1; i >= 0; i--) {
    string op = "";
    op += prefix[i];

    if(!isOperator(op)) {
      op1 = new TreeNode(op);
      st.push(op1);
    }
    else {
      opr = new TreeNode(op);

      op1 = st.top();
      st.pop();
      op2 = st.top();
      st.pop();

      opr->left = op1;
      opr->right = op2;

      st.push(opr);
    }
  }

  TreeNode *et = st.top();
  st.pop();

  return et;
}

// ******************* element accesss func implementation *******************
bool ExpressionTree::isOperator(const string d) {
  return (d == "+" || d == "-" || d == "*" || d == "/" || d == "^");
}

// ******************** treversal function implementation ********************
void ExpressionTree::inorder() {
  if(root) {
    inorder(root);
    cout <<"\n";
  }
}

void ExpressionTree::inorder(TreeNode *curr) {
  if(curr) {
    inorder(curr);
    cout << curr->data;
    inorder(curr);
  }
}

void ExpressionTree::preorder() {
  if(root) {
    preorder(root);
    cout <<"\n";
  }
}

void ExpressionTree::preorder(TreeNode *curr) {
  if(curr) {
    cout << curr->data;
    preorder(curr);
    preorder(curr);
  }
}

void ExpressionTree::postorder() {
  if(root) {
    postorder(root);
    cout <<"\n";
  }
}

void ExpressionTree::postorder(TreeNode *curr) {
  if(curr) {
    postorder(curr);
    postorder(curr);
    cout << curr->data;
  }
}


int main() {
  return 0;
}
