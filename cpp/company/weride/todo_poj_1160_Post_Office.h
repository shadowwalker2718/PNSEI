//
// Created by Henry Wu on 11/24/18.
//

#ifndef PNSEI_POJ_1160_POST_OFFICE_H
#define PNSEI_POJ_1160_POST_OFFICE_H

#include "pnsei.h"
namespace _poj_1160{
// wrong
int a[10]={1, 2, 3, 6, 7, 9, 11, 22, 44, 50};
int cost[11][11];
int dp[11][11];

void get_cost(int v) {
  int i, j, k, m;
  memset(cost, 0, sizeof(cost));
  for(i=1; i<=v; ++i) {
    for(j=i; j<=v; ++j) {
      cost[i][j] = 0;
      m = (i+j) >> 1;
      for(k=i; k<=j; ++k) {
        cost[i][j] += (a[m]-a[k]) >= 0 ? a[m]-a[k] : a[k]-a[m];
      }
    }
  }
}

int test() {
  int p=5, v=10;
  get_cost(v);
  for (int i = 1; i <= v; ++i) {
    dp[i][i] = 0;
    dp[i][1] = cost[1][i];
  }

  for (int j = 2; j <= p; ++j)
    for (int i = j + 1; i <= v; ++i) {
      dp[i][j] = INT_MAX;
      for (int k = j - 1; k < i; ++k) {
        dp[i][j] = min(dp[i][j], dp[k][j - 1] + cost[k + 1][i]);
        printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
      }
    }

  printf("%d\n", dp[v][p]);
  return 0;
}
/*  ---------------------
      作者:殷华
  来源:CSDN
  原文:https://blog.csdn.net/u011639256/article/details/38926387
  版权声明:本文为博主原创文章,转载请附上博文链接!*/
}


#endif //PNSEI_POJ_1160_POST_OFFICE_H
