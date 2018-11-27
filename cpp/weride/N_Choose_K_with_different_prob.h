//
// Created by Henry Wu on 11/24/18.
//

#ifndef PNSEI_N_CHOOSE_K_WITH_DIFFERENT_PROB_H
#define PNSEI_N_CHOOSE_K_WITH_DIFFERENT_PROB_H

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=312851
 * <<Probability>> Page 42
 *
2017(10-12月) 码农类General 硕士 全职@Jingchi - Other - 技术电面  | Fail | 在职跳槽
两道题.
1. 纵向打印tree.
      1
    /   \

   2     3

  / \   / \
  4  5  6  2
输出
4
2
156
3
7


2. Toss N个硬币,问有K个硬币get head的概率是多少.当时用dp做的.

挂了,第二问用dp没写明白.
噢噢补充一下哈.第二题面试官说每次硬币朝上的概率并不一定一样.是一个数组:P[1....n], 每次的概率为P[i]. 这样的话就不能用combination做了.
还是得DP或者递归.
F(N, k) = F(N - 1, k - 1) * P_k + F(N - 1, k) * (1 - P_k)
*/
#include "henry.h"
namespace _weride_prob{
struct Solution{
  VVD dp;
  double N_choose_K_with_different_prob(int n, int k, const VD& prob){
    assert(prob.size()>=n);

    dp=VVD(n+1, VD(k+1));
    /*build dp*/
    dp[0][0] = 1.0;
    REP(i,1,n+1){
      REP(j,0,k+1){
        if(i<j) continue;
        if(j==0){
          dp[i][0] = dp[i-1][0]*(1-prob[i-1]);
          continue;
        }
        dp[i][j] = dp[i-1][j-1]*prob[i-1] + dp[i-1][j]*(1-prob[i-1]);
      }
    }
    return dp[n][k];
  }
};

void test(){
  Solution sln;
  assert(sln.N_choose_K_with_different_prob(1,1,{0.6}) == 0.6);
  assert(sln.N_choose_K_with_different_prob(1,0,{0.6}) == 0.4);
  assert(sln.N_choose_K_with_different_prob(2,0,{0.6,0.4}) == 0.24);
  assert(sln.N_choose_K_with_different_prob(2,2,{0.6,0.4}) == 0.24);
  assert(sln.N_choose_K_with_different_prob(2,1,{0.6,0.4}) == 0.52);
  assert(sln.N_choose_K_with_different_prob(2,3,{0.6,0.4}) == 0.0);
}


}




#endif //PNSEI_N_CHOOSE_K_WITH_DIFFERENT_PROB_H
