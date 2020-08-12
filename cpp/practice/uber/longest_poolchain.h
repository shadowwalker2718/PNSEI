//
// Created by Henry Wu on 11/20/18.
//

#ifndef PNSEI_LONGEST_POOLCHAIN_H
#define PNSEI_LONGEST_POOLCHAIN_H

/*
 * https://www.glassdoor.com/Interview/Given-the-travel-time-of-each-customer-Find-the-driver-with-the-longest-chain-of-trips-which-means-there-is-always-at-lea-QTN_2278730.htm
 * 2018(10-12月) 码农类General 博士 全职@uber - 内推 - 技术电面  | Other | fresh grad应届毕业生
新鲜电面面经



Find longest poolChain

input: List<Log>
output: 最长的poolchain

log结构:
Long timestamp
int driver_id
int passenger_id
String pickup / dropoff

poolchain的定义:
直接或者间接的有overalp的行程（乘客)数目

Algo: meeting room
*/

#include "henry.h"

namespace _uber_longest_poolchain {

struct travel_log {
  size_t timestamp;
  int driver_id;
  int passenger_id;
  bool action; // true -> pick up; false -> dropoff
};

struct cmp {
  bool operator()(const travel_log &a, const travel_log &b) const{
    return a.timestamp < b.timestamp || (a.timestamp == b.timestamp && a.passenger_id < b.passenger_id);
  }
};

int find_longest_pool_chain(vector<travel_log> vl) {
  map<int, set<travel_log, cmp>> m;
  for (travel_log &t: vl) {
    m[t.driver_id].insert(t); // in STL set, if key is the same, set will use the later one overwrite previous one
  }
  size_t r = 0;
  for (auto &pr: m) {
    auto &s = pr.second;
    size_t start = INT_MIN, p = 0;
    for (const travel_log &t: s) {
      if (t.action) {
        p++;
        if (p == 2) {
          start = t.timestamp;
        }
      } else {
        p--;
        if (p == 1) {
          r = max(r, t.timestamp - start);
          start = 0;
        }
      }
    }
  }
  return r;
}

void test() {
  vector<travel_log> logs = {{1,  0, 0, true},
                             {4,  0, 1, true},
                             {4,  0, 2, true},
                             {5,  0, 0, false},
                             {7,  0, 1, false},
                             {8,  0, 3, true},
                             {9,  0, 4, true},
                             {10, 0, 2, false},
                             {13, 0, 3, false},
                             {15, 0, 4, false},
                             {17, 0, 5, true},
                             {20, 0, 5, false}
  };
  int r = find_longest_pool_chain(logs);
  assert(r == 5);
}
};

#endif //PNSEI_LONGEST_POOLCHAIN_H
