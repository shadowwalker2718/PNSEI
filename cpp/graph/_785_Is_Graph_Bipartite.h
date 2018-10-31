//
// Created by root on 10/31/18.
//

#ifndef PNSEI_785_IS_GRAPH_BIPARTITE_H
#define PNSEI_785_IS_GRAPH_BIPARTITE_H

#include "henry.h"

/* *
Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every
 edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j
 exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i]
 does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation:
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation:
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
* */

namespace _785_Is_Graph_Bipartite {

    bool isBipartite_BFS(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> color(n);
        for(int k=0;k<n;k++){ //////
            if(color[k]!=0) continue;
            color[k]=1;
            queue<int> q;
            q.push(k);
            while(!q.empty()){
                int t=q.front(); q.pop();
                for(int i: graph[t]){
                    if(color[i]==0){
                        color[i]=color[t]*-1;
                        q.push(i);
                    }else if(color[i]==color[t])
                        return false;
                }
            }
        }
        return true;
    }

    // Just replace queue with stack, then it becomes DFS
    // also front() is change to top()
    bool isBipartite_DFS(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> color(n);
        for(int k=0;k<n;k++){
            if(color[k]!=0) continue;
            color[k]=1;
            stack<int> stk;
            stk.push(k);
            while(!stk.empty()){
                int t=stk.top(); stk.pop();
                for(int i: graph[t]){
                    if(color[i]==0){
                        color[i]=color[t]*-1;
                        stk.push(i);
                    }else if(color[i]==color[t])
                        return false;
                }
            }
        }
        return true;
    }

    bool test(){
        vector<vector<int>> vvi={{1,2,3}, {0,2}, {0,1,3}, {0,2}};
        assert(isBipartite_BFS(vvi) == false);
    }

};


#endif //PNSEI_785_IS_GRAPH_BIPARTITE_H
