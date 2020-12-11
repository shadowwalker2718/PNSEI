#pragma once

#include "pnsei.h"

namespace _407 {

class Solution {
public:
  int trapRainWater(vector<vector<int>> &hs) {
    int ROW = hs.size();
    if (ROW <= 2)
      return 0;
    int COL = hs[0].size();
    vector<vector<int>> lm(ROW, vector<int>(COL, 0)), rm = lm, fm = lm, bm = lm;
    for (int i = 0, tmax = 0; i < ROW; ++i, tmax = 0)
      for (int j = 0; j < COL; ++j)
        lm[i][j] = tmax = max(tmax, hs[i][j]);
    for (int i = 0, tmax = 0; i < ROW; ++i, tmax = 0)
      for (int j = COL - 1; j >= 0; --j)
        rm[i][j] = tmax = max(tmax, hs[i][j]);
    for (int j = 0, tmax = 0; j < COL; ++j, tmax = 0)
      for (int i = 0; i < ROW; ++i)
        fm[i][j] = tmax = max(tmax, hs[i][j]);
    for (int j = COL - 1, tmax = 0; j >= 0; --j, tmax = 0)
      for (int i = ROW - 1; i >= 0; --i)
        bm[i][j] = tmax = max(tmax, hs[i][j]);
    int r = 0;
    for (int i = 1; i < ROW - 1; ++i)
      for (int j = 1; j < COL - 1; ++j)
        r += min(max(0, min(lm[i][j], rm[i][j]) - hs[i][j]),
                 max(0, min(fm[i][j], bm[i][j]) - hs[i][j]));
    return r;
  }
};

class Solution2 {
public:
  int trapRainWater(vector<vector<int>> &heightMap) {
    if (heightMap.empty())
      return 0;
    int m = heightMap.size(), n = heightMap[0].size(), res = 0, mx = INT_MIN;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>> dir{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
          q.push({heightMap[i][j], i * n + j});
          visited[i][j] = true;
        }
      }
    }
    while (!q.empty()) {
      auto t = q.top();
      q.pop();
      int h = t.first, r = t.second / n, c = t.second % n;
      mx = max(mx, h);
      for (int i = 0; i < dir.size(); ++i) {
        int x = r + dir[i][0], y = c + dir[i][1];
        if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y])
          continue;
        visited[x][y] = true;
        if (heightMap[x][y] < mx)
          res += mx - heightMap[x][y];
        q.push({heightMap[x][y], x * n + y});
      }
    }
    return res;
  }
};

struct customLess {
  bool operator()(int *a, int *b) { return a[2] > b[2]; }
};
class Solution3 { // 46 lines, 49 ms, 96%
public:
  priority_queue<int *, vector<int *>, customLess> pq;
  int dfs(vector<vector<int>> &map, vector<vector<int>> &visited, int i, int j,
          int h, int st) {
    int r = map.size(), c = map[0].size();
    if (i >= r || i < 0 || j > c - 1 || j < 0 || (visited[i][j] && st != 0))
      return 0;
    visited[i][j] = 1;
    if (map[i][j] > h) {
      pq.push(new int[3]{i, j, map[i][j]});
      return 0;
    }
    return dfs(map, visited, i + 1, j, h, 1) +
           dfs(map, visited, i, j + 1, h, 1) +
           dfs(map, visited, i - 1, j, h, 1) +
           dfs(map, visited, i, j - 1, h, 1) + h - map[i][j];
  }
  int trapRainWater(vector<vector<int>> &heightMap) {
    if (heightMap.size() < 3 || heightMap[0].size() < 3)
      return 0;
    vector<int> tmpv(heightMap[0].size(), 0);
    vector<vector<int>> visited(heightMap.size(), tmpv);
    int r = heightMap.size(), c = heightMap[0].size(), i, j, k, rst = 0;
    int *tmp, *tmp2;
    for (i = 0; i < r; i++) {
      tmp = new int[3];
      tmp[0] = i, tmp[1] = 0, tmp[2] = heightMap[i][0];
      pq.push(tmp);
      tmp = new int[3];
      tmp[0] = i, tmp[1] = c - 1, tmp[2] = heightMap[i][c - 1];
      pq.push(tmp);
    }
    for (j = 1; j < c - 1; j++) {
      tmp = new int[3]{0, j, heightMap[0][j]};
      // tmp[0]=0,tmp[1]=j,tmp[2]=heightMap[0][j];
      pq.push(tmp);
      tmp = new int[3];
      tmp[0] = r - 1, tmp[1] = j, tmp[2] = heightMap[r - 1][j];
      pq.push(tmp);
    }
    while (!pq.empty()) {
      tmp2 = pq.top(), pq.pop();
      rst += dfs(heightMap, visited, tmp2[0], tmp2[1], tmp2[2], 0);
      delete[] tmp2;
    }
    return rst;
  }
};

void test() {
  Solution2 sln;
  vector<vector<int>> vvi = {
      {1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
  assert(sln.trapRainWater(vvi) == 4);

  vvi = {{12, 13, 1, 12},
         {13, 4, 13, 12},
         {13, 8, 10, 12},
         {12, 13, 12, 12},
         {13, 13, 13, 13}};
  assert(sln.trapRainWater(vvi) == 14);
}

} // namespace _407
