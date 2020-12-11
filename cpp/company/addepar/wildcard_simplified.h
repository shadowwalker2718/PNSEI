//
// Created by Henry Wu on 11/3/18.
//

#ifndef PNSEI_WILDCARD_SIMPLIFIED_H
#define PNSEI_WILDCARD_SIMPLIFIED_H

/*
2016(1-3月) 码农类General 硕士 全职@addepar - 网上海投 - 技术电面  | Other | fresh grad应届毕业生
Addepar一个小公司,是去google面试的时候路上看见的,弱弱地投一下SDE职位
    HR电话10min扯一扯但,然后很快安排第一次电面,2/1/2016 面完就来贡献面经~~~

基本流程都是5min聊自己,30min做题,然后再聊一聊,就通知等结果,看下一个step.其实都回答上来也不一定有next step,
 比如two sigma,电面问题大家都总结好了,都回答出来,也还是悲剧没有onsite

    题目是经典string matching,类似lc原题wildcard matching,但是更简单,没有'?' 的情况,直接只有*的情况,
    比如catcat 和c*t*t是match的输出True,否则比如cats,c*g 输出False

    感觉自己coding还是弱爆了,而且面试就脑子短路啊~~~~
*/
#include "pnsei.h"
namespace addepar_wildcard_simple{

vector<vector<char>> dp;
bool getdp(string& s, string& p, int x, int y){
  if(dp[x][y]!=-1) return dp[x][y]==1;// cache hit
  // init dp

  // logic
  if(s[x-1]==p[y-1]) return dp[x][y]=getdp(s,p,x-1,y-1);
  if(p[y-1]=='*'){
    for(int i=x-1;i>=0;i--){
      if(getdp(s,p,i+1,y-1))
        return dp[x][y]=true;
    }
    return false;
  }else{
    return dp[x][y]=0;
  }
}
bool match(string s, string p){
  int M=s.size(), N=p.size();
  dp=vector<vector<char>>(M+1, vector<char>(N+1, -1));
  return getdp(s,p,M,N);
}


//https://www.youtube.com/watch?v=3ZDZ-N0EPV0
bool isMatch(string s, string p) { // Bottom up DP
  int m = s.size(), n = p.size();
  vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
  dp[0][0] = true;  // empty s matches empty p
  for (int i = 1; i <= n; ++i) { // empty s matches "*" or "**" ...
    if (p[i - 1] == '*')
      dp[0][i] = dp[0][i - 1];
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) { // j start from 1 because dp[*][0] are also false
      if (p[j - 1] == '*') {
        dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; // either left or top cell
      } else if(s[i - 1] == p[j - 1]){
          dp[i][j] = dp[i - 1][j - 1];
      }
    }
  }
  return dp[m][n];
}


}

#endif //PNSEI_WILDCARD_SIMPLIFIED_H
