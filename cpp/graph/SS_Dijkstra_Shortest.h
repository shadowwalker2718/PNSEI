//
// Created by Henry Wu on 10/30/18.
//
#include "henry.h"

namespace graph_Dijkstra {

#define PII pair<int,int>

// https://www.hackerrank.com/challenges/dijkstrashortreach/problem
// this is for an undirected graph, DAG should be OK too
vector<int> shortestReach(int n, vector<vector<int>> es, int source) {
  map<int, map<int, int>> edges; // node->node->weight/cost/length
  for (auto v: es)
    edges[v[0]][v[1]] = v[2];

  priority_queue<PII, vector<PII >, greater<PII>> distances_pq;// min-heap
  vector<int> single_source_distances = vector<int>(n + 1, INT_MAX); // distance to s
  distances_pq.emplace(0, source); // {distance from the single source, to_node}
  set<int> visited;
  while (!distances_pq.empty()) {
    const auto top = distances_pq.top();
    distances_pq.pop();
    int top_node = top.second;
    if (visited.count(top_node))
      continue;//
    single_source_distances[top_node] = top.first;
    for (const auto &neighbor : edges[top_node]) { //{node,len}
      int d = top.first + edges[top_node][neighbor.first];
      if (single_source_distances[neighbor.first] > d) { //relax
        single_source_distances[neighbor.first] = d;
        distances_pq.emplace(d, neighbor.first);////into PQ
      }
    }
    visited.insert(top_node);
  }
  single_source_distances.erase(single_source_distances.begin() + source);
  single_source_distances.erase(single_source_distances.begin());
  return single_source_distances;
}

// http://sde.quant365.com/graph.html#dijkstra-algorithm
bool test() {
  vector<vector<int>> es = {
      {1, 2, 24},
      {1, 4, 20},
      {3, 1, 3},
      {4, 3, 12},

      {2, 1, 24},
      {4, 1, 20},
      {1, 3, 3},
      {3, 4, 12}
  };
  vector<int> r = {24, 3, 15};
  assert(r == shortestReach(4, es, 1));
  return true;
}
}
