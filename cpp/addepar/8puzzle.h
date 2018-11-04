//
// Created by root on 11/4/18.
//

#ifndef PNSEI_MOVE_9_IN_MATRIX_H
#define PNSEI_MOVE_9_IN_MATRIX_H

#include "henry.h"

namespace addepar_AStar {
// A* Algo
// https://en.wikipedia.org/wiki/A*_search_algorithm

/*
 *
 * 第五轮：算法题。
given a 3*3 matrix filling by unique numbers from 1 to 9.
原来的MATRIX我不记得了，就是打乱顺序的。只记得9在第二行最左边。
You can only switch 9 with 9's up/down/left/right neighbours. Each switch is counted as a step.
 Question: what's the minimum number of steps to reach the state that the matrix is like
1 2 3
4 5 6
7 8 9
 *
 * */
// https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html
// https://stackoverflow.com/questions/32442837/minimum-number-of-steps-to-sort-3x3-matrix-in-a-specific-way

// {matrix, steps_so_far}
typedef pair<iMatrix, int> state;
const iMatrix GOAL = {{1, 2, 3,},
                      {4, 5, 6,},
                      {7, 8, 0,}};

int manhattan(const iMatrix &a, int moves) {
  int dist = moves;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (a[i][j] != 0) {

        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            if (a[i][j] == GOAL[k][l])
              dist += abs(i - k) + abs(j - l);
          }
        }

      }
    }
  }
  return dist;
}

struct cmp { // min heap
  bool operator()(state &a, state &b) {
    return manhattan(a.first, a.second) > manhattan(b.first, b.second);
  }
};

class solution {
  set<iMatrix> visited;
  map<iMatrix, iMatrix> parent; // current ==> previous
  const int dx[4] = {-1, +1, 0, 0};
  const int dy[4] = {0, 0, -1, +1};
private:
  void print_path(iMatrix s) {
    if (parent.count(s))
      print_path(parent[s]);

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        printf("%d ", s[i][j]);
      }
      cout << endl;
    }
    cout << endl;
    return;
  }

  void print(const iMatrix &s) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        printf("%d ", s[i][j]);
      }
      cout << "\n";
    }
    cout << string(80,'*') << endl;
  }

public:
  bool safe(int i, int j) {
    return (i >= 0 && i <= 2 && j >= 0 && j <= 2);
  }

  vector<iMatrix> get_neighbours(iMatrix &a) {
    pair<int, int> pos;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (a[i][j] == 0) {
          pos.first = i;
          pos.second = j;
          break;
        }
      }
    }
    vector<iMatrix> ans;
    for (int k = 0; k < 4; k++) {
      int cx = pos.first;
      int cy = pos.second;
      iMatrix n = a;
      if (safe(cx + dx[k], cy + dy[k])) {
        swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
        ans.push_back(n);
      }
    }
    return ans;
  }

  int solve(iMatrix a) {
    priority_queue<state, vector<state>, cmp> Q;
    Q.push(state(a, 0));
    while (!Q.empty()) {
      auto t = Q.top();
      Q.pop();
      iMatrix s = t.first;
      print(s);
      int mv = t.second;
      visited.insert(s);
      if (s == GOAL) {
        print_path(s);
        return mv;
      }
      for (auto nx: get_neighbours(s)) {
        if (visited.count(nx) == 0) {
          parent[nx] = s;
          Q.emplace(nx, mv + 1);
        }
      }
    }
  }

};

int test() {
  iMatrix a = {{0, 1, 3},
               {4, 2, 5},
               {7, 8, 6}};
  solution sln;
  assert(sln.solve(a) == 4);
}


}
#endif //PNSEI_MOVE_9_IN_MATRIX_H
