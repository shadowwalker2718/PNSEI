//
// Created by Henry Wu on 10/30/18.
//

#ifndef PNSEI_MST_H
#define PNSEI_MST_H

#include "pnsei.h"

namespace graph_MST{

// https://www.hackerrank.com/challenges/kruskalmstrsub/problem

int V=5, E=6;
map<int,map<int,int>> m; // a->b 1

vector<int> bo(V+1,-1);
int findbo(int x){ return (bo[x]!=-1)?findbo(bo[x]):x;}
bool connected(int x, int y){
  return findbo(x)==findbo(y);
}
void merge(int x, int y){
  if(connected(x,y))
    return;
  x=findbo(x), y=findbo(y);
  bo[x]=y;
}

int start=1;
void init(){
  m[1][2]=3;
  m[1][3]=4;
  m[4][2]=6;
  m[5][2]=2;
  m[2][3]=5;
  m[3][5]=7;
}
pair<int,vector<pair<int,int>>> kruskal(){
  init();
  map<int, map<int,int>> es; // weight => (a -> b), weight-indexed map
  for(auto& pr: m)
    for(auto& xy: pr.second)
      es[xy.second][pr.first] = xy.first;
  vector<pair<int,int>> r;
  int sum=0;
  for(auto& pr: es){
    auto& mp=pr.second;
    for(auto& ab : mp){
      if(connected(ab.first, ab.second))
        continue;
      r.push_back(ab);
      merge(ab.first, ab.second);
      sum += pr.first;
    }
  }
  return {sum,r};
}


// https://en.wikipedia.org/wiki/Prim%27s_algorithm
//
// Different variations of the algorithm differ from each other in how the set Q is implemented: as a simple
// linked list or array of vertices, or as a more complicated priority queue data structure. This choice
// leads to differences in the time complexity of the algorithm. In general, a priority queue will be quicker
// at finding the vertex v with minimum cost, but will entail more expensive updates when the value of C[w] changes.
#define COST int
int prim(){
  int v=5, e=6, start=1;
  map<int,map<int,int>> m; // a,b,w
  m[1][2]=3, m[2][1]=3;
  m[1][3]=4, m[3][1]=4;
  m[4][2]=6, m[2][4]=6;
  m[5][2]=2, m[2][5]=2;
  m[2][3]=5, m[3][2]=5;
  m[3][5]=7, m[5][3]=7;
  /*cin >> v >> e;
  int x,y,z;
  for(int i=0;i<e;i++)
      cin >> x >> y >> z, m[x][y]=z, m[y][x]=z;
  cin>>start;*/
  priority_queue<pair<COST,int>,vector<pair<COST,int>>,greater<pair<COST,int>>> q;
  set<int> nodes;
  q.emplace(0,start);
  int sum=0;
  while(!q.empty()){
    auto e=q.top(); q.pop(); // {dis,a}
    if(nodes.count(e.second))
      continue;
    cout << "cost:" << e.first << ", node#:" << e.second << endl;
    sum+=e.first, nodes.insert(e.second);
    for(auto& pr: m[e.second])// {b,w}
      q.emplace(pr.second, pr.first);
  }
  return sum;
}


int test(){
  auto r=kruskal();
  auto p=prim();
  assert(15 == r.first);
  assert(15 == p);
  for (int i = 0; i < r.second.size(); ++i){
    cout << char('A'+r.second[i].first-1) << ","
         << char('A'+r.second[i].second-1) << endl;
  }
  return 0;
}

}

#endif //PNSEI_MST_H
