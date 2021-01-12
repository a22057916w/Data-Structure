#include <isotream>

#include <infix_to_postfix.h>

using namespace std;

int main() {
  string exp = "(a-b/c)*(a/k-l)";

  string postExp = InfixToPostfix(exp);
  cout << postExp << endl;

  return 0;
}
