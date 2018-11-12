//
// Created by root on 11/6/18.
//

#ifndef PNSEI_CLOSEST_CAR_H
#define PNSEI_CLOSEST_CAR_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=455844&highlight=cruise
 * 2018(10-12月)-[10]MFE/Fin/FinMath博士+<3个月短暂实习/全职 - 内推|Chicago MachineLearningEng全职@cruisefresh grad应届毕业生
 *
 对方先介绍了公司情况,然后就是聊简历,不知道怎么准备,结结巴巴的,后来做题就好了.
 问的是一个matrix,其中一个点是起点P,周围有4个车,问**最近的**到任意一个车的距离.

 当时觉得用dfs,bfs,和用heap run dijkstra4次都能做,但跑4
 次某些点肯定会重复计算.写的时候用的是bfs+map,做完了让我优化,对方的意思是用heap,并且遇到其中一个车就return.我是顺着他说,所以都聊的
 挺好的.但疑问是,如果用heap,不应该在压入pq的时候就return吧,因为先压入的不一定是最短的.其次不管so far的是不是最短的,都要检查暂时不
 是最短的最后会不会relax,以及找到了一个车,还要继续搜索其它三个车的距离进行比较,先搜后搜都没关系.
 *
 * */
#include "henry.h"

namespace _cruise_dijkstra{
const vector<PII> D={{1,0},{-1,0},{0,1},{0,-1}};

// return the closest car's coordinates, distance
pair<PII,int> getClosestCar(VVI m, set<PII> cars, PII user) {
  int R=m.size(), C=m[0].size();
  priority_queue<pair<int,PII>, vector<pair<int,PII>>, greater<pair<int,PII>>> distances;// min-heap {distance,{x,y}}
  //VVI ds(R, VI(C));
  map<PII,int> point_to_distance; // (x,y) => distance
  //set<PII> visited;
  distances.emplace(0, user);
  while (!distances.empty()) {
    auto top = distances.top();
    if(cars.count(top.second)){
      //cout << "closest dis:" << top.first << endl;
      return {top.second, top.first};
    }
    distances.pop();
    //if (visited.count(top.second))
    //  continue;//
    //visited.insert(top.second);
    point_to_distance[top.second] = top.first; // top.first is the distance of current point to user
    for (const auto &dr : D) { //{node,len}
      int nx=dr.first+top.second.first, ny = dr.second+top.second.second;
      if(nx<0 or nx>=R or ny<0 or ny>=C) continue;
      int new_distance = top.first + m[nx][ny];
      if (!point_to_distance.count({nx,ny}) or point_to_distance[{nx,ny}] > new_distance) { //relax
        point_to_distance[{nx,ny}] = new_distance;
        distances.emplace(new_distance, PII({nx, ny}));////into PQ
      }
    }
  }
  return {{INT_MAX,INT_MAX},0};
}

pair<PII,int> getClosestCar_with_visited(VVI m, set<PII> cars, PII user) {
  int R=m.size(), C=m[0].size();
  priority_queue<pair<int,PII>, vector<pair<int,PII>>, greater<pair<int,PII>>> distances;// min-heap {distance,{x,y}}
  map<PII,int> point_to_distance; // (x,y) => distance
  set<PII> visited;
  distances.emplace(0, user);
  while (!distances.empty()) {
    auto top = distances.top();
    if(cars.count(top.second)){
      //cout << "closest dis:" << top.first << endl;
      return {top.second, top.first};
    }
    distances.pop();
    if (visited.count(top.second))
      continue;//
    visited.insert(top.second);
    point_to_distance[top.second] = top.first; // top.first is the distance of current point to user
    for (const auto &dr : D) { //{node,len}
      int nx=dr.first+top.second.first, ny = dr.second+top.second.second;
      if(nx<0 or nx>=R or ny<0 or ny>=C) continue;
      int new_distance = top.first + m[nx][ny];
      if (!point_to_distance.count({nx,ny}) or point_to_distance[{nx,ny}] > new_distance) { //relax
        point_to_distance[{nx,ny}] = new_distance;
        distances.emplace(new_distance, PII({nx, ny}));////into PQ
      }
    }
  }
  return {{INT_MAX,INT_MAX},0};
}

void test(){
  /*
   *7 0 4 1 9 3 9 0 6 6
    8 4 0 6 7 1 2 0 1 3
    3 3 4 7 9 2 8 5 1 5
    6 9 7 0 0 6 5 0 6 3
    8 4 7 1 3 5 2 5 7 5
    0 0 1 4 9 x 9 7 8 0
    4 4 1 1 4 4 9 9 4 6
    3 4 2 2 5 7 9 0 4 6
    5 5 9 8 9 0 1 0 8 9
    1 4 3 4 8 9 8 7 8 4
   */
#define REP(i,x,y) for(int i=x;i<y;i++)
  srand(0xdeadbeef);
  int k=20;
  while(k--){
    VVI m(10+rand()%100, VI(10+rand()%200));
    REP(i,0,m.size()){
      REP(j,0,m[0].size()){
        m[i][j] = rand()%10;
      }
    }
    set<PII> s={{0,0},{m.size()-1,m[0].size()-1},{0,m[0].size()-1},{m.size()-1,0}};
    assert(getClosestCar(m,s,{m.size()/2,m[0].size()/2}) == getClosestCar_with_visited(m,s,{m.size()/2,m[0].size()/2}));
  }
  {
    srand(0xdeadbeef);
    VVI m(10, VI(10));
    REP(i,0,10){
      REP(j,0,10){
        m[i][j] = rand()%10;
        cout << m[i][j] << " ";
      }
      cout << endl;
    }
    set<PII> s={{0,0},{9,9},{0,9},{9,0}};
    auto r=getClosestCar(m,s,{5,5});
    assert(r.first == PII({9,0}));
    assert(r.second==24);
  }
}

}




#endif //PNSEI_CLOSEST_CAR_H
