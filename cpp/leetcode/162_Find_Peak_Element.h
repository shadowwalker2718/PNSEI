//
// Created by Henry Wu on 11/3/18.
//

#ifndef PNSEI_162_FIND_PEAK_ELEMENT_H
#define PNSEI_162_FIND_PEAK_ELEMENT_H

#include "henry.h"

/*
 *
 * A peak element is an element that is greater than its neighbors.

Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that nums[-1] = nums[n] = -∞.

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5
Explanation: Your function can return either index number 1 where the peak element is 2,
             or index number 5 where the peak element is 6.
 *
 * */

// https://leetcode.com/problems/find-peak-element/description/
namespace _162{
    int findPeakElement(vector<int>& nums) {
        int h=0, t=nums.size()-1;
        while(h<t){
            int m=h+(t-h)/2; // lower median
            if(nums[m] > nums[m+1]){
                t=m;
            }else h=m+1;
        }// h==t
        return h;
    }

    void test(){
        VI v={1,2,3,1};
        assert(findPeakElement(v)==2);
        v={1,2,1,3,5,6,4};
        int r=findPeakElement(v);
        assert(r==2 || r==5);
    }
}

#endif //PNSEI_162_FIND_PEAK_ELEMENT_H
