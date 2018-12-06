//
// Created by Henry Wu on 12/5/18.
//

#ifndef PNSEI_255_VERIFY_PREORDER_SEQUENCE_IN_BINARY_SEARCH_TREE_H
#define PNSEI_255_VERIFY_PREORDER_SEQUENCE_IN_BINARY_SEARCH_TREE_H

/* https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/ */
/* https://leetcode.com/problems/validate-binary-search-tree/description/ */

#include "henry.h"

namespace _255{

class Solution {
public:
  bool verify(vector<int> &nums, int i, int j, int min, int max) {
    if (i > j)
      return true;
    int R = nums[i]; // first node, Root node
    if (R < min || R > max)
      return false;

    int m = i + 1;
    while (m <= j && nums[m] <= R)
      m++;

    return (verify(nums, i+1, m-1, min, R) &&
            verify(nums, m, j, R, max));
  }

  bool verifyPreorder(vector<int> &preorder) {
    int N = preorder.size();
    return (verify(preorder, 0, N-1, INT_MIN, INT_MAX));
  }
};



}

#endif //PNSEI_255_VERIFY_PREORDER_SEQUENCE_IN_BINARY_SEARCH_TREE_H
