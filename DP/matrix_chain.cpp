#include <iostream>
#include <vector>
#include <climits>        // for macro INT_MAX
#include <algorithm>
using namespace std;

typedef vector<vector<int>> vii;

// fill the dp with bottom up "diagonally", better draw an adjacent matrix
int matrixChain(int x, int y, vector<int> arr) {
  int n = arr.size();

  // we us index '1' as start
  vii dp(n + 1, vector<int>(n + 1, INT_MAX / 2));

  // init diagnoal entry of 2D-dp
  for(int i = 1; i < n + 1; i++)
    dp[i][i] = 0;

  // p for the multiplication lenght, ex. (AB)C...Z
  // we need to proceed all the way to include (ABC...Z)
  for(int p = 2; p < n; p++) {

    // find the optimal solution, starting from arr[1] to arr[n - p + 1]
    // ex. case: (ABC)DE to case: AB(CDE)
    for(int i = 1; i < n - p + 1; i++) {

      // set the end mark                            i  j
      // ex. find the optimal partition in ABC from (ABC)DE
      int j = i + p - 1;

      // find the optimal break point in [i, j]
      // ex. find the minimun multiplication by the order A(BC) for ABC
      for(int k = i; k < j; k++) {

        // opt(Ai...Aj) = Ai...Ak * Ak+1...Aj + dim(Ai...Ak)*dim(Ak+1...Aj)
        // ex. dp[1][3] = dp[1][1] + dp[2][3] + dim(A0*A1)*dim(A2*A3)
        //                                          p * q * r
        int mul = dp[i][k] + dp[k + 1][j] + arr[i - 1]*arr[k]*arr[j];
        dp[i][j] = min(dp[i][j], mul);
      }
    }
  }

    return dp[x][y];
}

int main() {
  vector<int> arr = {1, 2, 3, 4};
  cout << matrixChain(1, 3, arr) << endl;
  return 0;
}

/*
Reference:
  https://www.youtube.com/watch?v=GMzVeWpyTN0
*/
