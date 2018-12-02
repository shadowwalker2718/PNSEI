//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_POSTOFFICE_H
#define PNSEI_POSTOFFICE_H

#include "henry.h"

namespace _weride_kmeans {

// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=314760&extra=&highlight=jingchi&page=1

/*
1. 一维直线上有若干村庄,能够建若干个仓库,每个村庄的cost为距离其最近的仓库到它距离的平方,求最小cost总和

设村庄数目为n,表示为V1, ..., Vn,且不妨设V1 <= ... <= Vn
设仓库数目为m,表示为W1, ..., Wm
首先考虑m = 1的情况,也就是只有一个仓库.那么问题就是求W1的值,使得

 (V1 - W1)^2 + ... + (Vn - W1)^2

的值最小.

使用微积分的知识我们可以知道当

W1 = (V1 + ... + Vn) / n

时 —— 也就是W1是所有村庄中点时 —— 上面的表达式有最小值.

现在考虑有多个仓库的情况,这等价于将V1, ..., Vn划分成m个区间,使Wi取值为第i个区间的中点,求cost最小的划分方案

那么就是动态规划了,定义:
dp(k, u) = 前k个村庄放置u个仓库的最小cost
C(i, j) = 将仓库建在Vi, ..., Vj中点处的cost,这个值可以O(j-i+1)时间内计算出来

那么状态转移方程:
dp(k, 1) = C(1, k)
dp(k, u) = min( dp(k-1, u-1) + C(k, k),
                dp(k-2, u-1) + C(k-1, k),
               ...
             )

时间复杂度O(m * n * n) —— 不确定还有没有进一步优化
空间复杂度O(n) —— 使用滚动数组的话
// http://web.engr.oregonstate.edu/~xfern/classes/cs434/slides/clustering2-16.pdf
// https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5148156/#!po=95.5882
----------------------------------------------------------------------------------------------------
xbbjames1 发表于 2018-2-6 14:39
兄弟, 你看了下你这个状态转移方程 我有一个问题啊? 当你选了S(k, u) = S(k-i, u-1) + Cost(k-i+1, k)  ...

> 这是个好问题,考虑动态规划算法给出的最优划分,实质上是如下问题的最优解:
将V1, ..., Vn划分成m个区间,使Wi取值为第i个区间的所有村庄位置的平均值,求cost最小的划分方案...

而你的意思是说,动态规划算法给出的"最优划分",是否会出现这样的情况:
存在两个区间S、T,其中S中的某个村庄（比起S自身的中值点)反而更靠近T的中值点.
答案是不可能有这样的情况,用反证法不妨设某些村庄离其他区间的中值点更近,那么我们做如下操作:
(1) 将这些村庄移入对应的距离最近的区间
(2) 调整受影响区间的中值重新计算cost
那么,(1)+(2)本质上是K-means算法的1D特例的一个iteration,可以证明cost一定是减小的（分别考虑(1)和(2),都是减小cost的;
或者可以看下这个ppt的Proof of monoticity那一页:http://web.engr.oregonstate.edu/ ... /clustering2-16.pdf)
这与动态规划给出的cost的最优性矛盾.
补充内容 (2018-2-7 14:58):
还搜到一篇文章就是讲的一模一样的状态转移方程（居然有100多引用..):
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5148156/#!po=95.5882
*/

class solution {
  vector<vector<double>> dp;

  // for one warehouse, villages from i to j(i<=j) clustering with it
  // the SOS is stored in costs[i][j], which is a Upper triangular matrix with diag=0
  // i and j are 1-based ordinal number, not 0-based index of array
  // inclusive
  vector<vector<double>> costs; // MSE matrix
  int L = 0; // # of villages
  int W = 0; // # of warehouses
  VI villages;

  // C(i, j) = 将仓库建在Vi, ..., Vj中点处的cost
  // Can be optimized with partial_sum
  void build_costmatrix_with_one_centroid() { // O(L^3)
    //VI ps(villages);
    //partial_sum(ps.begin(), ps.end(), ps.begin());
    REP(i, 1, L + 1) {
      REP(j, i + 1, L + 1) {
        double sum = 0.0;
        REP(k, i, j + 1) { // could be O(1)
          sum += villages[k - 1];
        }
        double centroid = sum / (j - i + 1); //!!
        REP(k, i, j + 1) {
          double distance = villages[k - 1] - centroid;
          costs[i][j] += distance * distance;
        }
      }
    }
  }

  // dp[x][y] means MSE of clustering x villages with y warehouses
  void build_dp() { // O(L^2)
    //init dp and bootstrap dp[k][1]
    fill(dp[0].begin(), dp[0].end(), 0.);
    REP(i, 1, L + 1) {
      dp[i][1] = costs[1][i];
    }
    REP(x, 1, L + 1) { // # villages
      REP(y, 2, W + 1) { // # warehouses
        if (x <= y) {
          dp[x][y] = 0.0;
          continue;
        }
#if DEBUG
        double sos = numeric_limits<double>::max(), prev, co, mz;
        // z is the # of villages clustering with the last warehouse
        REP(z, 1, x + 1) {
          double t=dp[x - z][y - 1] + costs[x - z + 1][x];
          if(sos > t){
            sos = t, mz=z, co=costs[x - z + 1][x], prev=dp[x - z][y - 1];
          }
        }
        cout << "x:" << x << ",y:" << y
        << ",#clustered/w/last:" << mz
        << ",sos:" << sos << ",(prev=" << prev
        << ",co=" << co << ")" << endl;
#else
        double sos = numeric_limits<double>::max();
        // z is the # of villages clustering with the last warehouse
        REP(z, 1, x + 1) {
          sos = min(sos, dp[x - z][y - 1] + costs[x - z + 1][x]); //!!
        }
#endif
        dp[x][y] = sos;
      }
    }
  }

public:
  explicit solution(const VI &villages_, int m_) {
    villages = villages_;
    W = m_;
    L = villages_.size();
    dp = vector<vector<double>>(L + 1, vector<double>(W + 1, INT_MAX));
    costs = VVD(L + 1, VD(L + 1, 0.0));
  }

  double SOS() { // sum of square
    build_costmatrix_with_one_centroid();
    build_dp();
    return dp[L][W];
  }
};


void test() {
  VI villages = {1, 2, 3, 6, 7, 9, 11, 22, 44, 50};
  int m = 5;
  assert(solution(villages, m).SOS()==16.75);

  villages = {6,7,9,11};
  assert(solution(villages, 1).SOS()==14.75);
};
}

#endif //PNSEI_POSTOFFICE_H
