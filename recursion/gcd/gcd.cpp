#include <iostream>
using namespace std;

typedef unsigned long long LLU;

// It's presumably a >= b but it's okay for the other way around.
LLU gcd(int a, int b) {
  if(b == 0)
    return a;
  else
    return gcd(b, a % b);
}

int main() {
  int a, b;
  while(cin >> a >> b && (a >= 0 && b >= 0))
    cout << gcd(a, b) << endl;
  return 0;
}
