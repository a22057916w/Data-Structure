#include <iostream>
using namespace std;

typedef unsigned long long LLU;


// The concept is (Stpe 1.) moveing n - 1 discs from A(start) to B,
// then (Step 2.) moving the last disc from A to C(dest),
// finally, (Step 3.) moving all the discs from B to C.

// Suggestion to picture a diagram to draw a conclusion,
// such that H(4) = (Step 1.)H(3) + (Step 2.)1 + (Step 3.)H(3), H(3) = H(2) + 1 + H(2) ...

// H(discs, begin, bridge, end)
LLU hanoi(int n, LLU steps) {
  if(n == 1)
    return 1;
  else {
    int tmp = steps;
    steps += hanoi(n - 1, tmp);   // Step 1. H(n - 1, A, C, B)
    steps += hanoi(1, tmp);       // Step 2. H(1, A, B, C)
    steps += hanoi(n - 1, tmp);   // Step 3. H(n - 1, B, A, C)
  }
  return steps;
}

int main() {
  int n;
  while(cin >> n && n > 0)
    cout << hanoi(n, 0) << endl;
  return 0;
}
