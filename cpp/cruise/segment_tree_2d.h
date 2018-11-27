//
// Created by Henry Wu on 11/27/18.
//

#ifndef PNSEI_SEGMENT_TREE_2D_H
#define PNSEI_SEGMENT_TREE_2D_H

// https://stackoverflow.com/questions/25121878/2d-segment-quad-tree-explanation-with-c
#include "henry.h"

namespace segment_tree_2d {

VVI P;

/* 2D Segment Tree node */
struct Point {
  int x, y, mx;

  Point() {}

  Point(int x, int y, int mx) : x(x), y(y), mx(mx) {}

  bool operator<(const Point &other) const {
    return mx < other.mx;
  }
};

struct Segtree2d {

  // I didn't calculate the exact size needed in terms of 2D container size.
  // If anyone, please edit the answer.
  // It's just a safe size to store nodes for MAX * MAX 2D grids which won't cause stack overflow :)
  Point T[500]; // TODO: calculate the accurate space needed

  int n, m;

  // initialize and construct segment tree
  void init(int n, int m) {
    this->n = n;
    this->m = m;
    build(1, 1, 1, n, m);
  }

  // build a 2D segment tree from data [ (a1, b1), (a2, b2) ]
  // Time: O(n logn)
  Point build(int nid, int a1, int b1, int a2, int b2) { // all are indices
    // out of range
    if (a1 > a2 || b1 > b2)
      return dummy_node();

    // if it is only a single index, assign value to node
    if (a1 == a2 && b1 == b2)
      return T[nid] = Point(a1, b1, P[a1-1][b1-1]);

    // split the tree into four segments
    T[nid] = dummy_node();
    T[nid] = maxNode(T[nid], build(4 * nid - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2));
    T[nid] = maxNode(T[nid], build(4 * nid - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2));
    T[nid] = maxNode(T[nid], build(4 * nid + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2));
    T[nid] = maxNode(T[nid], build(4 * nid + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2));
    return T[nid];
  }

  // helper function for query(int, int, int, int);
  Point query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
    // if we out of range, return dummy
    if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or (a1 > a2 or b1 > b2)) // no overlap or node's BB is invalid
      return dummy_node();
    // if it is within range, return the node
    if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2)
      return T[node];
    // split into four segments
    Point mx = dummy_node();
    mx = maxNode(mx, query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2));
    mx = maxNode(mx, query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2));

    // return the maximum value
    return mx;
  }

  // query from range [ (x1, y1), (x2, y2) ]
  // Time: O(logn)
  Point query(int x1, int y1, int x2, int y2) {
    return query(1, 1, 1, n, m, x1, y1, x2, y2);
  }

  // helper function for update(int, int, int);
  Point update(int node, int a1, int b1, int a2, int b2, int x, int y, int value) {
    if (a1 > a2 or b1 > b2)
      return dummy_node();

    if (x > a2 or y > b2 or x < a1 or y < b1)
      return T[node];

    if (x == a1 and y == b1 and x == a2 and y == b2)
      return T[node] = Point(x-1, y-1, value);

    Point mx = dummy_node();
    mx = maxNode(mx, update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x, y, value));
    mx = maxNode(mx, update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x, y, value));
    mx = maxNode(mx, update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x, y, value));
    mx = maxNode(mx, update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x, y, value));
    return T[node] = mx;
  }

  // update the value of (x, y) index to 'value'
  // Time: O(logn)
  Point update(int x, int y, int value) {
    return update(1, 1, 1, n, m, x, y, value);
  }

  // utility functions; these functions are virtual because they will be overridden in child class
  virtual Point maxNode(Point a, Point b) {
    return max(a, b);
  }

  // dummy node
  virtual Point dummy_node() {
    return Point(0, 0, -INT_MAX);
  }
};

/* 2D Segment Tree for range minimum query; a override of Segtree2d class */
struct Segtree2dMin : Segtree2d {
  // overload maxNode() function to return minimum value
  Point maxNode(Point a, Point b) {
    return min(a, b);
  }

  Point dummy_node() {
    return Point(0, 0, INT_MAX);
  }
};

struct point{
  int x=0,y=0;
  point(){}
  point(int a,int b){x=a,y=b;}
  bool operator==(point& o){return x==o.x and y==o.y;}
  bool operator<=(point& o){return x<=o.x and y<=o.y;}
};
struct bb{
  point tl, br;
  bb(){}
  bb(point a, point b){tl=a, br=b;}
  bool is_atomic(){return tl==br;}
  vector<bb> split(){
    vector<bb> r;
    // TODO - bugs [0,0] [1,1]
    point p1, p2;
    r.push_back(bb{tl,{(tl.x+br.x)/2,(tl.y+br.y)/2}});
    p1.x=(tl.x+br.x)/2+1, p1.y=(tl.y+br.y)/2+1;
    if(p1<=br)
      r.push_back(bb{p1,br});
    p1.x=(tl.x+br.x)/2+1, p1.y=tl.y , p2={br.x,(tl.y+br.y)/2};
    if(p1<=p2)
      r.push_back(bb{p1,p2});
    p1={tl.x,(tl.y+br.y)/2+1} , p2={(tl.x+br.x)/2,br.y};
    if (p1<=p2)
      r.push_back(bb{p1, p2});

    return r;
  }
  bool overlap(bb o){
    return !(o.tl.x>br.x|| o.br.x<tl.x || o.tl.y>br.y || o.br.y<tl.y);
  }
  bool contain(bb o){
    return tl<=o.tl and o.br<=br;
  }
  bool contain(point p){
    return tl.x<=p.x && p.x<=br.x && tl.y<=p.y && p.y<=br.y;
  }
  //int area(){return (br.x-tl.x+1)*(br.y-tl.y+1);}
};
struct stree2d{ // sum segment tree
  stree2d(){}
  void build(VVI& m){
    v=build_rec(m,{point{0,0},{(int)m.size()-1,(int)m[0].size()-1}});
  }
  int build_rec(VVI& m,bb o){
    b=o;
    if(o.is_atomic()){
      return v=m[o.tl.x][o.tl.y];
    }else{
      auto r=o.split();
      int t=0;
      REP(i,0,r.size()){
        children[i]= new stree2d();
        t+=children[i]->build_rec(m,r[i]);
      }
      return v=t;
    }
  }
  int range_query(bb o){
    int r=0;
    if(b.overlap(o)){
      if (b.is_atomic() or o.contain(b))
        return v;
      REP(i,0,4){
        if(children[i]==0) continue;
        r+=children[i]->range_query(o);
      }
    }
    return r;
  }
  void update(point p, int k){
    if(!b.contain(p)) return;
    if(b.is_atomic()) {
      v = k;
      return;
    }
    int t=0;
    REP(i,0,4){
      if(children[i]==0) continue;
      children[i]->update(p,k);
      t+=children[i]->v;
    }
    v=t;
  }

  bb b;
  int v=INT_MAX; // sum
  stree2d* children[4]={};
};


/* Drier program */
int test() {
// initialize class objects
  Segtree2d Tmax;
  Segtree2dMin Tmin;

  // input
  P = {{3, 0, 1, 4, 2},
       {5, 6, 3, 2, 1},
       {1, 2, 0, 1, 5},
       {4, 1, 0, 1, 7},
       {1, 0, 3, 0, 5}};
  // query
  int x1 = 2, y1 = 1, x2 = 4, y2 = 3;
  stree2d st;
  st.build(P);
  int sum=st.range_query({{x1, y1}, {x2, y2}});
  assert(sum==8);
  st.update({3,2},2);
  sum=st.range_query({{x1, y1}, {x2, y2}});
  assert(sum==10);


  int n=P.size()-1, m=P[0].size()-1;

  // initialize
  Tmax.init(n, m);
  Tmin.init(n, m);



  int r=Tmax.query(x1, y1, x2, y2).mx;
  r=Tmin.query(x1, y1, x2, y2).mx;

  // update
  int x = 3, y = 2, v = 2;
  Tmax.update(x, y, v);
  Tmin.update(x, y, v);

  return 0;
}

}

#endif //PNSEI_SEGMENT_TREE_2D_H
