#include <iostream>
using namespace std;

typedef long long LL;

// The method is applied if and only if y >= 0
LL exp(int x, int y) {
  if(y <= 0)
    return 1;
  else
    return x * exp(x, y - 1);
}

int main() {
  int x, y;

  // This only works when y >= 0
  while(cin >> x >> y && y >= 0)
    cout << exp(x, y) << endl;
  return 0;
}
