// https://leetcode.com/problems/coin-change/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
      vector<int> dp(amount + 1, INT_MAX / 2);
      dp[0] = 0;

      // dp[i] represents the fewest number of coins to make up the amount i
      for(int i = 1; i < dp.size(); i++)
        for(const auto& coin : coins)
          if(coin <= i)
            dp[i] = min(dp[i], dp[i - coin] + 1);

      return dp[amount] < INT_MAX / 2 ? dp[amount] : -1;
    }
};
