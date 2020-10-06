// The expression of binomial coefficent is c(n, m) or (n m), where c(n, m) equals
// n!/m!(n-m)! for all n, m > 0, except for c(n, 0) = 1 and c(0, m) = 0,
// where n > 0 and m >= 0

// Applying Pascal's law for revursive solution. However, since it would cause
// stack-overflow, we would seek for a non_recusrive solution.

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef unsigned long long LLU;

#define REC 0
#if(REC == 1)

// By the Pascal's law, c(n, m) equals c(n - 1, m - 1) + c(n - 1, m), where n, m are
// positive natural number,

// For instance, let's say we want to find the combination of picking 5 students out of 10,
// It's equal to the combination of picking a particular student(No.3) then picking 4 out of 10,
// plus the combination of not picking a particular student(No.3) then picking 5 out of 10.

// Applying Pascal's law
LLU bin_coef(int n, int m) {
  if(n == 0 && m != 0)      // c(0, m) = 0, where m > 0
    return 0;
  else if(m == 0)           // c(n. 0) = 1, where n >= 0
    return 1;
  return bin_coef(n - 1, m - 1) + bin_coef(n - 1, m);
}

int main() {
  int n, m;
  while(cin >> n >> m && (n >= 0 && m >= 0))
    cout << bin_coef(n, m) << endl;
  return 0;
}

#else

int main() {
  LLU n, m;
  while(cin >> n >> m && (n >= 0 && m >= 0)) {
    LLU ans = 1;

    if(n == 0 && m != 0)        // c(0, m) = 0, where m > 0
      ans = 0;
    else if(m == 0 || n == m)   // c(n, 0) = 1 and c(n, n) = 1, where n >= 0, and m == n
      ans = 1;
    else {
      // c(n, m) = c(n, n-m), we want the latter to be smaller
      m = min(n - m, m);

      // c(n, m) = n!/m!(n-m)!
      //         = n(n-1)(n-2)...(n-m+1)/m(m-1)(m-2)...1
      for(int i = 0; i <= m - 1; i++)
        ans *= (n - i);
      for(int i = 0; i <= m - 1; i++)
        ans /= (m - i);
    }
    cout << ans << endl;
  }
  return 0;
}

#endif
