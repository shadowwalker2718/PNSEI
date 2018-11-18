//
// Created by root on 11/18/18.
//

#ifndef PNSEI_464_CAN_I_WIN_H
#define PNSEI_464_CAN_I_WIN_H

#include "henry.h"

// https://leetcode.com/problems/can-i-win/
// https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
//
namespace _464{
struct Solution { // 109 ms, beat 89%
  bool miniMax(int state, unordered_map<int,bool> &dp, int goal, int maxn){
    if(dp.count(state)) return dp[state];//该状态已经被搜索过
    for(int i=maxn-1; i>=0; i--)//遍历每个数字
      if(state&(1<<i)){ //如果它还没被使用getbit(i)==1
        //如果当前已经能实现目标,或对方接下来不能赢.(异或把该位变0表示使用该数字)
        if(i+1>=goal){
          cout << i << endl;
          return dp[state] = true;
        }
        if(!miniMax(state^(1<<i),dp,goal-i-1,maxn))
          return dp[state] = true;
      }
    return dp[state] = false;
  }
  bool canIWin(int maxChoosableInteger, int desiredTotal){
    if(maxChoosableInteger>=desiredTotal) return true;
    if(maxChoosableInteger*(maxChoosableInteger+1)/2<desiredTotal) return false;
    int state = (1 << maxChoosableInteger) - 1; //初始状态为全1即全部数字都可用(1==available)
    unordered_map<int,bool> dp(desiredTotal);//记录状态,dp[i]表示当前可用数为i,目标为goal时能不能赢
    return miniMax(state, dp, desiredTotal, maxChoosableInteger);
  }
};

void test(){
  Solution sln;
  assert(sln.canIWin(5,12));
}
}

#endif //PNSEI_464_CAN_I_WIN_H
