// https://leetcode.com/problems/maximum-subarray/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_end = 0;
        int max_sum = INT_MIN;

        // if the next number > max_end(1st to curr), max_end = number
        for(int i = 0; i < nums.size(); i++) {
            max_end = max(nums[i], nums[i] + max_end);
            max_sum = max(max_sum, max_end);
        }

        return max_sum;
    }
};
