#ifndef PNSEI_41_FIRST_MISSING_POSITIVE_H
#define PNSEI_41_FIRST_MISSING_POSITIVE_H

#include "pnsei.h"

namespace _41{
/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
Follow up:

Your algorithm should run in O(n) time and uses constant extra space.
*/
struct Solution {
  // edge case: INT_MIN
  int firstMissingPositive(vector<int> nums) {
    if(nums.empty())
      return 1;

    for(int i=0;i<nums.size();++i){
      while(nums[i]>0 // INT_MIN
             && nums[i]-1<nums.size()
             && nums[i]-1!=i
             && nums[i]!=nums[nums[i]-1]) // avoid infinite loop
        swap(nums[i], nums[nums[i]-1]);
    }
    for(int i=0; i<nums.size(); ++i)
      if(i+1!=nums[i])
        return i+1;
    return nums.size()+1;
  }

};

}

#endif // PNSEI_41_FIRST_MISSING_POSITIVE_H
