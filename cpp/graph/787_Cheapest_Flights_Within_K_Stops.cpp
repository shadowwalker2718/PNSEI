//
// Created by root on 10/30/18.
//

#include "henry.h"
#include "graph/787_Cheapest_Flights_Within_K_Stops.h"

// https://leetcode.com/problems/cheapest-flights-within-k-stops/
namespace _787 {

    // Bellman-Ford
    class Solution { // O(K*)
    public:
        int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
            unordered_map<int, unordered_map<int, int>> mp; // a -> b = cost
            for (auto &e : flights)
                mp[e[0]][e[1]] = e[2];
            unordered_map<int, int> cost = mp[src];
            while (K--) {
                unordered_map<int, int> tmp = cost; // cost from starting point
                for (const pair<int, int> &e : tmp) {
                    unordered_map<int, int> &next = mp[e.first];
                    for (auto &f : next) {
                        if (cost.count(f.first)) {
                            cost[f.first] = min(cost[f.first], e.second + f.second);
                        } else {
                            cost[f.first] = e.second + f.second;
                        }
                    }
                }
            }
            return cost.count(dst) ? cost[dst] : -1;
        }
    };


    // Dijkstra
    class Solution2 { // O(K*)
    public:
        int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
        }
    };


    bool test(){
        return true;
    }
}