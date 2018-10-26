#pragma once

#include "henry.h"

namespace _winner_tree {

// http://stackoverflow.com/questions/13544476/how-to-find-max-and-MIN-in-array-using-minimum-comparisons
pair<int, int> minmax(vector<int> v) {
  if (v.empty())
    return {INT_MAX, INT_MAX};
  if (v.size() == 1)
    return {v.front(), v.front()};
  int mi = INT_MAX, mx = INT_MIN;
  int start;
  if (v.size() & 1) {
    mi = mx = v.front(), start = 1;
  } else {
    if (v[0] > v[1])
      mx = v[0], mi = v[1];
    else
      mx = v[1], mi = v[0];
    start = 2;
  }
  for (int i = start; i < v.size() - 1; i += 2) {
    int s, b;
    if (v[i] > v[i + 1])
      s = v[i + 1], b = v[i];
    else
      s = v[i], b = v[i + 1];
    if (s < mi)
      mi = s;
    if (b > mx)
      mx = b;
  }
  return {mi, mx};
}

int _2ndsmallest_v1(vector<int> v) { // 2N comparison
  if (v.empty())
    return INT_MAX;
  if (v.size() == 1)
    return v.front();
  int s1 = INT_MAX, s2 = INT_MAX;
  cout << v.size() << endl;
  int count = 0;
  for (int i : v) {
    if (++count && i < s1)
      s2 = s1, s1 = i;
    else if (++count && i < s2)
      s2 = i;
  }
  cout << count << endl; // 100 elements, 191 comps
  return s2;
}

struct SecondSmallest {
  vector<vector<int>> dp;
  // vector<vector<int>> dp2;
  int count = 0;
#define MIN(x, y)                                                              \
  min((x), (y));                                                               \
  count++;
  const vector<int> v;
  SecondSmallest(const vector<int> &_v) : v(_v) {
    dp = vector<vector<int>>(v.size(), vector<int>(v.size(), INT_MAX));
    // dp2 = vector<vector<int>>(v.size(), vector<int>(v.size(), INT_MAX));
  }

  int _2ndsmallest() { return _2ndsmallest(0, v.size() - 1); }

  int _2ndsmallest(int h, int t) {
    /*if (dp2[h][t] != INT_MAX) {
      cout << h << "-" << t << endl;
      return dp2[h][t];
    }*/
    if (t - h == 1)
      // return dp2[h][t] = v.front();
      return v.front();
    if (t - h == 2) {
      /*dp2[h][t] =  MIN(v[0], v[1]);
      return dp2[h][t];*/
      int r = MIN(v[0], v[1]);
      return r;
    }
    int c1 = INT_MAX, c2 = INT_MAX;
    int R = smallest(h, t);
    int m = h + (t - h) / 2;
    if (R == smallest(h, m)) {
      c1 = _2ndsmallest(h, m);
      c2 = smallest(m + 1, t);
    } else if (R == smallest(m + 1, t)) {
      c1 = _2ndsmallest(m + 1, t);
      c2 = smallest(h, m);
    }
    if (c1 == INT_MAX)
      // return dp2[h][t] = c2;
      return c2;
    /*dp2[h][t] = MIN(c1, c2);
    return dp2[h][t];*/
    int r = MIN(c1, c2);
    return r;
  }

  int smallest() { return smallest(0, v.size() - 1); }

  int smallest(int h, int t) {
    if (dp[h][t] != INT_MAX) {
      cout << h << "," << t << endl;
      return dp[h][t];
    }
    if (h == t)
      return v[h];
    dp[h][t] =
        MIN(smallest(h, h + (t - h) / 2), smallest(h + (t - h) / 2 + 1, t));
    return dp[h][t];
  }

  int comp_num() {
    cout << count << endl;
    return count;
  }
};

void test() {
  vector<int> v = {
      553, 518, 358, 192, 727, 800, 265, 133, 696, 545, 107, 245, 203, 809, 115,
      746, 98,  343, 827, 707, 671, 273, 890, 716, 49,  984, 204, 595, 865, 406,
      219, 538, 582, 264, 140, 1,   892, 625, 912, 110, 165, 169, 256, 133, 667,
      649, 262, 362, 515, 612, 109, 595, 346, 572, 242, 408, 976, 360, 583, 315,
      235, 376, 327, 527, 178, 342, 479, 286, 675, 561, 641, 595, 276, 977, 422,
      648, 479, 427, 997, 945, 856, 46,  185, 924, 564, 515, 470, 756, 5,   187,
      686, 799, 443, 407, 334, 171, 367, 830, 672, 362};
  assert((minmax({39, 34, 52, 14, 40, 77, 83, 12, 41, 78}) ==
          pair<int, int>({12, 83})));

  assert((minmax({39, 34, 52, 14, 40, 77, 83, 12, 41}) ==
          pair<int, int>({12, 83})));

  assert((_2ndsmallest_v1(v) == 5));

  // v = { 39, 34, 52, 14, 40, 77, 83, 12, 41 };
  SecondSmallest sln(v);
  assert(sln._2ndsmallest() == 5);
  int r = v.size() + ceil(log2(v.size())) - 2;
  cout << r << endl;
  cout << sln.comp_num() << endl;
  assert(sln.comp_num() == (v.size() + ceil(log2(v.size())) - 2));
  // assert(sln.smallest()==1);
}

} // namespace _winner_tree
