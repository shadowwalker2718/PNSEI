#ifndef PNSEI_587_ERECT_THE_FENCE_H
#define PNSEI_587_ERECT_THE_FENCE_H

#include "pnsei.h"

namespace _587{
// https://leetcode.com/problems/erect-the-fence/description/
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

class Solution {
  long long cross(const Point &O,const Point &A,const Point &B){
    return (A.x-O.x)*(long long)(B.y-O.y) - (A.y-O.y)*(long long)(B.x-O.x);
  }
public:
  vector<Point> outerTrees(vector<Point>& points) {
    int L=points.size(), k=0;
    vector<Point> r(2*L);
    auto cmp=[](Point& p1, Point& p2){
      return p1.x<p2.x ||(p1.x==p2.x && p1.y<p2.y);};
    auto equ=[](Point& p1, Point& p2){
      return (p1.x==p2.x && p1.y==p2.y);};
    sort(points.begin(), points.end(), cmp);
    for(int i=0;i<L;++i){
      while(k>=2 && cross(r[k-2],r[k-1],points[i])<0) k--;
      r[k++]=points[i];
    }
    for(int i=L-2,t=k+1;i>=0;i--){
      while(k>=t && cross(r[k-2],r[k-1],points[i])<0) k--;
      r[k++]=points[i];
    }
    r.resize(k), sort(r.begin(), r.end(), cmp);
    r.erase(unique(r.begin(), r.end(), equ), r.end());
    return r;
  }
};

void test(){
  vector<Point> vp={{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
  Solution sln;
  auto r=sln.outerTrees(vp);
  for(Point& p: r){
    cout << p.x << "," << p.y << endl;
  }
}

}

#endif //PNSEI_587_ERECT_THE_FENCE_H
