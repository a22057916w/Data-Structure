#include <iostream>
using namespace std;

typedef unsigned long long LLU;

#define REC = 1
#if(REC = 1)

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
  return 0;
}

#else
#define MAXN 1005

int main() {

  LLU fib[MAXN] = {0};
  fib[0] = 0, fib[1] = 1;

  for(int i = 2; i < MAXN; i++)
    fib[i] = fib[i - 1] + fib[i - 2];

  int n;
  while(cin >> n && n >= 0)
    cout << fib[n] << endl;
}

#endif
