#include <iostream>
using namespace std;

typedef unsigned long long LLU;

#define REC 0

#if(REC == 1)
// Produced according to the Ackermann's function directly
LLU ack(int m, int n) {
  if(m == 0)
    return n + 1;
  if(m >= 0 && n == 0)
    return ack(m - 1, 1);
  else
    return ack(m - 1, ack(m, n - 1));
}
#else
// Since the recursive method may cause stackoverflow, we need another solution
LLU ack(int m, int n) {
    LLU ans = 0;
    for(int i = m; i >= 0; i--) {
      for(int j = n; j >= 0; j--) {
        for(int k = m; k >= 0; k--)
      }
    }
}
#endif

int main() {
  int m, n;
  while(cin >> m >> n && (m >= 0 && n >= 0))
    cout << ack(m, n) << endl;
  return 0;
}
