/*
Algorithm
1. Scan the infix expression from left to right.
2. If the scanned character is an operand, output it.
3. Else,
      1 If the precedence of the scanned operator is greater than the precedence
        of the operator in the stack(or the stack is empty or the stack contains
        a ‘(‘ ), push it.
      2 Else, Pop all the operators from the stack which are greater than in
        precedence than that of the scanned operator. After doing
        that Push the scanned operator to the stack. (If you encounter
        parenthesis while popping then stop there and push the scanned operator
        in the stack.)
4. If the scanned character is an ‘(‘, push it to the stack.
5. If the scanned character is an ‘)’, pop the stack  and output it until a ‘(‘
   is encountered, and discard both the parenthesis.
6. Repeat steps 2-6 until infix expression is scanned.
7. Print the output
8. Pop and output from the stack until it is not empty.
*/

#include <iostream>
#include <cctype>       // For function isalpha()
#include <string>
#include <stack>
#include <vector>
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
vector<char> InfixToPostfix(const string s) {
  vector<char> postExp;           // Declared as return params
  stack<char> st;

  for(int i = 0; i < s.length(); i++) {

    // If the scanned character is an operand, add it to output vector.
    if(isalpha(s[i]))
      postExp.push_back(s[i]);

    // If the scanned character is an ‘(‘, push it to the stack.
    else if(s[i] == '(')
      st.push(s[i]);

    // If the scanned character is an ‘)’, pop and to output string from the
    // stack until an ‘(‘ is encountered.
    else if(s[i] == ')') {
      while(!st.empty() && st.top() != '(') {
        postExp.push_back(st.top());
        st.pop();
      }
      if(st.top() == '(')
        st.pop();
    }

    //If an operator is scanned
    else {
      while(!st.empty() && prec(s[i]) < prec(st.top())) {
          postExp.push_back(st.top());
          st.pop();
      }
      st.push(s[i]);
    }
  }

  // Pop all the remaining elements from the stack
  while(!st.empty()) {
    postExp.push_back(st.top());
    st.pop();
  }

  return postExp;
}

int main() {
  string exp = "a+b*(c^d-e)^(f+g*h)-i";

  vector<char> postExp = InfixToPostfix(exp);
  for(auto c : postExp)
    cout << c;
  cout << "\n";

  return 0;
}
