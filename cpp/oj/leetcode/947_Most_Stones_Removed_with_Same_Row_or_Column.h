//
// Created by Henry Wu on 11/25/18.
//

#ifndef PNSEI_947_H
#define PNSEI_947_H

#include "pnsei.h"

namespace _947 {

typedef long long ll;

#define FILL(x, v) memset(x,v,sizeof(x))

const int INF = (int) 1E9;
#define MAXN 1005

VI rep;

int find(int x) {
  return rep[x] == x ? x : rep[x] = find(rep[x]);
}

void unionset(int x, int y) {
  int rx = find(x), ry = find(y);
  if (rx == ry) return;
  rep[rx] = ry;
}

class Solution {
public:
  int removeStones(vector<vector<int>> &st) {
    int n = st.size();
    rep.resize(n);
    REP(i, 0, n) rep[i] = i;
    REP(i, 0, n) {
      REP(j, i + 1, n) {
        if (st[i][0] == st[j][0] || st[i][1] == st[j][1]){
          unionset(i, j);
        }
      }
    }
    int ans = 0; // ans is the # of groups
    REP(i, 0, n) if (find(i) == i) ans++;
    return n - ans;
  }
};


void test() {
  VVI v = {{0, 0},
           {0, 1},
           {1, 0},
           {1, 2},
           {2, 1},
           {2, 2}};
  Solution sln;
  assert(sln.removeStones(v) == 5);
}

}
#endif //PNSEI_947_H
