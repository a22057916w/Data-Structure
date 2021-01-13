#ifndef PREFIX_TO_INFIX_H_
#define PREFIX_TO_INFIX_H_

#include <cctype>
#include <string>
#include <stack>

using std::string;
using std::stack;

string PrefixToInfix(const string prefix) {
  stack<string> infix;

  for(int i = prefix.length() - 1; i >= 0; i--) {

    if(isalpha(prefix[i])) {
      string op(1, prefix[i]);
      infix.push(op);
    }
    else {
      string op1 = infix.top();
      infix.pop();
      string op2 = infix.top();
      infix.pop();

      infix.push("(" + op1 + prefix[i] + op2 + ")");
    }
  }

  return infix.top();
}

#endif /* PREFIX_TO_INFIX_H_ */
