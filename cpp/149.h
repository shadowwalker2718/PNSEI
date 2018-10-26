#pragma once

#include "henry.h"

namespace _149 {
/*** Definition for a point.*/
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

// https://leetcode.com/problems/max-points-on-a-line/
struct Solution {
#define _equal(a, b) ((a.x == b.x) && (a.y == b.y))
#define _slope(a, b) ((float)(a.y - b.y) / (a.x - b.x))
  int maxPoints(vector<Point> &ps) { // T: O(N^2)
    int r = 0, L = ps.size();
    for (int i = 0; i < L; ++i) { // O(N^2)
      int dup = 1;
      unordered_map<float, int> counter;
      counter[NAN] = 0;

      for (int j = 0; j < L; ++j) {
        if (i == j)
          continue;
        if (_equal(ps[i], ps[j]) && dup++)
          continue; // dup points
        counter[ps[i].x == ps[j].x ? INFINITY : _slope(ps[i], ps[j])]++;
      }
      for (auto &pr : counter) {
        r = max(r, pr.second + dup);
      }
    }
    return r;
  }
};

struct Solution2 {                       // 29ms
  int maxPoints(vector<Point> &points) { // 39ms
    int result = 0;
    for (int i = 0; i < points.size(); i++) {
      unordered_map<long long, int> count;
      int same = 1;
      int mx = 0;
      for (int j = i + 1; j < points.size(); j++) {
        int x = points[i].x - points[j].x;
        int y = points[i].y - points[j].y;
        int g = gcd(x, y);
        if (!g) { // g==0 means same points
          same++;
          continue;
        }
        x /= g, y /= g;
        mx = max(mx, ++count[((long long)(x) << 32) | y]);
      }
      result = max(result, mx + same);
    }
    return result;
  }

  int gcd(int num1, int num2) {
    int temp;
    while (num2)
      temp = num2, num2 = num1 % num2, num1 = temp;
    return num1;
  }
};

void test() {
  //[[0,0],[1,1],[1,-1]]
  {
    Solution sln;
    vector<Point> ps = {{0, 0}, {1, 1}, {1, -1}};
    assert(sln.maxPoints(ps) == 2);
  }
  {
    Solution2 sln;
    vector<Point> ps = {{0, 0}};
    assert(sln.maxPoints(ps) == 1);
  }
  {
    Solution2 sln;
    vector<Point> ps = {{0, 0}, {100, 10}, {100, 10}};
    assert(sln.maxPoints(ps) == 2);
  }
}
} // namespace _149