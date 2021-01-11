/*
Concept
1. New 2 stacks A and B for output and temporary storage.
2. Scan the infix expression from right to left.
3. If the scanned character, push it to A
4. Else,
      1 If the precedence of the scanned operator is greater than the precedence
        of the operator in B(or the stack is empty or the stack contains
        a ‘)‘ ), push it.
      2 Else, Pop all the operators from B which are greater than in
        precedence than that of the scanned operator. After doing
        that Push the scanned operator to the stack. (If you encounter
        parenthesis while popping then stop there and push the scanned operator
        in the stack.)
5. If the scanned character is an ‘)‘, push it to B.
6. If the scanned character is an ‘(’, pop B and push it to A until a ‘(‘
   is encountered, and discard both the parenthesis.
7. Repeat steps 3-6 until infix expression is scanned.
8. Pop all the operators from B to A until B is not empty.
9. Pop and print the output from A until it is not empty.
.*/

/*
Algorithm 1
1. reverse the string and '(', ')'.
2. Scan the infix expression from left to right.
3. Do step 3 to 9 from Concept with '(', ')' exchange.
*/

#include <iostream>
#include <cctype>       // For function isalpha()
#include <string>
#include <stack>
#include <vector>
#include <algorithm>  // for reversing string
using namespace std;

// Function to return the precedence of operators
int prec(const char c) {
  if(c == '^')
    return 3;
  else if(c == '*' || c == '/')
    return 2;
  else if(c == '-' || c == '+')
    return 1;
  else
    return -1;
}

// The main function to convert infix expression to pretfix expression
string InfixToPrefix(const string str) {
  string s = str;               // tmp for const str
  string preExp = "";           // return params
  stack<char> out, tmp;

  // Reverse the given string and exchange '(', ')'.
  // Make sure using reference to be able to change elements from s
  reverse(s.begin(), s.end());
  for(auto &c : s) {
    if(c == ')')
      c = '(';
    else if(c == '(')
      c = ')';
  }

  for(int i = 0; i < s.length(); i++) {

    // If the scanned character is an operand, push it to out(stack).
    if(isalpha(s[i]))
      out.push(s[i]);

    // If the scanned character is an ‘(‘, push it to tmp(stack).
    else if(s[i] == '(')
      tmp.push(s[i]);

    // If the scanned character is an ‘)’, pop to out(stack) from tmp(stack)
    // until an ‘(‘ is encountered.
    else if(s[i] == ')') {
      while(!tmp.empty() && tmp.top() != '(') {
        out.push(tmp.top());
        tmp.pop();
      }
      if(tmp.top() == '(')
        tmp.pop();
    }

    // If an operator is scanned
    else {
      while(!tmp.empty() && prec(s[i]) <= prec(tmp.top())) {
          out.push(tmp.top());
          tmp.pop();
      }
      tmp.push(s[i]);
    }
  }

  // Pop all the remaining elements from tmp(stack) to out(stack)
  while(!tmp.empty()) {
    out.push(tmp.top());
    tmp.pop();
  }

  // Pop all the remaining elements and add it to return string(preExp)
  // from out(stack)
  while(!out.empty()) {
    preExp += out.top();
    out.pop();
  }

  return preExp;
}

int main() {
  string exp = "(a-b/c)*(a/k-l)";

  string preExp = InfixToPrefix(exp);
  for(auto c : preExp)
    cout << c;
  cout << "\n";

  return 0;
}
