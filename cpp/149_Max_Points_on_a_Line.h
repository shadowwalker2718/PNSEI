#pragma once

#include "henry.h"

/*
Even in modulo, the divisor cannot be 0.

[cling]$ 10%0
input_line_3:2:4: warning: remainder by zero is undefined [-Wdivision-by-zero]
 10%0
   ^~
*/


namespace _149 {
/*** Definition for a point.*/
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

int gcd(int x,int y){
  if (x==0) return y; // any number and 0 have gcd==that number.
  return gcd(y%x,x);
}

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
    // get all different pairs of points - combination requires ordered access
    for (int i = 0; i < points.size(); i++) {
      unordered_map<long long, int> count;
      int same = 1, mx = 0;
      for (int j = i + 1; j < points.size(); j++) {
        int x = points[i].x - points[j].x;
        int y = points[i].y - points[j].y;
        int g = gcd(x, y);
        if (g==0) { // g==0 means same points
          same++;
          continue;
        }
        x /= g, y /= g;
        long long slope_rep=((long long)(x) << 32) | y;
        mx = max(mx, ++count[slope_rep]);
      }
      result = max(result, mx + same);
    }
    return result;
  }

  int gcd(int x, int y) {
    int temp;
    while (y)
      temp = y, y = x % y, x = temp;
    return x;
  }
};


/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution3 {
public:
    int maxPoints(vector<Point> &points) { // 39ms
        int result = 0;
        unordered_set<int> duplicated_points;
        for(int i=0;i<points.size();i++){
            unordered_map<long long,int> count;
            int same = 0;
            int mx = 0;
            for(int j = i + 1; j < points.size(); j ++){ // Point of i < j
                if(duplicated_points.count(j))
                    continue;
                int x = points[i].x - points[j].x;
                int y = points[i].y - points[j].y;
                if(0==x and 0==y){  // same points
                    duplicated_points.emplace(j);
                    same ++;
                    continue;
                }
                int g = gcd(x, y);
                x /= g, y /= g;
                ++ count[((long long)(x)<<32)|y];
            }
            for(const auto& pr: count)
                mx=max(mx, pr.second);
            result=max(result, mx+same+1);
        }
        return result;
    }

    int gcd(int x, int y) {
        int temp;
        while (y)
            temp = y, y = x % y, x = temp;
        return x;
    }
};


void test() {
  //[[0,0],[1,1],[1,-1]]
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
