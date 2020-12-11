#pragma once

#pragma once
#include "pnsei.h"
#include <mutex> // For std::unique_lock
#include <numeric>
#include <shared_mutex>

namespace _comb_sum {

class Solution {
public:
  int combinationSum4(vector<int> &nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < target; i++) {
      for (int num : nums) {
        if (i + num <= target) {
          dp[i + num] += dp[i];
          cout << i + num << "|" << dp[i + num] << "+=" << i << "&" << dp[i]
               << ",";
        }
      }
      cout << endl;
    }
    return dp[target];
  }
};

void test() {
  Solution sln;
  vector<int> v = {1, 2, 5};
  cout << sln.combinationSum4(v, 11) << endl;
}
} // namespace _comb_sum
