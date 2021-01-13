#include "infix_to_postfix.h"
#include "infix_to_prefix.h"
#include "postfix_to_infix.h"
#include "prefix_to_infix.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
  string exp = "(a-b/c)*(a/k-l)";

  string postExp = InfixToPostfix(exp);
  string preExp = InfixToPrefix(exp);

  cout << postExp << endl;
  cout << preExp << endl;

  cout << PostfixToInfix(postExp) << endl;
  cout << PrefixToInfix(preExp) << endl;

  return 0;
}
