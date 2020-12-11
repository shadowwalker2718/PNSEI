//
// Created by Henry Wu on 11/4/18.
//

#ifndef PNSEI_MOVE_9_IN_MATRIX_H
#define PNSEI_MOVE_9_IN_MATRIX_H

#include "pnsei.h"

namespace addepar_AStar {
// A* Algo
// https://en.wikipedia.org/wiki/A*_search_algorithm

/*
第五轮:算法题.
given a 3*3 matrix filling by unique numbers from 1 to 9.
原来的MATRIX我不记得了,就是打乱顺序的.只记得9在第二行最左边.
You can only switch 9 with 9's up/down/left/right neighbours. Each switch is counted as a step.
Question: what's the minimum number of steps to reach the state that the matrix is like
1 2 3
4 5 6
7 8 9
 *
 * */
// https://www.cs.princeton.edu/courses/archive/spr10/cos226/assignments/8puzzle.html
// https://stackoverflow.com/questions/32442837/minimum-number-of-steps-to-sort-3x3-matrix-in-a-specific-way

// T: O(?)

// {matrix, steps_so_far}
using state=pair<iMatrix, int>;
const iMatrix GOAL = {{1, 2, 3,}, // target matrix
                      {4, 5, 6,},
                      {7, 8, 0,}};

// moves - from original matrix, to the current matrix, how many steps we have moved?
// after `moves` steps, the original matrix becomes the current matrix
int manhattan_to_goal(const iMatrix &current_matrix, int moves){
  int distance = moves;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (current_matrix[i][j] != 0) {
        int t=current_matrix[i][j];

        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            if (t == GOAL[k][l])
              distance += abs(i - k) + abs(j - l); // manhattan distance
          }
        }

      }
    }
  }
  return distance;
}

struct cmp { // min heap
  bool operator()(state &a, state &b) {
    return manhattan_to_goal(a.first, a.second) > manhattan_to_goal(b.first, b.second);
  }
};

class solution {
  set<iMatrix> visited;
  map<iMatrix, iMatrix> parent; // current ==> previous
  const int dx[4] = {-1, +1, 0, 0};
  const int dy[4] = {0, 0, -1, +1};
private:
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

  bool safe(int i, int j) {
    return (i >= 0 && i <= 2 && j >= 0 && j <= 2);
  }

  vector<iMatrix> get_neighbours(const iMatrix &current) {
    pair<int, int> pos;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (current[i][j] == 0) {
          pos.first = i, pos.second = j;
          break;
        }
      }
    }
    vector<iMatrix> ans;
    for (int k = 0; k < 4; k++) {
      int cx = pos.first, cy = pos.second;
      iMatrix n = current;
      if (safe(cx + dx[k], cy + dy[k])) {
        swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
        ans.push_back(n);
      }
    }
    return ans;
  }

  int solve_bfs(iMatrix a) {
    priority_queue<state, vector<state>, cmp> Q; //min heap
    Q.push(state(a, 0)); // init
    while (!Q.empty()) {
      auto t = Q.top(); Q.pop();
      iMatrix s = t.first;
      //print(s);
      int moves_so_far = t.second;
      visited.insert(s);
      if (s == GOAL) {
        //print_path(s);
        return moves_so_far;
      }
      for (const auto& nx: get_neighbours(s)) {
        if (visited.count(nx) == 0) {
          parent[nx] = s;
          Q.emplace(nx, moves_so_far + 1);
        }
      }
    }
    return 0;
  }

};

}
#endif //PNSEI_MOVE_9_IN_MATRIX_H
