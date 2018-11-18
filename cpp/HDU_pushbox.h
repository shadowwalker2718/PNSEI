#pragma once

#include "henry.h"

/* http://acm.hdu.edu.cn/showproblem.php?pid=1254
 *
 * 推箱子是一个很经典的游戏.今天我们来玩一个简单版本.在一个M*N的房间里有一个箱子和一个搬运工,搬运工的工作就是把箱
 * 子推到指定的位置,注意,搬运工只能推箱子而不能拉箱子,因此如果箱子被推到一个角上(如图2)那么箱子就不能再被移动了,如
 * 果箱子被推到一面墙上,那么箱子只能沿着墙移动.

现在给定房间的结构,箱子的位置,搬运工的位置和箱子要被推去的位置,请你计算出搬运工至少要推动箱子多少格.

 输入数据的第一行是一个整数T(1<=T<=20),代表测试数据的数量.然后是T组测试数据,每组测试数据的第一行是两个
 正整数M,N(2<=M,N<=7),代表房间的大小,然后是一个M行N列的矩阵,代表房间的布局,其中0代表空的地板,1代表墙,
 2代表箱子的起始位置,3代表箱子要被推去的位置,4代表搬运工的起始位置.

Sample Input:
1
5 5
{{0, 3, 0, 0, 0}
{1, 0, 1, 4, 0}
{0, 0, 1, 0, 0}
{1, 0, 2, 0, 0}
{0, 0, 0, 0, 0}}

0 - blank, 1 - wall, 2 - start of box, 3 - target, 4 - man
Sample Output:
4

*/

namespace _hdu_1254 {
const int WALL = 1, START = 2, TARGET = 3, MAN = 4;
vector<vector<int>> B = {{0, 3, 0, 0, 0},
                         {1, 0, 1, 4, 0},
                         {0, 0, 1, 0, 0},
                         {1, 0, 2, 0, 0},
                         {0, 0, 0, 0, 0}};
int ROW = 5, COL = 5;
//判重需要开4维数组,分别保存Man的坐标和Box的坐标
bool bitmap[10][10][10][10] = {};
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
struct node {
  int mx, my, bx, by, step;
};
struct pos {
  int x, y;
};
node start;
queue<node> q;

//预处理起点后可以标记成空的地板,方便操作
void input(int m, int n) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (B[i][j] == START)
        B[i][j] = 0, start.bx = i, start.by = j;
      else if (B[i][j] == MAN)
        B[i][j] = 0, start.mx = i, start.my = j;
}
#define check(x, y) (x >= 0 && x < ROW && y >= 0 && y < COL && B[x][y] != 1)
//是否Man可以走到Box的边上一点,以便把Box推向它要移动的方向
bool bfs_man(int sx, int sy, int ex, int ey, int bx, int by) {
  if (!check(sx, sy))
    return 0;
  queue<pos> qq;
  vector<vector<bool>> bm(ROW, vector<bool>(COL, false));
  bm[sx][sy] = bm[bx][by] = 1; // start points, box points
  qq.push(pos{sx, sy});
  while (!qq.empty()) {
    pos u = qq.front();
    qq.pop();
    if (u.x == ex && u.y == ey)
      return 1;
    pos next;
    for (int i = 0; i < 4; i++) {
      next.x = u.x + dx[i], next.y = u.y + dy[i];
      if (!check(next.x, next.y) || bm[next.x][next.y])
        continue;
      bm[next.x][next.y] = 1;
      qq.push(next);
    }
  }
  return 0;
}
//注意Box本身不能移动,必须由Man驱动
int bfs_box() {
  q.push(start);
  bitmap[start.bx][start.by][start.mx][start.my] = 1;
  while (!q.empty()) {
    node u = q.front();
    q.pop();
    if (B[u.bx][u.by] == TARGET)
      return u.step;
    node next;
    for (int i = 0; i < 4; i++) {
      next.bx = u.bx + dx[i], next.by = u.by + dy[i], next.mx = u.bx,
      next.my = u.by;
      next.step = u.step + 1;
      // u.bx - dx[i], u.by - dy[i] 是Box移动的反方向点的坐标,Man's destination
      if (!check(next.bx, next.by) ||
          bitmap[next.bx][next.by][next.mx][next.my] ||
          !bfs_man(u.mx, u.my, u.bx - dx[i], u.by - dy[i], u.bx, u.by))
        continue;
      bitmap[next.bx][next.by][next.mx][next.my] = 1;
      q.push(next);
    }
  }
  return -1;
}
int test() {
  input(ROW, COL);
  assert(bfs_box() == 4);
  return 0;
}
} // namespace _hdu_1254