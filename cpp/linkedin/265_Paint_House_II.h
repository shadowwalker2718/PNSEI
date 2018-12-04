//
// Created by Henry Wu on 12/4/18.
//

#ifndef PNSEI_265_PAINT_HOUSE_II_H
#define PNSEI_265_PAINT_HOUSE_II_H

#include "henry.h"

namespace _265 {

//
// Trick: find the minimum except itself in a array with ONE SCAN
// https://leetcode.com/problems/paint-house-ii/
//
struct Solution {
  int minCostII(vector<vector<int>> &costs) {
    if (costs.empty() || costs[0].empty())
      return 0;
    int R = costs.size(), C = costs[0].size();
    for (int i = 1; i < R; i++) {
      // 如何找数列的最小和次小元素.
      // Find the 1st and 2nd smallest cell in previous costs.
      pair<int, int> prev_min(-1, INT_MAX), prev_sec(-1, INT_MAX); // {index, cost}
      int mi = INT_MAX;
      for (int j = 0; j < C; j++) {
        if (costs[i - 1][j] < prev_min.second)
          prev_sec = prev_min, prev_min = {j, costs[i - 1][j]};
        else if (costs[i - 1][j] < prev_sec.second)
          prev_sec = {j, costs[i - 1][j]};
      }
      for (int j = 0; j < C; j++)
        costs[i][j] += (prev_min.first == j) ? prev_sec.second : prev_min.second;
    }
    int r = INT_MAX;
    for (int j = 0; j < C; j++) r = min(r, costs[R - 1][j]);
    return r;
  }
};

#endif //PNSEI_265_PAINT_HOUSE_II_H
