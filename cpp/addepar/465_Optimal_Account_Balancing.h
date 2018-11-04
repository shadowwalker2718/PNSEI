//
// Created by root on 11/4/18.
//

#ifndef PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H
#define PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H
#include "henry.h"

namespace _465{

/*
 *
 * A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for
 * $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means
 * person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the
 * person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].

  Given a list of transactions between a group of people, return the **minimum deal_numberber of transactions** required to
  settle the debt.

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
class Solution_Recursive {
public:
  int minTransfers(vector<vector<int>>& transactions) {
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
  int rec(vector<int>& accnt, int start, int deal_number) {
    int res = INT_MAX;
    while (start < accnt.size() && accnt[start] == 0)
      ++start;
    for (int i = start + 1; i < accnt.size(); ++i) {
      if (accnt[i]!=0 and (accnt[i] ^ accnt[start]) < 0) {
        accnt[i] += accnt[start];
        res = min(res, rec(accnt, start + 1, deal_number + 1));
        accnt[i] -= accnt[start];
      }
    }
    return res == INT_MAX ? deal_number : res;
  }
};

// First calculate the net balance of each one, then the idea is try to find smallest clique that sum up to 0. Once find
// one, we erase the clique from the balance set and increase the result by n(clique)-1. Optimized with 2Sum and 3Sum.
class Solution {
  void setErase(unordered_multiset<int>& balance, int v) {
    auto itr = balance.find(v);
    if (itr != balance.end()) balance.erase(itr);
  }
  int nSum(int cliq, unordered_multiset<int>& balance, int s) {
    vector<int> bal(balance.begin(), balance.end());
    if (cliq == 2) {
      for (int i : bal)
        if (balance.count(s-i)) {
          setErase(balance, i);
          setErase(balance, s-i);
          return 1;
        }
    } else if (cliq == 3) {
      sort(bal.begin(), bal.end());
      for (int i = 0; i < bal.size()-2; ++i) {
        if (i > 0 && bal[i]==bal[i-1]) continue;
        for (int j = i+1, k = bal.size()-1; j < k;) {
          if (bal[i]+bal[j]+bal[k]<s) ++j;
          else if (bal[i]+bal[j]+bal[k]>s) --k;
          else {
            setErase(balance, bal[i]);
            setErase(balance, bal[j]);
            setErase(balance, bal[k]);
            return 2;
          }
        }
      }
    } else {
      for (int i : bal) {
        setErase(balance, i);
        int res = nSum(cliq-1, balance, s-i);
        if (res != 0) return res+1;
        balance.insert(i);
      }
    }
    return 0;
  }
public:
  int minTransfers(vector<vector<int>>& transactions) {
    unordered_multiset<int> balance;
    unordered_map<int, int> balanceMap;
    for (auto& v : transactions) {
      balanceMap[v[0]] -= v[2];
      balanceMap[v[1]] += v[2];
    }
    for (auto& pair : balanceMap)
      if (pair.second != 0) balance.insert(pair.second);
    if (balance.size() == 0)
      return 0;
    int res = 0, clique = 2;
    while (clique < balance.size()) {
      int r = nSum(clique, balance, 0);
      if (r == 0) clique++;
      else res += r;
    }
    return res+balance.size()-1;
  }
};



void test(){
  Solution sln;
  vector<vector<int>> vi={{0,1,10},
                          {1,0,1},
                          {1,2,5},
                          {2,0,5}};
  assert(sln.minTransfers(vi)==1);

  vi={{1,8,1},{1,13,21},{2,8,10},{3,9,20},{4,10,61},{5,11,61},{6,12,59},{7,13,60}};
  assert(sln.minTransfers(vi)==8);
}

}

#endif //PNSEI_465_OPTIMAL_ACCOUNT_BALANCING_H
