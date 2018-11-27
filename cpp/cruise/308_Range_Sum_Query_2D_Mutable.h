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


namespace _BIT{
// Binary Indexed Tree
class NumMatrix {
  void update(int row, int col, int val) { // O(LogR* LogC)
    int diff = val - mat[row + 1][col + 1];
    for (int i = row + 1; i < mat.size(); i += i&-i) {
      for (int j = col + 1; j < mat[i].size(); j += j&-j) {
        bit[i][j] += diff;
      }
    }
    mat[row + 1][col + 1] = val;
  }
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
class NumMatrix {

public:
  NumMatrix(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    R = matrix.size();
    mat = matrix;
    segment_tree_2D.resize(R, vector<int>(C, 0));
    // build tree
    for (int i = R-1; i >= 1; --i) {
      for (int j = C-1; j >= 1; --j) {
        segment_tree_2D[i][j] = mat[2*i-R][j*2-C] + mat[2*i+1-R][j*2+1-C];
      }
    }
  }

  void update(int row, int col, int val) { // O(LogR* LogC)
    int inc = val - mat[row][col];
    mat[row][col] = val;
    int x=row+R;
    while(x>0){
      int y=col+C;
      while(y>0){
        segment_tree_2D[x/2][y/2]=mat[x/2*2-R][y/2*2-C] + mat[x/2*2+1-R][y/2*2+1-C];
        y/=2;
      }
      x/=2;
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    int r=0, extra=0;
    row1 += R, row2 += R;
    while(row1<row2){
      col1+=C, col2+=C;
      while(col1<col2){
        if(col1%2==1){
          if(row1%2==1){
            if(row1>=R){
              extra += (col1>=C)?mat[row1-R][col1-C]:segment_tree_2D[row1-R][col1];
            }else{
              extra += (col1>=C)?mat[row1][col1-C]:segment_tree_2D[row1][col1];
            }
            row1++;
          }
          col1++;
        }
        if(col2%2==0){
          if(row2%2==0){
            if(row2>=R){
              extra += (col2>=C)?mat[row2-R][col2-C]:segment_tree_2D[row2-R][col2];
            }else{
              extra += (col2>=C)?mat[row2][col2-C]:segment_tree_2D[row2][col2];
            }
            row2--;
          }
          col2--;
        }
        col1/=2, col2/=2;
      }
      r += (col1==col2?(segment_tree_2D[row1][col1]+segment_tree_2D[row2][col1]):0);
    }
    return 0;
  }


private:
  int R=0, C=0; // original matrix width M, height N
  VVI segment_tree_2D;
  VVI mat;
};
}


}


#endif //PNSEI_308_RANGE_SUM_QUERY_2D_MUTABLE_H
