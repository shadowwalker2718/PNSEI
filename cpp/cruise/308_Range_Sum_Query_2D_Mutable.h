//
// Created by root on 11/7/18.
//

#ifndef PNSEI_308_RANGE_SUM_QUERY_2D_MUTABLE_H
#define PNSEI_308_RANGE_SUM_QUERY_2D_MUTABLE_H

/*
https://leetcode.com/problems/range-sum-query-2d-mutable/description/

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D

The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
*/

#include "henry.h"

namespace _308{

// http://www.cnblogs.com/grandyang/p/5300458.html

namespace _column_sum{
// Column Sum
class NumMatrix {
public:
  NumMatrix(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    mat = matrix;
    colSum.resize(matrix.size() + 1, vector<int>(matrix[0].size(), 0));
    for (int i = 1; i < colSum.size(); ++i) { // row major traversal
      for (int j = 0; j < colSum[0].size(); ++j) {
        colSum[i][j] = colSum[i - 1][j] + matrix[i - 1][j];
      }
    }
  }

  void update(int row, int col, int val) { // O(C)
    for (int i = row + 1; i < colSum.size(); ++i) {
      colSum[i][col] += val - mat[row][col];
    }
    mat[row][col] = val;
  }

  int sumRegion(int row1, int col1, int row2, int col2) { // O(C)
    int res = 0;
    for (int j = col1; j <= col2; ++j) {
      res += colSum[row2 + 1][j] - colSum[row1][j];
    }
    return res;
  }

private:
  vector<vector<int>> mat;
  vector<vector<int>> colSum;
};
}


namespace _bit{
// Binary Indexed Tree
class NumMatrix {
public:
  NumMatrix(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    mat.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
    bit.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[i].size(); ++j) {
        update(i, j, matrix[i][j]);
      }
    }
  }

  void update(int row, int col, int val) { // O(LogR* LogC)
    int diff = val - mat[row + 1][col + 1];
    for (int i = row + 1; i < mat.size(); i += i&-i) {
      for (int j = col + 1; j < mat[i].size(); j += j&-j) {
        bit[i][j] += diff;
      }
    }
    mat[row + 1][col + 1] = val;
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return getSum(row2 + 1, col2 + 1) - getSum(row1, col2 + 1) - getSum(row2 + 1, col1) + getSum(row1, col1);
  }

  int getSum(int row, int col) { // O(LogR * LogC)
    int res = 0;
    for (int i = row; i > 0; i -= i&-i) {
      for (int j = col; j > 0; j -= j&-j) {
        res += bit[i][j];
      }
    }
    return res;
  }

private:
  vector<vector<int>> mat;
  vector<vector<int>> bit;
};

}

namespace _segment_tree{

}


}


#endif //PNSEI_308_RANGE_SUM_QUERY_2D_MUTABLE_H
