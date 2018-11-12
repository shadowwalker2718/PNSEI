//
// Created by root on 11/12/18.
//

#ifndef PNSEI_INTERVAL_SUBTRACTION_H
#define PNSEI_INTERVAL_SUBTRACTION_H
/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=456224&highlight=cruise
 * 2019(10-12月) 码农类General 本科 全职@cruise - 内推 - 技术电面  | Fail | fresh grad应届毕业生
就是给你一堆排好序的,没有overlap的interval,然后再给一个target interval.求出所有在target interval中存在,却不在interval list中存在的interval
 *
 * */
#include "henry.h"

namespace _cruise_interval{

vector<pair<int,int>> interval_subtraction(vector<pair<int,int>> intervals, pair<int,int> t){
  //intervals.push_back(t);
  //sort(intervals.begin(), intervals.end());
  //if(intervals.front().first>t.second or intervals.back().second<t.first) return {};//no overlap
  //if(intervals.front()==t or intervals.back()==t) return {};
  vector<pair<int,int>> r;
  vector<pair<int, char>> v;
  for(auto i: intervals){
    v.emplace_back(i.first,-1);
    v.emplace_back(i.second,1);
  }
  v.emplace_back(t.first, 1);
  v.emplace_back(t.second, -1);
  sort(v.begin(), v.end());
  int i=0;
  PII tmp={INT_MAX,0};
  for(auto pr: v){
    i+=pr.second;
    if(i==1){
      tmp.first=pr.first;
    }else if (i==0 and tmp.first!=INT_MAX){
      tmp.second=pr.first;
      r.push_back(tmp);
      tmp = {INT_MAX,0};
    };
  }
  return r;
}

void test(){
  vector<PII> intervals;
  intervals.emplace_back(1,3);
  intervals.emplace_back(4,7);
  intervals.emplace_back(9,14);
  intervals.emplace_back(20,34);
  intervals.emplace_back(43,46);
  auto r=interval_subtraction(intervals, {5,41});
  assert(vector<PII>({{7,9},{14,20},{34,41}}) == r);
  assert(interval_subtraction(intervals, {50,71}) == vector<PII>({{50,71}}));
}
}



#endif //PNSEI_INTERVAL_SUBTRACTION_H
