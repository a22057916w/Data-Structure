#include <iostream>
#include <cctype>
#include <string>
#include <stack>
using namespace std;

string PostfixToInfix(const string postfix) {
  stack<string> infix;

  for(int i = 0; i < postfix.length(); i++) {

    if(isalpha(postfix[i])) {
      string op(1, postfix[i]);
      infix.push(op);
    }
    else {
      string op1 = infix.top();
      infix.pop();
      string op2 = infix.top();
      infix.pop();

      infix.push("(" + op2 + postfix[i] + op1 + ")");
    }
  }

  return infix.top();
}

int main() {
  string postfix = "xyae+/%";

  cout << PostfixToInfix(postfix) << endl;
  return 0;
}
