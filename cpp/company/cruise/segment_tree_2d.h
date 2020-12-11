//
// Created by Henry Wu on 11/27/18.
//

#ifndef PNSEI_SEGMENT_TREE_2D_H
#define PNSEI_SEGMENT_TREE_2D_H

// https://stackoverflow.com/questions/25121878/2d-segment-quad-tree-explanation-with-c
#include "pnsei.h"

namespace segment_tree_2d {

struct point {
  int x = 0, y = 0;

  point() {}

  point(int a, int b) { x = a, y = b; }

  bool operator==(point &o) const { return x == o.x && y == o.y; }

  bool operator<=(point &o) const { return x <= o.x && y <= o.y; }
};

struct bb {
  point tl, br;

  bb() {}

  bb(point a, point b) { tl = a, br = b; }

  bool is_atomic() { return tl == br; }

  vector<bb> split() {
    vector<bb> r;
    point p1, p2;
    r.push_back(bb{tl, {(tl.x + br.x) / 2, (tl.y + br.y) / 2}});
    p1.x = (tl.x + br.x) / 2 + 1, p1.y = (tl.y + br.y) / 2 + 1;
    if (p1 <= br)
      r.push_back(bb{p1, br});
    p1.x = (tl.x + br.x) / 2 + 1, p1.y = tl.y, p2 = {br.x, (tl.y + br.y) / 2};
    if (p1 <= p2)
      r.push_back(bb{p1, p2});
    p1 = {tl.x, (tl.y + br.y) / 2 + 1}, p2 = {(tl.x + br.x) / 2, br.y};
    if (p1 <= p2)
      r.push_back(bb{p1, p2});

    return r;
  }

  bool overlap(bb o) {
    return !(o.tl.x > br.x || o.br.x < tl.x || o.tl.y > br.y || o.br.y < tl.y);
  }

  bool contain(bb o) {
    return tl <= o.tl && o.br <= br;
  }

  bool contain(point p) {
    return tl.x <= p.x && p.x <= br.x && tl.y <= p.y && p.y <= br.y;
  }
  //int area(){return (br.x-tl.x+1)*(br.y-tl.y+1);}
};

struct segment_tree_2d { // sum segment tree
  segment_tree_2d() {}

  void build_tree(VVI &m) {
    if(m.empty() || m[0].empty()) return;
    int R=m.size(), C=m[0].size();
    v = build_rec(m, {point{0, 0}, {R - 1, C - 1}});
  }

  int build_rec(VVI &m, bb o) {
    b = o;
    if (o.is_atomic()) {
      return v = m[o.tl.x][o.tl.y];
    } else {
      auto r = o.split();
      int t = 0;
      REP(i, 0, r.size()) {
        children[i] = new segment_tree_2d();
        t += children[i]->build_rec(m, r[i]);
      }
      return v = t;
    }
  }

  int range_query(bb o) {
    int r = 0;
    if (b.overlap(o)) {
      if (b.is_atomic() || o.contain(b))
        return v;
      REP(i, 0, 4) {
        if (children[i] == 0) continue;
        r += children[i]->range_query(o);
      }
    }
    return r;
  }

  void update(point p, int k) {
    if (!b.contain(p)) return;
    if (b.is_atomic()) {
      v = k;
      return;
    }
    int t = 0;
    REP(i, 0, 4) {
      if (children[i] == 0) continue;
      children[i]->update(p, k);
      t += children[i]->v;
    }
    v = t;
  }

  bb b; // bounding box for the current segment tree
  int v = INT_MAX; // value corresponding to the current bounding box, could be sum or min or whatever
  segment_tree_2d *children[4] = {};
};

class NumMatrix {
  segment_tree_2d t;
public:
  NumMatrix(vector<vector<int>> matrix) {
    t.build_tree(matrix);
  }

  void update(int row, int col, int val) {
    t.update({row,col},val);
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return t.range_query({{row1,col1},{row2,col2}});
  }
};



/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */

/* Driver program */
int test() {
  NumMatrix nm(VVI{});

  VVI P = {{3, 0, 1, 4, 2},
           {5, 6, 3, 2, 1},
           {1, 2, 0, 1, 5},
           {4, 1, 0, 1, 7},
           {1, 0, 3, 0, 5}};
  // query
  int x1 = 2, y1 = 1, x2 = 4, y2 = 3;
  segment_tree_2d st;
  st.build_tree(P);
  int sum = st.range_query({{x1, y1},
                            {x2, y2}});
  assert(sum == 8);
  st.update({3, 2}, 2);
  sum = st.range_query({{x1, y1},
                        {x2, y2}});
  assert(sum == 10);
  return 0;
}

}

#endif //PNSEI_SEGMENT_TREE_2D_H
