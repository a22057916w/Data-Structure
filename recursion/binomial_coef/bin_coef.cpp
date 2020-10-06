#include <iostream>
using namespace std;

typedef unsigned long long LLU;

// By the Pascal's law, c(n, m) equals c(n - 1, m - 1) + c(n - 1, m).
// For instance, let's say we want to find the combination of picking 5 students out of 10,
// It's equal to the combination of picking a particular student(No.3) then picking 4 out of 10,
// plus the combination of not picking a particular student(No.3) then picking 5 out of 10.
LLU bin_coef(int n, int m) {
  if(n == 0)
    return 0;
  if(m == 0)
    return 1;

  // Applying Pascal's law
  return bin_coef(n - 1, m - 1) + bin_coef(n - 1, m);
}

int main() {
  int n, m;
  while(cin >> n >> m && (n >= 0 && m >= 0))
    cout << bin_coef(n, m) << endl;
}
