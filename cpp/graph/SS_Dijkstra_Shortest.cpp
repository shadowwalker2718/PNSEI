//
// Created by root on 10/30/18.
//
#include "henry.h"
#include "graph.h"

namespace graph_Dijkstra {

#define PB push_back
#define F first
#define S second
#define HAS count
#define MP make_pair
#define PII pair<int,int>

    // this is for an undirected graph, DAG should be OK too
    vector<int> shortestReach(int n, vector<vector<int>> es, int s) {
        map<int, map<int, int>> edges; // node->node->weight/cost/length
        for (auto v: es)
            edges[v[0]][v[1]] = v[2];
        priority_queue<PII, vector<PII >, greater<PII>> distances;// min-heap
        vector<int> ds = vector<int>(n + 1, INT_MAX); // distance to s
        distances.emplace(0, s); // {distance, node}
        set<int> visited;
        while (!distances.empty()) {
            auto t = distances.top();
            distances.pop();
            if (visited.HAS(t.S))
                continue;//
            ds[t.S] = t.F;
            for (const auto &pr : edges[t.S]) { //{node,len}
                int d = t.F + edges[t.S][pr.F];
                if (ds[pr.F] > d) { //relax
                    ds[pr.F] = d, distances.emplace(d, pr.F);////
                }
            }
            visited.insert(t.S);
        }
        ds.erase(ds.begin() + s);
        ds.erase(ds.begin());
        return ds;
    }

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
    }
}