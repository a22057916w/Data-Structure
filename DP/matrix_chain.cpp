#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef vector<vector<int>> vii;

int matrixChain(int x, int y, vector<int> arr) {
  int n = arr.size();
  vii dp(n + 1, vector<int>(n + 1, INT_MAX / 2));

  for(int i = 1; i < n + 1; i++)
    dp[i][i] = 0;

  for(int p = 2; p < n; p++)
    for(int i = 1; i < n - p + 1; i++) {
      int j = i + p - 1;
      dp[i][j] = INT_MAX / 2;
      for(int k = i; k < j; k++) {
        int q = dp[i][k] + dp[k + 1][j] + arr[i - 1]*arr[k]*arr[j];
        dp[i][j] = min(dp[i][j], q);
      }
    }

    return dp[x][y];
}

int main() {
  vector<int> arr = {1, 2, 3, 4};
  cout << matrixChain(1, 3, arr) << endl;
  return 0;
}
