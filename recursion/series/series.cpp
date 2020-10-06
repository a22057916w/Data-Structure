// Using recursivee to solve 1 + 2 + ... + n

#include <iostream>
using namespace std;

typedef unsigned long long LLU;

LLU series(int n) {
  if(n == 0)
    return n;
  else
    return n + series(n - 1);
}

int main() {
  int n;

  while(cin >> n && n >= 0)
    cout << series(n) << endl;
}
