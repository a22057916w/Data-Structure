/*
Algorithm
1. Read the Postfix expression from left to right.
2. If the symbol is an operand, then push it onto the Stack.
3. If the symbol is an operator, then pop two operands from the Stack
   Create a string by concatenating the two operands and the operator between
   them. string = (operand2 + operator + operand1)
4. Repeat the above steps until end of Postfix expression.
*/

#ifndef POSTFIX_TO_INFIX_H_
#define POSTFIX_TO_INFIX_H_

#include <cctype>           // for function isalpah()
#include <string>
#include <stack>

using std::string;
using std::stack;

string PostfixToInfix(const string postfix) {
  stack<string> infix;

  // read from left to right
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

  // There must be a single element in stack now which is the required infix.
  return infix.top();
}

#endif /* POSTFIX_TO_INFIX_H_ */
