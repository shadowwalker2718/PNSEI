//
// Created by henry on 11/11/18.
//

#ifndef PNSEI_304_RANGE_SUM_QUERY_2D_IMMUTABLE_H
#define PNSEI_304_RANGE_SUM_QUERY_2D_IMMUTABLE_H

#include "henry.h"
namespace _304 {
/*

 https://leetcode.com/problems/range-sum-query-2d-immutable/discuss/75350/Clean-C++-Solution-and-Explaination-O(mn)-space-with-O(1)-time

 To calculate sums, the ideas as below

+-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
|     | |       |     |        |     |     |     |         |     |     |        |
|     | |       |     |        |     |     |     |         |     |     |        |
+-----+-+       |     +--------+     |     |     |         |     +-----+        |
|     | |       |  =  |              |  +  |     |         |  -  |              |
+-----+-+       |     |              |     +-----+         |     |              |
|               |     |              |     |               |     |              |
|               |     |              |     |               |     |              |
+---------------+     +--------------+     +---------------+     +--------------+

   sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +

                        matrix[i-1][j-1]
So, we use the same idea to find the specific area's sum.

+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
|               |   |         |    |   |   |           |   |         |    |   |   |          |
|   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
|   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
|   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
|   |      |    |   |         |    |   |   |           |   |              |   |              |
|   +------+    |   +---------+    |   +---+           |   |              |   |              |
|        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+


 * */

class NumMatrix {
private:
  int row, col;
  vector<vector<int>> sums;

public:
  NumMatrix(vector<vector<int>> matrix) {
    row = matrix.size();
    col = row > 0 ? matrix[0].size() : 0;
    sums = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));
    for (int i = 1; i <= row; i++) {
      for (int j = 1; j <= col; j++) {
        sums[i][j] = matrix[i - 1][j - 1] + sums[i - 1][j] + sums[i][j - 1] -
                     sums[i - 1][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1] -
           sums[row1][col2 + 1] + sums[row1][col1];
  }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */
} // namespace _304

#endif // PNSEI_304_RANGE_SUM_QUERY_2D_IMMUTABLE_H
