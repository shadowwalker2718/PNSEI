//
// Created by Henry Wu on 10/30/18.
//
#include "pnsei.h"

namespace graph_Dijkstra {

#define PII pair<int,int>

// https://www.hackerrank.com/challenges/dijkstrashortreach/problem
// http://sde.quant365.com/graph.html#dijkstra-algorithm
// This is for an undirected graph, DAG should be OK too
// Dijkstra works for undirected graph too! as long as the bi-directional
// distance in-between two nodes are the same!
vector<int> shortestReach(int n, vector<vector<int>> es, int source) {
  map<int, map<int, int>> edges; // node->node->weight/cost/length
  for (auto v: es)
    edges[v[0]][v[1]] = v[2];

  // The PQ is a min-heap to store the `distance from THE source to each node`
  priority_queue<PII, vector<PII >, greater<>> distances_pq;// min-heap
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
}
