#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// top-down 2D-dp, better draw an adjacent matrix
int ZO_KS(vector<int> &V, vector<int> &W, int weight) {
  int n = V.size();
  vector<vector<int>> KS(n + 1, vector<int>(weight + 1));
  // KS[i][w]:
  // 1. i for first item to ith item
  // 2. w for avaliable weight

  // For the ith item, there are two cases:
  // 1. the ith item is in optimal solution, which considered as KS[i - 1][w - W[i]] + V[i]
  // 2.             not in optimal solution, which considered as KS[i - 1][w]
  // Therefore, we select the larger one between the two cases.
  for(int i = 1; i <= n; i++)
    for(int w = 1; w <= weight; w++) {
      if(w - W[i] < 0)            // in case index out of range
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

/*
reference:
  https://www.youtube.com/watch?v=wNFypN2glsA&list=PLOAQYZPRn2V6ms1JSww6pqXKf5x0o_gan&index=24
*/
