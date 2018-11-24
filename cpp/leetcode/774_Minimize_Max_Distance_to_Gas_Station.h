//
// Created by root on 11/23/18.
//

#ifndef PNSEI_774_MINIMIZE_MAX_DISTANCE_TO_GAS_STATION_H
#define PNSEI_774_MINIMIZE_MAX_DISTANCE_TO_GAS_STATION_H

/*
 * https://leetcode.com/contest/weekly-contest-69/problems/minimize-max-distance-to-gas-station/

On a horizontal number line, we have gas stations at positions stations[0], stations[1], …, stations[N-1],
 where N = stations.length.

Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:

Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
 * */
#include "henry.h"
namespace _774{

struct interval{
double l; // distance or length
int n; // number of gas stations in this block
double g; // average
interval(double d):l(d),n(1),g(l){}
};
struct comp{ // compare average
  bool operator()(interval& x, interval& y){
    return x.g < y.g;
  }
};

// the strategy is to choose the max average length block every time
class Solution { // (N+K*LogN)
public:
  double minmaxGasDist(vector<int>& v, int K) {
    priority_queue<interval,vector<interval>,comp> pq; // max heap
    for(int i=0;i<(int)v.size()-1;++i){ // N
      double ds=(double)(v[i+1])-v[i];
      pq.emplace(ds);
    }
    while(K--){ // K
      auto tp=pq.top();
      pq.pop();
      tp.n+=1, tp.g=tp.l/tp.n;
      pq.push(tp);
    }
    auto r=pq.top();
    return r.g;
  }
};

// Assuming we have known the result
class Solution_Binary_Search { // O(?*N)
public:
double minmaxGasDist(vector<int>& v, int K) {
  // 1. get all intervals
  adjacent_difference(v.begin(), v.end(), v.begin());
  v.erase(v.begin());
  // 2. get the max
  int mx=*max_element(v.begin(), v.end());
  double h=0, t=(double)mx;
  while(t-h>1e-9){ // O(?)
    double m=h+(t-h)/2.0;
    long long required=0;
    for(int i: v) // O(N)
      required+=ceil(i/m)-1;
    if(required>K){
      h=m;
    }else{
      t=m;
    }
  }
  return t;
}
};

}
#endif //PNSEI_774_MINIMIZE_MAX_DISTANCE_TO_GAS_STATION_H
