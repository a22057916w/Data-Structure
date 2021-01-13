/*
Algorithm
1. Read the Prefix expression in reverse order (from right to left).
2. If the symbol is an operand, then push it onto the Stack.
3. If the symbol is an operator, then pop two operands from the Stack
   Create a string by concatenating the two operands and the operator between
   them. string = (operand1 + operator + operand2)
4. Repeat the above steps until end of Prefix expression.
*/

#ifndef PREFIX_TO_INFIX_H_
#define PREFIX_TO_INFIX_H_

#include <cctype>           // for function isalpah()
#include <string>
#include <stack>

using std::string;
using std::stack;

string PrefixToInfix(const string prefix) {
  stack<string> infix;

  // reading from right to left
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

      // concat the operands and operator
      infix.push("(" + op1 + prefix[i] + op2 + ")");
    }
  }

  // Stack now contains the Infix expression
  return infix.top();
}

#endif /* PREFIX_TO_INFIX_H_ */
