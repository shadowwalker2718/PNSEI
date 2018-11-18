//
// Created by root on 11/17/18.
//

#ifndef PNSEI_944_DELETE_COLUMNS_TO_MAKE_SORTED_H
#define PNSEI_944_DELETE_COLUMNS_TO_MAKE_SORTED_H

/*
 * We are given an array A of N lowercase letter strings, all of the same length.

Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.

For example, if we have a string "abcdef" and deletion indices {0, 2, 3}, then the final string after deletion is "bef".

Suppose we chose a set of deletion indices D such that after deletions, each remaining column in A is in non-decreasing sorted order.

Formally, the c-th column is [A[0][c], A[1][c], ..., A[A.length-1][c]]

Return the minimum possible value of D.length.



Example 1:

Input: ["cba","daf","ghi"]
Output: 1

Example 2:

Input: ["a","b"]
Output: 0

Example 3:

Input: ["zyx","wvu","tsr"]
Output: 3

 * */
#include "henry.h"
namespace _944{
class Solution {
public:
  int minDeletionSize(vector<string>& A) {
    // transpose Matrix
    vector<string> s(A.front().size(), string(A.size(), ' '));
    for (int r = 0; r < A.size(); ++r) {
      for (int c = 0; c < A[r].size(); ++c) {
        s[c][r] = A[r][c];
      }
    }
    // count un_sorted rows
    return count_if(s.begin(), s.end(), [](auto & p) {
      return !is_sorted(p.begin(), p.end());
    });
  }
};
}

}

#endif //PNSEI_944_DELETE_COLUMNS_TO_MAKE_SORTED_H
