//
// Created by Henry Wu on 11/2/18.
//

#ifndef PNSEI_307_RANGE_SUM_QUERY_MUTABLE_H
#define PNSEI_307_RANGE_SUM_QUERY_MUTABLE_H

#include "pnsei.h"

// https://leetcode.com/problems/range-sum-query-mutable/description/

namespace _307_segmentTree {

class NumArray {
  vector<int> v;
  int L = 0;

  void build_segtree(vector<int> &nums) {
    L = nums.size();
    v.resize(L * 2);
    for (int i = 0; i < L; i++)
      v[i + L] = nums[i];
    for (int i = L - 1; i > 0; i--)
      v[i] = v[i << 1] + v[(i << 1) + 1];
  }

  int rec(int ti, int tj) {
    if (ti > tj) return 0; //////////////////// edge case: ti=3, tj=4; ti=4, tj=5
    if (ti == tj) return v[ti];
    int extra = 0;
    if (ti & 1) // tree index ti odd, right child
      extra += v[ti++];
    if ((tj & 1) == 0) // tree index tj even, left child
      extra += v[tj--];
    return extra + rec(ti / 2, tj / 2);
  }

public:
  NumArray(vector<int> nums) {
    build_segtree(nums);
  }

  void update(int i, int val) {
    int tree_index = L + i;
    int delta = val - v[tree_index];
    while (tree_index > 0) {
      v[tree_index] += delta;
      tree_index >>= 1;
    }
  }

  int sumRange(int i, int j) {
    if (i > j) return INT_MIN;
    int tree_i = i + L, tree_j = j + L;
    return rec(tree_i, tree_j);
  }

  int sumRange_iterative(int i, int j) {
    if (i > j) return INT_MIN;
    int tree_i = i + L, tree_j = j + L;
    int r=0, extra=0;
    while(tree_i < tree_j){
      if(tree_i&1) extra+=v[tree_i++];
      if(tree_j%2==0) extra+=v[tree_j--];
      tree_i/=2, tree_j/=2;
    }
    /* for example, tree_i=3 and tree_j=4, it is like: \ /, so it will become tree_i=4 and tree_j=3 */
    return extra + (tree_i==tree_j?v[tree_i]:0);////////////
  }
};

void test() {
  vector<int> vi = {1, 2, 3, 4, 5};
  NumArray na(vi);
  assert(na.sumRange(2, 4) == 12);
  assert(na.sumRange(0, 4) == 15);
  assert(na.sumRange_iterative(2, 4) == 12);
  assert(na.sumRange_iterative(0, 4) == 15);
}

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

};

#endif //PNSEI_307_RANGE_SUM_QUERY_MUTABLE_H
