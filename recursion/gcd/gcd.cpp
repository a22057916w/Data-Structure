#include <iostream>
using namespace std;

typedef unsigned long long LLU;

#define REC 0

#if(REC == 1)
// It's presumably a >= b but it's okay for the other way around.
LLU gcd(int a, int b) {
  if(b == 0)
    return a;
  else
    return gcd(b, a % b);
}
#else
// Using loop to implement gcd
LLU gcd(int a, int b) {
    while(b > 0) {
      int tmp = b;
      b = a % b;
      a = tmp;
    }
    return a;
}
#endif

int main() {
  int a, b;
  while(cin >> a >> b && (a >= 0 && b >= 0))
    cout << gcd(a, b) << endl;
  return 0;
}
