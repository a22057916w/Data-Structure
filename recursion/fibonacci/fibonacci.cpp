#include <iostram>
using namespace std;

typedef unsigned long long LLU;

LLU fabonacci(int n) {
  if(n == 0)
    return 0;
  if(n == 1)
    return 1;
  return fabonacci(n - 1) + fabonacci(n - 2);
}

int main() {
  int n;

  while(cin >> n && n >= 0)
    cout << fabonacci(n) << endl;
}
