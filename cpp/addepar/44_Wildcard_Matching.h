//
// Created by root on 10/31/18.
//

#ifndef PNSEI_44_WILDCARD_MATCHING_H
#define PNSEI_44_WILDCARD_MATCHING_H

#include "henry.h"

namespace _44{

    /*
     * 外卡匹配和正则匹配最大的区别就是在星号的使用规则上，对于正则匹配来说，星号不能单独存在，前面必须要有一个字符，
     * 而星号存在的意义就是表明前面这个字符的个数可以是任意个，包括0个，那么就是说即使前面这个字符并没有在s中出现过也无
     * 所谓，只要后面的能匹配上就可以了。而外卡匹配就不是这样的，外卡匹配中的星号跟前面的字符没有半毛钱关系，如果前面
     * 的字符没有匹配上，那么直接返回false了，根本不用管星号。而星号存在的作用是可以表示任意的字符串，当然只是当匹配
     * 字符串缺少一些字符的时候起作用，当匹配字符串包含目标字符串没有的字符时，将无法成功匹配。*/

    class Solution { // TLE
    public:
        bool isMatch(string s, string p) {
            p.erase(unique(p.begin(), p.end(),[](char x, char y){return x==y and x=='*';}), p.end());
            return rec(s, p);
        }
        bool rec(string s, string p) {
            if(p.empty()) return s.empty();
            if(s.empty()){ //"*****" can match ""
                return p.empty() or p=="*";
            }

            if(p[0]=='?'){
                return rec(s.substr(1), p.substr(1));
            }else if(p[0]=='*'){
                string np=p.substr(1);
                for(int i=0; i<=s.size(); i++){
                    if(rec(s.substr(i), np))
                        return true;
                }
                return false;
            }else if(isalpha(p[0])){
                return p[0]==s[0] and rec(s.substr(1), p.substr(1));
            }
        }


      bool isMatch2(string s, string p) { // Bottom up DP
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
          if (p[i - 1] == '*')
            dp[0][i] = dp[0][i - 1];
        }
        for (int i = 1; i <= m; ++i) {
          for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
              dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; ////!!!!
            } else {
              dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
            }
          }
        }
        return dp[m][n];
      }

      void test(){
        string s = "acdcb";
        string p = "a*c?b";
        assert(isMatch2(s,p)==false);
      }
    };

    void test(){
        string s="mississippi";
        string p="m??*ss*?i*pi";
        Solution sln;
        cout << sln.isMatch(s,p) << endl;

        sln.isMatch2(s,p);
        sln.test();
    }
}


class Solution {
public:


#define valid(x,y) (int)(x>=0 && y>=0 && x<R && y<C && (x!=3 or y!=0) and (x!=3 or y!=2))
  vector<pair<int,int>> dirs={{ -1,-2 },{ -2,-1 }, { 1,2 },{ 2,1 },
                              { -1,2 },{ 2,-1 }, { 1,-2 },{ -2,1 }};
  int R=4, C=3;
  vector<vector<int>> m=vector<vector<int>>(5, vector<int>(4, -1));

  int mm[5][4][5001]={0};
  int getnum(int x, int y) {
    if (m[x][y]!=-1) return m[x][y];
    int r = 0;
    for (auto pr : dirs)
      r += valid(x+pr.first,y+pr.second);
    return m[x][y] = r;
  }

  int dfs(int x, int y, int k) {
    if(mm[x][y][k]!=0) return mm[x][y][k];
    if(y==0 and mm[x][2][k]!=0) return mm[x][2][k];
    if(y==2 and mm[x][0][k]!=0) return mm[x][0][k];
    if (k < 1) return mm[x][y][k]=1;
    if (k == 1) return mm[x][y][k]=getnum(x, y);
    int r = 0;
    for (auto& pr : dirs) {
      int nx = x + pr.first, ny = y + pr.second;
      if (valid(nx, ny)){
        r += dfs(nx, ny, k - 1);
      }
    }
    return mm[x][y][k]=r;
  }
  int knightDialer(int N) {

    long long tot=0;
    tot+=dfs(0,0,N-1);
    tot+=dfs(1,0,N-1);
    tot+=dfs(2,0,N-1);
    tot*=2;
    tot+=dfs(0,1,N-1);
    tot+=dfs(1,1,N-1);
    tot+=dfs(2,1,N-1);
    tot+=dfs(3,1,N-1);


    return tot%int(1e9+7);
  }

};

#endif //PNSEI_44_WILDCARD_MATCHING_H
