#pragma once
#include "pnsei.h"

namespace _knighttour {
#define valid(x, y) (int)(x >= 0 && y >= 0 && x < R && y < C)
vector<pair<int, int>> dirs = {{-1, -2}, {-2, -1}, {1, 2},  {2, 1},
                               {-1, 2},  {2, -1},  {1, -2}, {-2, 1}};

map<pair<int, int>, int> m; // position to num
int getnum(int R, int C, int x, int y) {
  if (m.count({x, y}))
    return m[{x, y}];
  int r = 0;
  for (auto pr : dirs)
    r += valid(x + pr.first, y + pr.second);
  return m[{x, y}] = r;
}

int dfs(int R, int C, int x, int y, int k) {
  if (k == 1)
    return getnum(R, C, x, y);
  int r = 0;
  for (auto pr : dirs) {
    int nx = x + pr.first, ny = y + pr.second;
    if (valid(nx, ny)) {
      int tmp = dfs(R, C, nx, ny, k - 1);
      r += tmp;
    }
  }
  return r;
}
void test() {
  assert(dfs(8, 8, 0, 0, 1) == 2);
  assert(dfs(8, 8, 4, 4, 2) == 56);
  assert(dfs(8, 8, 1, 0, 1) == 3);
  assert(dfs(8, 8, 2, 2, 1) == 8);
  assert(dfs(8, 8, 1, 0, 4) == 628);
  assert(dfs(8, 8, 4, 4, 4) == 1978);
}
}