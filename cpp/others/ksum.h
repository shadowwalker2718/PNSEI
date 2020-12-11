#pragma once

#include "pnsei.h"

namespace _ksum {

// https://www.lintcode.com/en/problem/k-sum-ii/
// return solution number
// return all feasible solutions

/*class Solution {
public:
  int kSum(vector<int> A, int K, int target) {
    if (A.size() < K || K < 2)
      return -1;
    int r = 0;
    dfs(r, A, K, target, 0);
    return r;
  }

  void dfs(int &r, vector<int> &A, int K, int t, int head) {
    if (K > 2) {
      for (int i = head; i < A.size(); ++i) {
        dfs(r, A, K - 1, t - A[i], head + 1);
      }
    } else if (K == 2) { // 2sum
      unordered_map<int, int> ms; // int->count
      for (int i = head; i < A.size(); ++i) {
        int j = A[i];
        if (ms.count(t - j)) {
          r++;
          if (ms[j] == 1) // counter minus 1
            ms.erase(j);
          else
            ms[j]--;
        } else
          ms[j]++;
      }
    }
  }
};*/

// As no dup, we can use hash!
class Solution_No_Duplicate {
public:
  VVI kSum(vector<int> A, int K, int target) {
    if (A.size() < K || K < 2)
      return {};
    VVI r;
    VI p;
    dfs(A, r, p, K, target, 0);
    return r;
  }

  void dfs(VI &A, VVI &r, VI p, int K, int T, int head) {
    if (K > 2) {
      for (int i = head; i < A.size(); ++i) {
        VI t = p;
        t.push_back(A[i]);
        dfs(A, r, t, K - 1, T - A[i], i + 1);
      }
    } else if (K == 2) { // 2sum
      unordered_set<int> ms; // int->count
      for (int i = head; i < A.size(); ++i) {
        int j = A[i];
        if (ms.count(T - j)) {
          VI t = p;
          t.push_back(j), t.push_back(T - j);
          r.push_back(t);
        }
        ms.insert(j);
      }
    }
  }
};

// How to remove duplicates?
// http://sde.quant365.com/combinatorics.html#combination-sum-ii
// http://sde.quant365.com/combinatorics.html#subsetspowerset-dag-dfs-ii
// http://sde.quant365.com/combinatorics.html#permutation-ii
// http://sde.quant365.com/google-2016-10.html#sum-1
class Solution_With_Duplicates {
public:
  VVI kSum(vector<int> A, int K, int target) {
    if (A.size() < K || K < 2)
      return {};
    VVI r;
    VI p;
    sort(A.begin(), A.end());
    dfs(A, r, p, K, target, 0);
    return r;
  }

  void dfs(VI &A, VVI &r, VI p, int K, int T, int head) {
    if (K > 2) {
      for (int i = head; i < A.size(); ++i) {
        if (i > head && A[i - 1] == A[i]) { continue; } ////
        VI t = p; // to avoid unwind stack changing data in container, use a temp var, use pass by value
        t.push_back(A[i]);
        dfs(A, r, t, K - 1, T - A[i], i + 1);
      }
    } else if (K == 2) { // 2sum
      int i = head, j = A.size() - 1;
      while (i < j) {
        while (i + 1 < A.size() && A[i] == A[i + 1]) i++; // remove duplicates
        while (j - 1 >= 0 && A[j] == A[j - 1]) j--; // remove dups
        int sum = A[i] + A[j];
        if (sum == T) {
          VI t = p;
          t.push_back(A[i]), t.push_back(A[j]);
          r.push_back(t); // cherry pick, different from account balancing problem
          i++, j--;
        } else if (sum < T) {
          i++;
        } else {
          j--;
        }
      }
    }
  }
};

void test() {
  /*Solution_No_Duplicate sln;
  auto r = sln.kSum({1, 4, 7, 10, 12, 15, 16, 18, 21, 23, 24, 25, 26, 29}, 5, 65);
  assert(r == 33);*/

  Solution_No_Duplicate sln2;
  auto r2 = sln2.kSum({1, 4, 7, 10, 12, 15, 16, 18, 21, 23, 24, 25, 26, 29}, 5, 65);
  /*
   * [[1,4,7,24,29],[1,4,10,21,29],[1,4,10,24,26],[1,4,12,23,25],[1,4,15,16,29],
   * [1,4,15,21,24],[1,4,16,18,26],[1,4,16,21,23],[1,7,10,18,29],[1,7,10,21,26],
   * [1,7,10,23,24],[1,7,12,16,29],[1,7,12,21,24],[1,7,15,16,26],[1,7,15,18,24],
   * [1,7,16,18,23],[1,10,12,16,26],[1,10,12,18,24],[1,10,15,16,23],[1,10,15,18,21],
   * [1,12,15,16,21],[4,7,10,15,29],[4,7,10,18,26],[4,7,10,21,23],[4,7,12,16,26],
   * [4,7,12,18,24],[4,7,15,16,23],[4,7,15,18,21],[4,10,12,15,24],[4,10,12,16,23],
   * [4,10,12,18,21],[4,12,15,16,18],[7,10,12,15,21]]
   * */
  assert(33 == r2.size());

  Solution_With_Duplicates sln_with_dups;
  auto r3 = sln_with_dups.kSum({16, 1, 4, 7, 10, 12, 15,
                                16, 18, 21, 23, 24, 25, 26, 29}, 5, 65);
  // one more result: [1 7 16 16 25]
  assert(r3.size() == 34);
}

} // namespace _ksum