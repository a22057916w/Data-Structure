#include <iostream>
using namespace std;

typedef unsigned long long LLU;

LLU factorial(int n) {
  if(n == 0)
    return n;
  else
    return n * factorial(n - 1);
}

int main() {
  int n;
  cin >> n;
  cout << factorial(n) << endl;
}
