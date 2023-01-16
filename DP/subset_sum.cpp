#include <iostream>
#include <vector>
using namespace std;

bool isSubsetSum(vector<int> &set, int sum) {
  int n = set.size();

  // subset[i][j] means there is a subset of set[a0, a1, ... ai] that has an
  // answer for the sum(j)
  vector<vector<bool>> subset(n + 1, vector<bool>(n + 1, false));

  // if sum is 0, the answer is true.
  // [0][0] must be set for true, for a one element subset condition check.
  for(int i = 0; i <= n; i++)
    subset[i][0] = true;

  /*
  We choose whether a new element should be "selected" to the subset,
  let j is sum, ai is element:
    Case j < ai:
     the sum is less than the ai, so we definitely not choosing it
    Case j >= ai:
     Option 1: Don't pick ai.
     Option 2: Pick ai, j - ai;
  */
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= sum; j++) {
      if(j < set[i - 1])      // set[i - 1] bc i start from 1
        subset[i][j] = subset[i - 1][j];
      else
        subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
    }



  // uncomment to print the table
  // for(int i = 0; i <= n; i++) {
  //   for(int j = 0; j <= sum; j++)
  //     cout << subset[i][j] << " ";
  //   cout << endl;
  // }

  return subset[n][sum];
}

int main() {
  vector<int> set = {3, 4, 5, 2};
  int sum = 6;

  if(isSubsetSum(set, sum) == true)
    cout << "Found a subset with given sum" << endl;
  else
    cout << "No subset with given sum" << endl;

  return 0;
}
