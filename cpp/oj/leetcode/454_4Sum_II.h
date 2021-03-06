//
// Created by Henry Wu on 11/17/18.
//

#ifndef PNSEI_454_4SUM_II_H
#define PNSEI_454_4SUM_II_H

/* https://leetcode.com/problems/4sum-ii/
 *
 * Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that
 * A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in
 the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

Example:

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 *
 * */
#include "pnsei.h"
namespace _454{
class Solution {
public:
  int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D){ //O(N^2)
    int ret = 0;
    unordered_map<int, int> m;
    for(auto a : A)
      for(auto b : B)
        m[a + b]++;
    for(auto c : C)
      for(auto d : D)
        ret += m[-(c + d)];
    return ret;
  }

};
}

#endif //PNSEI_454_4SUM_II_H
