//
// Created by Henry Wu on 11/4/18.
//

#ifndef PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H
#define PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H

#include "henry.h"

namespace _465_account_balancing {

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=230745&highlight=addepar
 * 2017(1-3月) 码农类General 硕士 全职@Addepar - 网上海投 - Onsite  | Fail | 在职跳槽
Addepar Front End onsite 面试 一共 五轮.

第一轮: 算法题.买卖股票题I, II. 最后又问了一个遍历 GRAPH 的题,没有写代码,只是说了思路.题目是比如A欠B$8,B欠C$6,C欠D$7,D又欠A$10, 应该怎么还钱?

 * */

/*
 *
 * A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for
 * $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means
 * person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the
 * person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].

  Given a list of transactions between a group of people,
  return the **minimum deal_numberber of transactions** required to settle the debt.

  Note:

  A transaction will be given as a tuple (x, y, z). Note that x ≠ y and z > 0.
  Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.
  Example 1:

  Input:
  [[0,1,10], [2,0,5]]

  Output:
  2

  Explanation:
  Person #0 gave person #1 $10.
  Person #2 gave person #0 $5.

  Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.

  Example 2:

  Input:
  [[0,1,10], [1,0,1], [1,2,5], [2,0,5]]

  Output:
  1

  Explanation:
  Person #0 gave person #1 $10.
  Person #1 gave person #0 $1.
  Person #1 gave person #2 $5.
  Person #2 gave person #0 $5.

  Therefore, person #1 only need to give person #0 $4, and all debt is settled.*/

// O(N!)
class Solution_Recursive { // NP Hard?
public:
  // return the **minimum deal_numberber of transactions** required to settle the debt.
  int minTransfers(vector<vector<int>> &transactions) {
    unordered_map<int, int> m;
    for (auto t : transactions) {
      m[t[0]] -= t[2];
      m[t[1]] += t[2];
    }
    vector<int> accnt(m.size());
    int cnt = 0;
    for (auto a : m) {
      if (a.second != 0)
        accnt[cnt++] = a.second;
    }
    return rec(accnt, 0, 0);
  }

  // BF
  int rec(vector<int> &accnt, int head, int deal_number) {
    int res = INT_MAX;
    while (head < accnt.size() && accnt[head] == 0) // find the first non-0 item in the vector
      ++head;
    for (int i = head + 1; i < accnt.size(); ++i) {
      if (accnt[i] != 0 && (accnt[i] ^ accnt[head]) < 0) {
        accnt[i] += accnt[head];
        res = min(res, rec(accnt, head + 1, deal_number + 1));
        accnt[i] -= accnt[head];
      }
    }
    return res == INT_MAX ? deal_number : res;
  }
};

class Solution_Ksum {
  // examplify how to remove one element from multiset
  void setErase(unordered_multiset<int>& balance, vector<int> v) {
    for (int i: v) {
      auto itr = balance.find(i);
      if (itr != balance.end())
        balance.erase(itr); // erase only 1 item
    }
  }

  // return transaction number
  int kSum(int K, unordered_multiset<int> &balance, int T) {
    // examplify how to erase multiset when looping
    // using a temp vector...
    vector<int> bal(balance.begin(), balance.end());
    if (K == 2) { // base case 2SUM
      for (int i : bal){ // -2, 2, 2,-1; [2,-1]
        if (balance.count(T - i)) {
          setErase(balance, {i, T - i});
          return 1; //!!
        }
      }
      return 0;
    } else {
      for (int i : bal) { // [-2,2,1,-1]; [2,1,-1], 2
        setErase(balance, {i});
        int res = kSum(K - 1, balance, T - i); // res == K-2
        if (res > 0)
          return res + 1;
        balance.insert(i);
      }
      return 0;
    }
  }

public:
  // clique problem
  int minTransfers(const vector<vector<int>> &transactions) {
    unordered_multiset<int> balance;
    unordered_map<int, int> balanceMap;
    for (auto &v : transactions) {
      balanceMap[v[0]] -= v[2];
      balanceMap[v[1]] += v[2];
    }
    for (auto &pair : balanceMap) {
      if (pair.second != 0)
        balance.insert(pair.second);
    }
    if (balance.size() == 0)
      return 0;
    int res = 0, clique = 2; // from smallest clique coz?
    while (clique < balance.size()) {
      int r = kSum(clique, balance, 0); // clique-1==r or r==0
      if (r == 0) // not found
        clique++;
      else
        res += r;
    }
    return res + balance.size() - 1;
  }
};

/*
// First calculate the net balance of each one, then the idea is try to find smallest clique that
// sum up to 0. Once find
// one, we erase the clique from the balance set and increase the result by n(clique)-1.
// Optimized with 2Sum and 3Sum.
class Solution {
  int _kSum(int K, unordered_multiset<int> &balance, int T) {
    auto it = balance.begin();
    if (K == 2) {
      while (it != balance.end()) {
#if 0
        auto t=T-*it;
        if (balance.count(t)) {
          balance.erase(it);
          balance.erase(balance.find(t));
          return 1; // one transaction needed
        }
        it++;
#endif
        auto t = balance.find(T - *it);
        if (t != balance.end() && it != t) {
          balance.erase(it);
          balance.erase(t);
          return 1; // one transaction needed
        }
        it++;
      }
    } else {
      while (it != balance.end()) {
        int t = *it;
        it = balance.erase(it);
        int res = _kSum(K - 1, balance, T - t);
        if (res != 0)
          return res + 1;
        balance.insert(t);
      }
    }
    return 0;
  }

public:
  int minTransfers(const vector<vector<int>> &transactions) {
    unordered_multiset<int> balance;
    unordered_map<int, int> balanceMap;
    for (auto &v : transactions) {
      balanceMap[v[0]] -= v[2];
      balanceMap[v[1]] += v[2];
    }
    for (auto &pair : balanceMap) {
      if (pair.second != 0)
        balance.insert(pair.second);
    }
    if (balance.size() == 0)
      return 0;
    int res = 0, clique = 2;
    while (clique < balance.size()) {
      int r = _kSum(clique, balance, 0);
      if (r == 0) // not found
        clique++;
      else
        res += r;
    }
    return res + balance.size() - 1;
  }

  int minTransfers2(const vector<vector<int>> &transactions) {
    vector<int> balance;
    unordered_map<int, int> balanceMap;
    for (auto &v : transactions) {
      balanceMap[v[0]] -= v[2];
      balanceMap[v[1]] += v[2];
    }
    for (auto &pair : balanceMap) {
      if (pair.second != 0)
        balance.push_back(pair.second);
    }
    if (balance.empty())
      return 0;
    sort(balance.begin(), balance.end());
    int r = 0, clique = 2;
    while (clique < balance.size()) {
      set<int> visited;
      r += __kSum(clique, balance, 0, visited);
      for(int i: visited) balance[i]=INT_MAX;
      balance.erase(remove(balance.begin(), balance.end(), INT_MAX), balance.end());
      clique++;
    }
    return r + balance.empty()?0:(balance.size()-1);
  }

  int __kSum(vector<int>& v, vector<int> p, set<int>& m, int K, int T) {
    if (K == 2) { // base case
      int i = 0, j = v.size() - 1, r = 0;
      while (i < j) {
        if (m.count(i) && i < v.size()) {
          i++;
          continue;
        }
        if (m.count(j) && j >= 0) {
          j--;
          continue;
        }
        if (i >= v.size() || j < 0)
          break;
        int t = v[i] + v[j];
        if (t == T) {
          r++, m.insert(i), m.insert(j), i++, j--;
          for (int i: p) {
            m.insert(i);
          }
        } else if (t < T) {
          i++;
        } else {
          j--;
        }
      }
      return r;
    } else {
      int r=0;
      for (int i = 0; i < v.size(); i++) {
        if (m.count(i)) continue;
        p.push_back(i);
        r += __kSum(v, p, m, K - 1, T - v[i]);
        p.pop_back();
      }
      return r*(K-1);
    }
  }
};
*/

void test() {
  Solution_Recursive sln;
  vector<vector<int>> vi = {{0, 1, 10},
                            {1, 0, 1},
                            {1, 2, 5},
                            {2, 0, 5}};
  assert(sln.minTransfers(vi) == 1);

  vi = {{1, 8, 1},
        {1, 13, 21},
        {2, 8, 10},
        {3, 9, 20},
        {4, 10, 61},
        {5, 11, 61},
        {6, 12, 59},
        {7, 13, 60}};
  Solution_Ksum sln2;
  assert(sln2.minTransfers(vi) == 8);

  vi={{2,0,5},{3,4,4}};
  assert(sln2.minTransfers(vi) == 2);

};

}

#endif //PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H
