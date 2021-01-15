#include <iostream>
#include <string>
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

  // constructor functions
  TreeNode *ExpressionTreeByPrefix(const string postfix);
  TreeNode *ExpressionTreeByPostfix(const string prefix);
  TreeNode *ExpressionTreeByInfix(const string infix);

  // element access
  bool isOperator(const string data);
  int prec(const string data);

  // traversal functions
  void inorder(TreeNode *curr);
  void preorder(TreeNode *curr);
  void postorder(TreeNode *curr);

public:
  ExpressionTree(const string str, const string exp);

  // traversal functions
  void inorder();
  void preorder();
  void postorder();
};


// ************************ constructor implementation ************************
ExpressionTree::ExpressionTree(const string str, const string exp) {
  if(exp == "post")
    root = ExpressionTreeByPostfix(str);
  else if(exp == "pre")
    root = ExpressionTreeByPrefix(str);
  else if(exp == "in")
    root = ExpressionTreeByInfix(str);
  else
    cout << "Expression Type is wrong" << endl;
}

/*
Algorithm (Postfix input)
1. Scan the string from left to right.
2. If a character is an operand push that into the stack.
3. If a character is an operator pop two values from the stack make them its
   child and push the current node again.
4. In the end, the only element of the stack will be the root of an
   expression tree.
*/
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

      // op2 must palce before op1 for Postfix
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

/*
Algorithm (Postfix input)
1. Scan the string from right to left.
2. If a character is an operand push that into the stack.
3. If a character is an operator pop two values from the stack make them its
   child and push the current node again.
4. In the end, the only element of the stack will be the root of an
   expression tree.
*/
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

      // op1 must palce before op2 for Prefix
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

TreeNode *ExpressionTree::ExpressionTreeByInfix(const string infix) {
  stack<TreeNode *> st;
  stack<string> stO;
  TreeNode *opr, *op1, *op2;

  for(int i = 0; i < infix.size(); i++) {
    string op = "";
    op += infix[i];

    if(!isOperator(op)) {
      op1 = new TreeNode(op);
      st.push(op1);
    }
    else if(op == "(")
      stO.push(op);
    else if(op == ")") {
      while(!stO.empty() && stO.top() != "(") {
        opr = new TreeNode(stO.top());
        stO.pop();

        op1 = st.top();
        st.pop();
        op2 = st.top();
        st.top();

        opr->left = op2;
        opr->right = op1;

        st.push(opr);
      }
      stO.pop();
    }
    else {
      while(!stO.empty() && prec(op) <= prec(stO.top())) {
        opr = new TreeNode(stO.top());
        stO.pop();

        op1 = st.top();
        st.pop();
        op2 = st.top();
        st.pop();

        opr->left = op2;
        opr->right = op1;

        st.push(opr);
      }
      stO.push(op);
    }
  }

  while(!stO.empty()) {
    opr = new TreeNode(stO.top());
    stO.pop();

    op1 = st.top();
    st.pop();
    op2 = st.top();
    st.pop();

    opr->left = op2;
    opr->right = op1;

    st.push(opr);
  }

  TreeNode *et = st.top();
  st.pop();

  return et;
}

// ******************* element accesss func implementation *******************
bool ExpressionTree::isOperator(const string data) {
  return (data == "+" || data == "-" || data == "*" || data == "/"
    || data == "^" || data == ")" || data == "(");
}

int ExpressionTree::prec(const string data) {
  string op = "";
  op += data;

  if(op == "^")
    return 3;
  else if(op == "*" || op == "/")
    return 2;
  else if(op == "-" || op == "+")
    return 1;
  else
    return -1;
}
// ******************** traversal function implementation ********************
void ExpressionTree::inorder() {
  if(root) {
    inorder(root);
    cout <<"\n";
  }
}

void ExpressionTree::inorder(TreeNode *curr) {
  if(curr) {
    inorder(curr->left);
    cout << curr->data;
    inorder(curr->right);
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
    preorder(curr->left);
    preorder(curr->right);
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
    postorder(curr->left);
    postorder(curr->right);
    cout << curr->data;
  }
}


int main() {
  string postfix = "ab+ef*g*-";
  ExpressionTree ET(postfix, "post");
  ET.inorder();

  string prefix = "-+ab**efg";
  ExpressionTree ET2(prefix, "pre");
  ET2.inorder();

  string infix = "a+b-e*f*g";
  ExpressionTree ET3(infix, "in");
  ET3.postorder();

  return 0;
}
