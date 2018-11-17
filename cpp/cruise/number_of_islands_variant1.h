//
// Created by root on 11/6/18.
//

#ifndef PNSEI_NUMBER_OF_ISLANDS_VARIANT1_H
#define PNSEI_NUMBER_OF_ISLANDS_VARIANT1_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=454133&highlight=cruise
 * 2019(10-12月) 码农类General 硕士 全职@Cruise - 内推 - 技术电面  | Other | fresh grad应届毕业生
电面就一题,类似数小岛,但是里面数字不是1,可能是其他的数字.不同数字不同的小岛..
follwup 小岛头尾连起来.

简历问得很细.很深.

 https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=445188&highlight=cruise
 coding是number of islands,dfs解的,follow up 1 八个方向, follow up 2 把这个平面卷成一个圆柱体,
 即最左边的一栏和最右边的一栏相接

 https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=454393&highlight=cruise
 2018(10-12月) 码农类General 硕士 全职@Cruise - Other - HR筛选  | Fail | fresh grad应届毕业生
一个小时的电面,问了10分钟简历,但没get到面试官到底想知道我简历哪部分,感觉答得很不好.问了一道题,就是那个数岛的,
 follow up 1是如果是圆柱的怎么办,就是第一个和最后一个连起来,follow up 2是如何节省空间.和面试官交流不是很流畅,应该是跪了
 *
 *
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=297272&highlight=cruise
 * 题很简单,但是只能用c++写,我还忘记了一个api的用法很尴尬.感觉他家挺好的,属于比较好的startup了,求onsite.
 考的一道题是connected components.大概有点像数小岛,就用dfs或者bfs直接做就好啦.

 但是followup问我如果grid是immutable的要怎么做,如果grid太大不能用额外的空间怎么做.时间复杂度也问的比较详细
 *
 * */
#include "henry.h"

namespace _cruise_islands {

struct UFO{ //union find object
  vector<int> bo, sz;
  void o(int len) {
    bo.resize(len),sz.resize(len);
    iota(bo.begin(), bo.end(), 0);
    fill(sz.begin(), sz.end(), 1);
  }
  int f(int x) {
    return (x==bo[x])?x:f(bo[x]);
  };
  void u(int x, int y) {
    int b = f(x), m = f(y);// after this line, no x and y any more!!
    if (b == m) { return; }
    if(b<m) swap(b,m); // b is big boss, m is small boss
    bo[m]=b,sz[b]+=sz[m],sz[m]=0;
  };
  int z(){ // size of connected comp
    return count_if(sz.begin(), sz.end(), [](int i) {return i>0; });
  }
  int c(int x, int y){
    return f(x)==f(y);
  }
};


struct Solution {
  Solution() { srand(0xdeadbeef); }

  VVC generateIslands(int R, int C) {
    VVC vs(R, VC(C, '0'));
    int k = 100;
    while (k--) {
      int i = rand() % R, ii = (i + rand() % R) % R;
      for (; i < ii; i++) {
        for (int j = rand() % C; j < ii % C; j++) {
          vs[i][j] = '0' + (i) % 9;
        }
      }
    }

    while (k++ < 100) {
      int x = rand() % (R / 2), y = rand() % (C / 2);
      for (int i = 0; i < x + rand() % 3; i++) {
        for (int j = 0; j < y + rand() % 4; j++) {
          vs[x + i][y + j] = '0' + (j) % 9;
        }
      }
    }
    return vs;
  }

  void printBoard(VVC board) {
    for (int i = 0; i < board.size(); ++i) {
      for (char c: board[i])
        cout << c << ' ';
      cout << endl;
    }
  }

  int numIslands(vector<vector<char>> &grid) {
    int r = 0;
    if (grid.empty() || grid[0].empty()) return r;
    const vector<pair<int, int>> D = {{1,  0},
                                      {-1, 0},
                                      {0,  1},
                                      {0,  -1}};
    int R = grid.size(), C = grid[0].size();
    vector<vector<bool>> visited(R, vector<bool>(C));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (visited[i][j] || grid[i][j] == '0') { continue; }
        stack<pair<int, int>> stk;
        stk.emplace(i, j), visited[i][j] = true;
        while (!stk.empty()) {
          auto p = stk.top();
          stk.pop();
          for (auto d : D) {
            int x = p.first + d.first, y = p.second + d.second;
            if (x >= 0 && x < R && y >= 0 && y < C && !visited[x][y]) {
              if (grid[x][y] == '1')
                visited[x][y] = true, stk.emplace(x, y);
            }
          }
        }
        r++;
      }
    }
    return r;
  }

  /*
  0 0 1 2 3 0 0 0 1 2 0 1 2 3 4 5 6 7 8 0 1 2 1 2 3 2 3 4 5 0
  0 1 0 0 0 1 2 3 4 5 0 1 2 3 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 2 0 0 1 2 3 4 0 1 2 3 4 5 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 1 0 0 0 1 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 0
  0 1 0 1 0 1 0 1 2 3 4 0 1 2 3 4 5 6 7 8 0 1 2 0 1 2 3 4 5 0
  0 1 0 1 0 0 0 1 2 3 4 0 1 2 3 4 5 6 7 8 0 1 2 3 1 2 3 4 5 6
  0 0 1 1 0 0 1 2 3 4 0 1 2 3 4 5 6 7 8 0 1 1 2 3 1 2 3 4 5 6
  0 0 1 1 0 0 1 2 3 4 0 1 2 3 4 5 6 7 8 0 1 1 2 3 4 3 3 4 5 6
  8 0 1 1 2 0 1 2 3 4 0 1 2 3 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 0 0 1 2 0 1 0 1 2 3 4 5 6 0 1 2 3 4 5 6 7 8 0 1 2 3 4 6 6
  1 0 1 2 2 0 1 0 1 2 3 4 5 6 7 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 0 1 2 2 0 1 0 1 2 3 4 5 6 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 0 1 1 2 0 1 0 1 2 3 4 5 6 7 8 0 3 4 5 6 7 8 0 1 2 3 4 5 0
  0 0 1 1 2 0 1 0 1 2 3 4 5 6 7 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6
  0 0 1 1 2 0 1 0 1 2 3 4 5 6 7 8 2 3 4 5 6 7 8 0 1 2 3 4 0 0
  0 0 1 2 2 0 1 0 1 2 3 4 5 6 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 0
  0 1 0 1 2 0 1 0 1 2 3 4 5 6 7 1 2 3 4 5 6 7 8 0 1 2 3 4 0 0
  0 1 0 1 2 0 1 0 1 2 3 4 5 6 7 8 0 3 4 5 6 7 8 0 1 2 3 4 5 0
  0 1 0 1 2 0 1 0 1 2 3 4 5 6 7 2 3 4 5 6 7 8 0 1 2 3 0 0 0 0
  0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 2 3 4 5 6 7 8 0 1 2 3 4 0 0 0
  */
  const vector<pair<int, int>> D = {{1,  0},
                                    {-1, 0},
                                    {0,  1},
                                    {0,  -1}};
  VVC grid;
  VVB bm;
  int ROW;
  int COL;

  int numIslands_different_char(vector<vector<char>> &_grid) {
    this->grid = _grid;
    if (grid.empty() || grid[0].empty()) return 0;
    int r = 0;
    ROW = grid.size(), COL = grid[0].size();
    bm = VVB(ROW, VB(COL)); // bit map of visited
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COL; ++j) {
        if (!bm[i][j]) {
          dfs(i, j, grid[i][j]);
          ++r;
        }
      }
    }
    return r;
  }

  void dfs(int i, int j, char c) {
    bm[i][j] = true;
    for (auto d: D) {
      int x = i + d.first, y = j + d.second;
      if (x >= 0 && y >= 0 && x < ROW && y < COL && !bm[x][y]) {
        if (grid[x][y] == c) {
          dfs(x, y, c);
        }
      }
    }
  }

  int numIslands_different_char_left_right_connected(vector<vector<char>> &_grid) {
    this->grid = _grid;
    if (grid.empty() || grid[0].empty()) return 0;
    int r = 0;
    ROW = grid.size(), COL = grid[0].size();
    bm = VVB(ROW, VB(COL)); // bit map of visited
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COL; ++j) {
        if (!bm[i][j]) {
          dfs2(i, j, grid[i][j]);
          ++r;
        }
      }
    }
    return r;
  }

  void dfs2(int i, int j, char c) {
    bm[i][j] = true;
    for (auto d: D) { // left right connected
      int x = i + d.first, y = (j + d.second + COL) % COL;
      if (x >= 0 && x < ROW && !bm[x][y] && grid[x][y] == c) {
        dfs2(x, y, c);
      }
    }
  }

  int numIslands_different_char_ufo(VVC &grid){
    if (grid.empty() || grid[0].empty()) return 0;
    int r = 0;
    ROW = grid.size(), COL = grid[0].size();
    UFO ufo;
    ufo.o(ROW*COL);
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COL; ++j) {
        for(auto d: D){
          int x=i+d.first, y=j+d.second;
          if(x>=0 && x<ROW && y>=0 && y<COL && grid[i][j]==grid[x][y])
            ufo.u(COL*i+j, COL*x+y);
        }
      }
    }
    return ufo.z();
  }

  int numIslands_different_char_ufo2(VVC &grid){
    if (grid.empty() || grid[0].empty()) return 0;
    int r = 0;
    ROW = grid.size(), COL = grid[0].size();
    UFO ufo;
    ufo.o(ROW*COL);
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COL; ++j) {
        for(auto d: D){
          int x=i+d.first, y=(j+d.second+COL)%COL;
          if(x>=0 && x<ROW && grid[i][j]==grid[x][y])
            ufo.u(COL*i+j, COL*x+y);
        }
      }
    }
    return ufo.z();
  }

};

void test() {
  Solution sln;
  auto vs = sln.generateIslands(20, 30);
  //sln.printBoard(vs);
  assert(sln.numIslands_different_char_ufo(vs)==152);
  assert(sln.numIslands_different_char_ufo2(vs)==148);
  assert(sln.numIslands_different_char(vs) == 152);
  assert(sln.numIslands_different_char_left_right_connected(vs) == 148);
  vs = sln.generateIslands(4, 5);
  //sln.printBoard(vs);
  assert(sln.numIslands_different_char(vs) == 4);
  assert(sln.numIslands_different_char_left_right_connected(vs) == 4);
}


}


#endif //PNSEI_NUMBER_OF_ISLANDS_VARIANT1_H
