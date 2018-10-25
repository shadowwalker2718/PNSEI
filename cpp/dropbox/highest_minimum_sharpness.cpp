#include <iostream>
#include <vector>


/*
 *
 * https://www.1point3acres.com/bbs/thread-316750-1-1.html
 *
 *
发一个最近的Dropbox电面

问的是Highest Minimum Sharpness, follow up是1M*1M board

用的是DP：
f(r, 0) = board[r][0]
f(r, c) = min(board[r][c], max(f(r-1,c-1), f(r, c-1), f(r, c+1)))

代码如下：

def find_highest_minimum_sharpness(board):
    rows, cols = len(board), len(board[0])
    for c in xrange(1, cols):
        for r in xrange(rows):
            left_max = board[r][c - 1]
            if r - 1 >= 0:
                left_max = max(left_max, board[r - 1][c - 1])
            if r + 1 < rows:
                left_max = max(left_max, board[r + 1][c - 1])
            board[r][c] = min(board[r][c], left_max)
    res = board[0][-1]
    for r in xrange(1, rows):
        res = max(res, board[r][-1])
    return res

Follow up的分析

For a very large board we could rotate the board clockwise by 90 degrees. Then process line by line.
To analyze the rotate strategy let's simplify the board to N*N. If we read a row and write to N rows
we have N disk seeks for reads and N*N disk seeks for writes. If we read a col and write to a row we
have N*N disk seeks for read and N disk seeks for write. We could balance the two. Say the mem can
fit K*K cells. We could read K rows of length K then rotate in mem then write to K rows of length K
For this operation we have K disk seeks for read and K disk seeks for write. There are `N*N/(K*K)`
blocks so in total we have `N*N/K` disk seeks for read and `N*N/K` disk seeks for write.
 * */

using namespace std;
#define INT_MIN -2147483648

int find_highest_minimum_sharpness(vector<vector<int>> &m) {
  if (m.empty() or m[0].empty())
    return INT_MIN;
  int R = m.size(), C = m[0].size();
  for (int j = 1; j < C; j++) {
    for (int i = 0; i < R; ++i) {
      int t = m[i][j - 1];
      if (i - 1 >= 0)
        t = max(t, m[i - 1][j - 1]);
      if (i + 1 < R)
        t = max(t, m[i + 1][j - 1]);
      m[i][j] = min(t, m[i][j]);
    }
  }
  int r = INT_MIN;
  for (int i = 0; i < R; ++i)
    r = max(r, m[i][C - 1]);
  return r;
}

int main(int argc, char **argv) {
  vector<vector<int>> board = {{5, 7, 2}, {7, 5, 8}, {9, 1, 5}};
  cout << find_highest_minimum_sharpness(board) << endl;
  return 0;
}
