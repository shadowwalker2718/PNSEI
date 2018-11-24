//
// Created by root on 11/23/18.
//

#ifndef PNSEI_480_SLIDING_WINDOW_MEDIAN_H
#define PNSEI_480_SLIDING_WINDOW_MEDIAN_H

#include "henry.h"

namespace _480_medianSlidingWindow{

// https://leetcode.com/problems/sliding-window-median/

struct Solution {
  vector<double> medianSlidingWindow(vector<int>& nums, int K) {
    if(K<=0) return {};
    multiset<int> BoundedBST(nums.begin(), nums.begin() + K);
    //https://en.cppreference.com/w/cpp/iterator/next
    //Return the nth successor of iterator it.
    multiset<int>::iterator upper_median = next(BoundedBST.begin(), K / 2);
    vector<double> medians;
    for (int i=K; ; i++) {
      if (K&1)
        medians.push_back(double(*upper_median));
      else
        medians.push_back((double(*upper_median) + *prev(upper_median)) / 2);
      if (i == nums.size())
        return medians;
      // insert nums[i]
      BoundedBST.insert(nums[i]);
      if (nums[i] < *upper_median) upper_median--; // ???
      if (nums[i-K] <= *upper_median) upper_median++; // ???
      // erase nums[i-K]
      int t = nums[i-K];
      BoundedBST.erase(BoundedBST.find(t)); // how to erase element from multiset BST
    }
    return medians;
  }
};

void test(){
  Solution sln;
  VI vi = {1,3,-1,-3,5,3,6,7};
  assert(sln.medianSlidingWindow(vi, 3) == vector<double>({1,-1,-1,3,5,6}));
}

}

#endif //PNSEI_480_SLIDING_WINDOW_MEDIAN_H
