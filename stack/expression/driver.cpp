#include <infix_to_postfix.h>
#include <infix_to_prefix.h>

#include <iostream>
#include <string>

using namespace std;

int main() {
  string exp = "(a-b/c)*(a/k-l)";

  string postExp = InfixToPostfix(exp);
  string preExp = InfixToPrefix(exp);

  cout << postExp << endl;
  cout << preExp << endl;

  return 0;
}
