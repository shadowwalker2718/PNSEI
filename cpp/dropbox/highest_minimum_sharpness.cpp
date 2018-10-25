#include <iostream>
#include <vector>

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
