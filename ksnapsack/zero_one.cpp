#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ZO_KS(vector<int> &V, vector<int> &W, int weight) {
  int n = V.size();
  vector<vector<int>> KS(n + 1, vector<int>(weight + 1));

  for(int i = 1; i <= n; i++)
    for(int w = 1; w <= weight; w++) {
      if(w - W[i] < 0)
        KS[i][w] = KS[i - 1][w];
      else
        KS[i][w] = max(V[i] + KS[i - 1][w - W[i]], KS[i - 1][w]);
    }

  return KS[n][weight];
}


int main() {

  vector<int> val = { 60, 100, 120};
  vector<int> wt = { 10, 20, 30 };
  int weight = 50;

  cout << ZO_KS(val, wt, weight) << endl;

  return 0;
}
