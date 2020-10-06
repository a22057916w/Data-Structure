#include <iostream>
using namespace std;

typedef unsigned long long LLU;

LLU factorial(int n) {
  if(n == 0)
    return 0;
  if(n == 1)
    return n;
  else
    return n * factorial(n - 1);
}

int main() {
  int n;
  while(cin >> n && n != -1)
    cout << factorial(n) << endl;
  return 0;
}
