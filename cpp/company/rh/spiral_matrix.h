#ifndef PNSEI_SPIRAL_MATRIX_H
#define PNSEI_SPIRAL_MATRIX_H

#include "pnsei.h"

struct Solution {
  vector<int> spiralOrder(const vector<vector<int>>& matrix) {
    vector<int> r;
    if (matrix.empty() || matrix[0].empty())
      return r;
    int R = matrix.size(), C = matrix[0].size();
    bool odd = (R & 1) || (C & 1);
    // peel it layer by layer, i in the layer number
    for (int i = 0; i<(min(R, C) + (int)odd) / 2; ++i) { // i+1是剥掉的层数,i=0是剥第一层
      for (int j = i; j<C - i; ++j) // (1)=>
        r.push_back(matrix[i][j]);
      for (int j = i + 1; j<R - 1 - i; ++j) // (2)down
        r.push_back(matrix[j][C - 1 - i]);
      if (R - 1 - i != i) { // avoid duplicate with (1)
        for (int j = C - 1 - i; j >= i; --j) // <<==
          r.push_back(matrix[R - 1 - i][j]); }
      if (C - 1 - i != i) {// avoid duplicate with (2)
        for (int j = R - 2 - i; j>i; --j) // up
          r.push_back(matrix[j][i]);
      }
    }
    return r;
  }
};

#endif // PNSEI_SPIRAL_MATRIX_H
