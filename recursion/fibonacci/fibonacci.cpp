#include <iostream>
using namespace std;

typedef unsigned long long LLU;

LLU fibonacci(int n) {
  if(n == 0)
    return 0;
  if(n == 1)
    return 1;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  int n;

  while(cin >> n && n >= 0)
    cout << fibonacci(n) << endl;
}
