//
// Created by Henry Wu on 11/17/18.
//

#ifndef PNSEI_18_4SUM_H
#define PNSEI_18_4SUM_H

#include "pnsei.h"

namespace _4sum {
// https://leetcode.com/problems/4sum/
// https://discuss.leetcode.com/topic/47834/share-my-k-sum-c-solution
/*
 * Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that
 * a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
 * */
class Solution {
public:
  vector<vector<int>> fourSum(vector<int> nums, int target, int k_ = 4) {
    K = k_;
    sort(nums.begin(), nums.end());
    tmp = vector<int>(K, 0);
    ksum_rec(nums, target, K, 0);
    return res;
  }

private:
  vector<vector<int>> res;
  vector<int> tmp;
  int K;

  void ksum_rec(const vector<int> &nums, int target, int n, int start) {
    if (n == 2) {
      int end = nums.size() - 1;
      while (start < end) {
        if (nums[start] + nums[end] == target) {
          tmp[K - 2] = nums[start];
          tmp[K - 1] = nums[end];
          res.push_back(tmp);
          // remove duplicates
          while (++start < end && nums[start - 1] == nums[start]);
          while (--end > start && nums[end + 1] == nums[end]);
        } else if (nums[start] + nums[end] > target)
          end--;
        else
          start++;
      }
    } else {
      int len = nums.size() - n;
      while (start <= len) {
        tmp[K - n] = nums[start];
        ksum_rec(nums, target - nums[start], n - 1, start + 1);
        while (++start <= len && nums[start - 1] == nums[start]);
      }
    }
  }
};

// Algo: two pointers
class Solution_Debug {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target, int K = 4) {
    sort(nums.begin(), nums.end());
    vector<int> tmp;
    ksum_rec(nums, tmp, target, K, 0);
    return res;
  }

private:
  vector<vector<int>> res;

  void ksum_rec(vector<int> &nums, vector<int> tmp, int target, int K, int start) {
    if (K == 2) {
      int end = nums.size() - 1;
      while (start < end) {
        if (nums[start] + nums[end] == target) {
          vector<int> t=tmp;
          t.push_back(nums[start]);
          t.push_back(nums[end]);
          res.push_back(t);
          while (++start < end && nums[start - 1] == nums[start]);
          while (--end > start && nums[end + 1] == nums[end]);
        } else if (nums[start] + nums[end] > target)
          end--;
        else
          start++;
      }
    } else {
      int end = nums.size() - K;
      while (start <= end) {
        vector<int> t=tmp;
        t.push_back(nums[start]);
        ksum_rec(nums, t, target - nums[start], K - 1, start + 1);
        while (++start <= end && nums[start - 1] == nums[start]);
      }
    }
  }
};

void test() {
  Solution sln;
  assert(sln.fourSum({ 1,0,-1,0,-2,2}, 0).size()==3);
}

} // namespace _ksum
#endif //PNSEI_18_4SUM_H
