//
// Created by Henry Wu on 11/3/18.
//

#ifndef PNSEI_935_KNIGHT_DIALER_H
#define PNSEI_935_KNIGHT_DIALER_H

#include "henry.h"

namespace _935{

class Solution {
public:
#define valid(x,y) (int)(x>=0 && y>=0 && x<R && y<C && (x!=3 || y!=0) && (x!=3 || y!=2))
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
    if(y==0 && mm[x][2][k]!=0) return mm[x][2][k];
    if(y==2 && mm[x][0][k]!=0) return mm[x][0][k];
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

}

#endif //PNSEI_935_KNIGHT_DIALER_H
