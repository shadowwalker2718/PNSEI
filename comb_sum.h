#pragma once

#pragma once
#include "henry.h"
#include <numeric>
#include <shared_mutex>
#include <mutex> // For std::unique_lock

namespace _comb_sum {

  class Solution {
  public:
    int combinationSum4(vector<int>& nums, int target) {
      vector<int> dp(target + 1, 0);
      dp[0] = 1;
      for (int i = 0; i < target; i++) {
        for (int num : nums) {
          if (i + num <= target) {
            dp[i + num] += dp[i];
            cout << i + num << "|" << dp[i + num] << "+=" << i << "&" << dp[i] << ",";
          }
        }
        cout << endl;
      }
      return dp[target];
    }
  };

  void test() {
    Solution sln;
    vector<int> v= {1, 2, 5};
    cout << sln.combinationSum4(v, 11) << endl;
  }
}













