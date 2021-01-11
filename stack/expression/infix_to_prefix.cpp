/*Algorithm
1. Scan the infix expression from left to right.
2. If the scanned character is an operand, output it.
3. Else,
      1 If the precedence of the scanned operator is greater than the precedence
        of the operator in the stack(or the stack is empty or the stack contains
        a ‘(‘ ), push it.
      2 Else, Pop all the operators from the stack which are greater than or
        equal to in precedence than that of the scanned operator. After doing
        that Push the scanned operator to the stack. (If you encounter
        parenthesis while popping then stop there and push the scanned operator
        in the stack.)
4. If the scanned character is an ‘(‘, push it to the stack.
5. If the scanned character is an ‘)’, pop the stack  and output it until a ‘(‘
   is encountered, and discard both the parenthesis.
6. Repeat steps 2-6 until infix expression is scanned.
7. Print the output
8. Pop and output from the stack until it is not empty.*/

#include <iostream>
#include <cctype>       // For function isalpha()
#include <string>
#include <stack>
#include <vector>
#include <algorith>
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

// The main function to convert infix expression
// to postfix expression
string InfixToPrefix(const string s) {
  string str = s;
  string preExp = "";           // Declared as return params
  stack<char> out, tmp;

  reverse(str.begin(), str.end());
  for(auto c : str) {
    if(c == ')')
      c = '(';
    if(c == '(')
      c = ')';
  }

  for(int i = 0; i < s.length(); i++) {

    // If the scanned character is an operand, add it to output vector.
    if(isalpha(s[i]))
      out.push(s[i]);

    // If the scanned character is an ‘(‘, push it to the stack.
    else if(s[i] == '(')
      tmp.push(s[i]);

    // If the scanned character is an ‘)’, pop and to output string from the
    // stack until an ‘(‘ is encountered.
    else if(s[i] == ')') {
      while(!tmp.empty() && tmp.top() != '(') {
        out.push((tmp.top());
        tmp.pop();
      }
      if(tmp.top() == '(')
        tmp.pop();
    }

    //If an operator is scanned
    else {
      while(!tmp.empty() && prec(s[i]) <= prec(tmp.top())) {
          out.push(tmp.top());
          tmp.pop();
      }
      tmp.push(s[i]);
    }
  }

  // Pop all the remaining elements from the stack
  while(!out.empty()) {
    s += out.top();
    out.pop();
  }

  return preExp;
}

int main() {
  string exp = "a+b*(c^d-e)^(f+g*h)-i";

  string preExp = InfixToPretfix(exp);
  for(auto c : pretExp)
    cout << c;
  cout << "\n";

  return 0;
}
