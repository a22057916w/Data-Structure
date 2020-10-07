#include <iostream>
using namespace std;

typedef unsigned long long LLU;

LLU ack(int m, int n) {
  if(m == 0)
    return n + 1;
  if(m >= 0 && n == 0)
    return ack(m - 1, 1);
  else
    return ack(m - 1, ack(m, n - 1));
}

int main() {
  int m, n;
  while(cin >> m >> n && (m >= 0 && n >= 0))
    cout << ack(m, n) << endl;
  return 0;
}
