//
// Created by Henry Wu on 11/16/18.
//

#ifndef PNSEI_200_NUMBER_OF_ISLANDS_H
#define PNSEI_200_NUMBER_OF_ISLANDS_H

// https://leetcode.com/problems/number-of-islands/description/
#include "pnsei.h"
namespace _200{
/*
 *
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are all
 * surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1


Example 2:

Input:
11000
11000
00100
00011

Output: 3
 *
 * */

struct Solution {
  //DFS iterative version
  int numIslands(vector<vector<char>>& grid) {
    int r = 0;
    if (grid.empty() || grid[0].empty()) return r;
    const vector<pair<int, int>> D = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
    int R = grid.size(), C = grid[0].size();
    vector<vector<bool>> visited(R, vector<bool>(C));
    for(int i=0;i<R;i++){
      for(int j=0;j<C;j++){
        if (visited[i][j] || grid[i][j]=='0'){ continue; }
        stack<pair<int, int>> stk;
        stk.emplace(i,j), visited[i][j]=true;
        while (!stk.empty()) {
          auto p = stk.top(); stk.pop();
          for (auto d : D) {
            int x = p.first + d.first, y = p.second + d.second;
            if (x >= 0 && x < R && y >= 0 && y < C && !visited[x][y]) {
              if (grid[x][y]=='1')
                stk.emplace(x, y), visited[x][y] = true;
            }
          }
        }
        r++;
      }
    }
    return r;
  }
};
}

#endif //PNSEI_200_NUMBER_OF_ISLANDS_H
