//
// Created by henry on 10/22/18.
//
#include "pnsei.h"

#ifndef C_289_GAME_OF_LIFE_H
#define C_289_GAME_OF_LIFE_H

namespace _289 {

/*
 *
 * */

// https://leetcode.com/problems/game-of-life/
class Solution {
public:
  void gameOfLife(vector<vector<int>> &b) {
    if (b.empty() || b[0].empty())
      return;
    int R = b.size(), C = b[0].size();
    vector<vector<int>> dr = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                              {0, 1},   {1, -1}, {1, 0},  {1, 1}};

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        int c = 0;
        for (auto &v : dr) {
          int nx = i + v[0], ny = j + v[1];
          if (nx < 0 || nx >= R || ny < 0 || ny >= C)
            continue;
          if (b[nx][ny] & 1)
            c++;
        }
        if (b[i][j] == 1) {
          if (c < 2 || c > 3)
            b[i][j] &= 1;
          else
            b[i][j] |= 0b10;
        } else if (c == 3)
          b[i][j] |= 0b10;
      }
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        b[i][j] >>= 1;
      }
    }
  }
};

} // namespace _289

#endif // C_289_GAME_OF_LIFE_H
