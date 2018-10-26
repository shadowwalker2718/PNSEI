#pragma once

#include "henry.h"

namespace _knn {

struct point {
  int x;
  int y;
  point(int x_, int y_) : x(x_), y(y_) {}
};

point *knn(vector<point> &ps, int k) { // O(N)
  if (ps.size() <= k)
    return NULL;
  nth_element(
      ps.begin(), ps.begin() + k - 1, ps.end(), [](point &p1, point &p2) {
        return (p1.x * p1.x + p1.y * p1.y) < (p2.x * p2.x + p2.y * p2.y);
      });
  return &ps[k - 1];
}

struct comp {
  bool operator()(point *l, point *r) {
    return (l->x * l->x + l->y * l->y) > (r->x * r->x + r->y * r->y);
  }
};
// priority_queue cannot use lambda function as comparator
// http://stackoverflow.com/questions/5807735/c-priority-queue-with-lambda-comparator-error
point knn2(vector<point> &ps, int k) { // O(N)
  point dummy = {INT_MIN, INT_MIN};
  if (ps.size() <= k || k <= 0)
    return dummy;
  priority_queue<point, vector<point>, comp> pq(comp(), ps); // O(N)
  while (--k)
    pq.pop(); // O(kLogN)
  return pq.top();
}

// NLogK
point knn4(vector<point> &ps, int k) {
  if (ps.size() <= k || k <= 0)
    return {INT_MIN, INT_MIN};
  auto COMP = [](const point &l, const point &r) {
    return (l.x * l.x + l.y * l.y) < (r.x * r.x + r.y * r.y);
  };
  priority_queue<point, vector<point>, decltype(COMP)> pq(
      ps.begin(), ps.begin() + k, COMP); // maxheap
  int i = k;
  while (i++ < ps.size()) // (N-k)LogK
    if (COMP(ps[i], pq.top())) {
      pq.pop(), pq.push(ps[i]);
    }
  return pq.top();
}

} // namespace _knn