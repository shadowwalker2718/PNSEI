//
// Created by Henry Wu on 10/30/18.
//

#ifndef PNSEI_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H
#define PNSEI_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H


#include "pnsei.h"

// https://leetcode.com/problems/cheapest-flights-within-k-stops/
// http://sde.quant365.com/graph.html#cheapest-flights-within-k-stops
namespace _787 {

// Bellman-Ford, Not a dag
class Solution { // O(K*)
public:
  // Single source shortest path
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
    unordered_map<int, unordered_map<int, int>> G; // a -> b = cost
    for (auto &e : flights)
      G[e[0]][e[1]] = e[2];
    unordered_map<int, int> node2cost = G[src];
    while (K--) { // O(K)
      unordered_map<int, int> tmp = node2cost; // cost from starting point {node, cost}
      for (const pair<const int, int> &e : tmp) { // O(V)
        unordered_map<int, int> &next = G[e.first];
        for (auto &f : next) { // O(V)
          if (node2cost.count(f.first)) {
            node2cost[f.first] = min(node2cost[f.first], e.second + f.second);
          } else {
            node2cost[f.first] = e.second + f.second;
          }
        }
      }
    }
    return node2cost.count(dst) ? node2cost[dst] : -1;
  }
};


// Dijkstra
class Solution2 { // O(K*)
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
    return 0;
  }
};


bool test() {
  VVI flights={{0,1,100},{1,2,100},{0,2,500}};
  assert(Solution().findCheapestPrice(3, flights, 0, 2, 0)==500);
  assert(Solution().findCheapestPrice(3, flights, 0, 2, 1)==200);
  return true;
}
}

#endif //PNSEI_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H
