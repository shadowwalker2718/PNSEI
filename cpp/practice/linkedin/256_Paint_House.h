//
// Created by Henry Wu on 12/4/18.
//

#ifndef PNSEI_256_PAINT_HOUSE_H
#define PNSEI_256_PAINT_HOUSE_H

#include "henry.h"

namespace _256{

/*
https://leetcode.com/problems/paint-house/

There are a row of n houses, each house can be painted with one of the three colors: red, blue or green.
 The cost of painting each house with a certain color is different. You have to paint all the houses
 such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example,
 costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting
 house 1 with color green, and so on... Find the minimum cost to paint all houses.

Note: All costs are positive integers.

https://segmentfault.com/a/1190000003903965

复杂度
时间  O(N∗3)  空间O(N∗3)

思路
 直到房子i,其最小的涂色开销是直到房子i-1的最小涂色开销,加上房子i本身的涂色开销.但是房子i的涂色方式需要根据房子i-1的涂色方式来确定,
 所以我们对房子i-1要记录涂三种颜色分别不同的开销,这样房子i在涂色的时候,我们就知道三种颜色各自的最小开销是多少了.
 我们在原数组上修改,可以做到不用extra空间.
*/

struct Solution{

  int minCost_3byn_matrix(VVI costs){
    if(costs.empty() || costs[0].empty()) return 0;
    int R=costs.size(), C=costs[0].size(); // we know C is 3 here
    REP(i,1,C){
      costs[0][i] += min(costs[1][i-1], costs[2][i-1]);
      costs[1][i] += min(costs[0][i-1], costs[2][i-1]);
      costs[2][i] += min(costs[0][i-1], costs[1][i-1]);
    }
    return min(min(costs[0].back(), costs[1].back()), costs[2].back());
  }

  int minCost(VVI costs){
    if(costs.empty() || costs[0].empty()) return 0;
    int R=costs.size(), C=costs[0].size(); // we know C is 3 here
    REP(i,1,R){
      costs[i][0] += min(costs[i-1][1], costs[i-1][2]);
      costs[i][1] += min(costs[i-1][0], costs[i-1][2]);
      costs[i][2] += min(costs[i-1][0], costs[i-1][1]);
    }
    return *min_element(costs.back().begin(), costs.back().end());
  }

  VI minCost_path(VVI costs){
    if(costs.empty() || costs[0].empty()) return 0;
    int R=costs.size(), C=costs[0].size(); // we know C is 3 here
    REP(i,1,R){
      costs[i][0] += min(costs[i-1][1], costs[i-1][2]);
      costs[i][1] += min(costs[i-1][0], costs[i-1][2]);
      costs[i][2] += min(costs[i-1][0], costs[i-1][1]);
    }
    auto it=min_element(costs.back().begin(), costs.back().end());
    VI path(R);
    path[R-1] = it - costs.back().begin(); // index of minimum, aka color
    for(int i=R-2; i>=0; i--){
      int mi = INT_MAX;
      for(int j=0; j<C; j++){
        if(j==path[i+1]) continue;
        if(mi>costs[i][j]){
          mi = costs[i][j], path[i]=j;
        }
      }
    }
    return path;
  }
};


void test(){
  VVI v={{2,3,4},{3,1,2},{4,2,7},{5,6,3},{5,2,4},{3,4,1},{2,3,6},{2,5,1}};
  Solution sln;
  assert(sln.minCost_path(v) == VI{0,2,1,2,1,2,0,2});
}

#endif //PNSEI_256_PAINT_HOUSE_H
