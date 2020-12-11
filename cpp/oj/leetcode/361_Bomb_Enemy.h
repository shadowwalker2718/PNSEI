#pragma once
#include "pnsei.h"

namespace _361 {
class Solution {
public:
  int maxKilledEnemies(vector<string> &g) {
    if (g.empty() || g[0].empty())
      return 0;                                      //
    int ROW = g.size(), COL = g[0].size();           //
    vector<vector<int>> c(ROW, vector<int>(COL, 0)); // counter

    int r = 0, tmp = 0, i = 0, j = 0;
    auto f = [&](int i, int j) {
      if ('0' == g[i][j]) {
        c[i][j] += tmp, r = max(r, c[i][j]);
      } else if ('W' == g[i][j]) {
        tmp = 0;
      } else {
        tmp++;
      }
    };
    for (i = tmp = 0; i < ROW; i++)
      for (j = tmp = 0; j < COL; j++)
        f(i, j);
    for (i = tmp = 0; i < ROW; i++)
      for (j = COL - 1; j >= 0; j--)
        f(i, j);
    for (j = tmp = 0; j < COL; j++)
      for (i = 0; i < ROW; i++)
        f(i, j);
    for (j = tmp = 0; j < COL; j++)
      for (i = ROW - 1; i >= 0; i--)
        f(i, j);
    return r;
  }
};

void test() {
  vector<string> g = {"0E00", "E0WE", "0E00"};
  Solution sln;
  assert(sln.maxKilledEnemies(g) == 3);
}
} // namespace _361