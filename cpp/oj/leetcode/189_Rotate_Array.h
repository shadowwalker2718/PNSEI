//
// Created by Henry Wu on 11/19/18.
//

#ifndef PNSEI_189_ROTATE_ARRAY_H
#define PNSEI_189_ROTATE_ARRAY_H

#include "pnsei.h"

// https://leetcode.com/problems/rotate-array/

namespace _189{

class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    k %= nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin()+k);
    reverse(nums.begin()+k, nums.end());
  }
};


/*public class Solution {
public void rotate(int[] nums, int k) {
    k = k % nums.length;
    int count = 0;
    for (int start = 0; count < nums.length; start++) {
      int current = start;
      int prev = nums[start];
      do {
        int next = (current + k) % nums.length;
        int temp = nums[next];
        nums[next] = prev;
        prev = temp;
        current = next;
        count++;
      } while (start != current);
    }
  }
}*/
}

#endif //PNSEI_189_ROTATE_ARRAY_H
