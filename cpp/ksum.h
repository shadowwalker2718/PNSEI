#pragma once

#include "henry.h"

namespace _ksum {

// return solution number

// return all feasible solutions

class Solution {
public:
  int kSum(vector<int> A, int k, int target) {
    if (A.size() < k || k <= 0)
      return 0;
    // std::sort(A.begin(), A.end());
    int r = 0;
    dfs(r, A, k, target, 0);
    return r;
  }

  void dfs(int &r, vector<int> &A, int k, int t, int head) {
    if (k > 2) {
      for (int i = head; i < A.size(); ++i)
        dfs(r, A, k - 1, t - A[i], head + 1);
    } else if (k == 2) {
      unordered_map<int, int> ms; // int->count
      for (int i = head; i < A.size(); ++i) {
        if (ms.count(t - A[i])) {
          r++;
          if (ms[A[i]] == 1)
            ms.erase(A[i]);
          else
            ms[A[i]]--;
        } else
          ms[A[i]]++;
      }
    } else if (k == 1)
      for (int i = head; i < A.size(); ++i)
        if (A[i] == t)
          r++;
  }
};

// https://discuss.leetcode.com/topic/47834/share-my-k-sum-c-solution
class Solution2 {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target, int k_ = 4) {
    k = k_;
    sort(nums.begin(), nums.end());
    tmp = vector<int>(k, 0);
    dfs(nums, target, k, 0);
    return res;
  }

private:
  vector<vector<int>> res;
  vector<int> tmp;
  int k;
  void dfs(vector<int> &nums, int target, int n, int start) {
    if (n == 2) {
      int end = nums.size() - 1;
      while (start < end) {
        if (nums[start] + nums[end] == target) {
          tmp[k - 2] = nums[start];
          tmp[k - 1] = nums[end];
          res.push_back(tmp);
          // remove duplicates
          while (++start < end && nums[start - 1] == nums[start])
            ;
          while (--end > start && nums[end + 1] == nums[end])
            ;
        } else if (nums[start] + nums[end] > target)
          end--;
        else
          start++;
      }
    } else {
      int len = nums.size() - n;
      while (start <= len) {
        tmp[k - n] = nums[start];
        dfs(nums, target - nums[start], n - 1, start + 1);
        while (++start <= len && nums[start - 1] == nums[start])
          ;
      }
    }
  }
};

void test() {
  // Solution2 sln;
  // assert(sln.kSum({ 1,4,7,10,12,15,16,18,21,23,24,25,26,29 }, 5, 13)==9);
}

} // namespace _ksum