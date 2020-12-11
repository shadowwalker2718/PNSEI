#pragma once

#include "pnsei.h"

namespace _sparsematrix {

// 符合条件的最小的sparse matrix
vector<vector<int>> csr2dense(vector<int> &rptr, vector<int> &cidx,
                              vector<int> &val) {
  int ROW = rptr.size() - 1, COL = *max_element(cidx.begin(), cidx.end()) + 1;
  vector<vector<int>> r(ROW, vector<int>(COL));
  int ri = 0;
  for (int i = 0; i < ROW; ++i)
    for (int j = rptr[i]; j < rptr[i + 1]; ++j)
      r[i][cidx[j]] = val[j];
  return r;
}

void test() {
  vector<vector<int>> r = {
      {1, 0, 5, 0}, {2, 3, 0, 0}, {4, 0, 0, 1}, {0, 0, 2, 0}};

  vector<int> rptr = {0, 2, 4, 6, 7};
  vector<int> cidx = {0, 2, 0, 1, 0, 3, 2};
  vector<int> val = {1, 5, 2, 3, 4, 1, 2};
  assert(csr2dense(rptr, cidx, val) == r);
}

} // namespace _sparsematrix
