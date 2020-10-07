#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef unsigned long long LLU;

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

// perm(a, b, c) = a + perm(b, c) -> perm(b,c) = b + perm(c)
//                 b + perm(a, c)                c + perm(b)
//                 c + perm(a, b)
void perm(string s, int pos, int n, int len) {
  if(pos == n)
    cout << s.substr(0, len) << endl;
  else {
    for(int i = pos; i < n; i++) {
        swap(s[pos], s[i]);
        perm(s, pos + 1, n, len);
        swap(s[pos], s[i]);
    }
  }
  return;
}

int main() {
  int n, len;
  while(cin >> n && (0 < n && n <= 26)) {
    string s = alphabet;
    len = n;    // record the length of substring s[0] + ... + s[n]
    perm(s, 0, n, len);  // the function would print all the combinations
  }
  return 0;
}
