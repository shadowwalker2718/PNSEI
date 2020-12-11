//
// Created by Henry Wu on 11/18/18.
//

#ifndef PNSEI_464_CAN_I_WIN_H
#define PNSEI_464_CAN_I_WIN_H

#include "pnsei.h"

// https://leetcode.com/problems/can-i-win/
// https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
//
namespace _464 {
struct Solution { // 109 ms, beat 89%
  bool miniMax(int state, unordered_map<int, bool> &dp, int goal, int maxn) {
    if (dp.count(state)) return dp[state];
    for (int i = maxn - 1; i >= 0; i--)
      if (state & (1 << i)) {
        if (i + 1 >= goal) {
          //cout << i << endl;
          return dp[state] = true;
        }
        if (!miniMax(state ^ (1 << i), dp, goal - i - 1, maxn))
          return dp[state] = true;
      }
    return dp[state] = false;
  }

  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (maxChoosableInteger >= desiredTotal) return true;
    if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) return false;
    int state = (1 << maxChoosableInteger) - 1; //(1==available)
    unordered_map<int, bool> dp(desiredTotal);
    return miniMax(state, dp, desiredTotal, maxChoosableInteger);
  }
};

void test() {
  Solution sln;
  assert(sln.canIWin(5, 12));
}
}

#endif //PNSEI_464_CAN_I_WIN_H
