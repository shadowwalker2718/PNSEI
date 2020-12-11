#pragma once

#include "pnsei.h"

namespace _winner_tree {

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=216014&highlight=addepar
 * 2016(10-12月) 码农类General 硕士 全职 Addepar - 网上海投 - 技术电面  | Other | fresh grad应届毕业生
11.15号面的第一轮:
第一题:有n个数,需要比几次才能选出最大值,n-1,然后怎么证明......证明............证......怎么跟高数一样,这还需要证?这还能这么证......
 *
 * */

// http://stackoverflow.com/questions/13544476/how-to-find-max-and-MIN-in-array-using-minimum-comparisons
//
// 1. Pick 2 elements(a, b), compare them. (say a > b)
// 2. Update min by comparing (min, b) //
// 3. Update max by comparing (max, a) //
//
// This way you would do 3 comparisons for 2 elements, amounting to 3N/2 - 2 total comparisons for N elements.
// Should it not be ceil(3N/2.0) - 2 since we do not need to update min or max in the very first step?
pair<int, int> minmax(vector<int> v) {
  int compare_time=0;
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
      mx = v[0], mi = v[1], compare_time++;
    else
      mx = v[1], mi = v[0];
    start = 2;
  }
  for (int i = start; i < v.size() - 1; i += 2) {
    int s, b;
    compare_time++;
    if (v[i] > v[i + 1])
      s = v[i + 1], b = v[i];
    else
      s = v[i], b = v[i + 1];
    if (s < mi)
      mi = s;
    if (b > mx)
      mx = b;
    compare_time+=2;
  }
  cout << "v size:" << v.size() << ", compare_time:" << compare_time << endl;
  return {mi, mx};
}

int _2ndsmallest_v1(vector<int> v) { // 2N comparison
  if (v.empty())
    return INT_MAX;
  if (v.size() == 1)
    return v.front();
  int s1 = INT_MAX, s2 = INT_MAX;
  int count = 0;
  for (int i : v) {
    if (++count && i < s1)
      s2 = s1, s1 = i;
    else if (++count && i < s2)
      s2 = i;
  }
  cout << "size:" << v.size() << ", count:" << count << endl; // 100 elements, 191 comps
  return s2;
}

struct SecondSmallest {
  vector<vector<int>> dp; // store info of smallest in between [h,t]

  int count = 0;
#define MIN(x, y)                                                              \
  min((x), (y));                                                               \
  count++;

  const vector<int> v;
  SecondSmallest(const vector<int> &_v) : v(_v) {
    dp = vector<vector<int>>(v.size(), vector<int>(v.size(), INT_MAX));
  }

  int _2ndsmallest() { return _2ndsmallest(0, v.size() - 1); }

  // Use tournament tree to find 2nd smallest
  int _2ndsmallest(int h, int t) {
    if (t - h == 1) //?
      return v.front();
    if (t - h == 2) {
      int r = MIN(v[0], v[1]);
      return r;
    }
    int c1 = INT_MAX, c2 = INT_MAX;
    int R = smallest(h, t); // Root of the tournament tree
    int m = h + (t - h) / 2; // lower median
    if (R == smallest(h, m)) {
      c1 = _2ndsmallest(h, m);
      c2 = smallest(m + 1, t);
    } else if (R == smallest(m + 1, t)) {
      c1 = _2ndsmallest(m + 1, t);
      c2 = smallest(h, m);
    }
    if (c1 == INT_MAX)
      return c2;
    int r = MIN(c1, c2);
    return r;
  }

  int smallest() { return smallest(0, v.size() - 1); }

  int smallest(int h, int t) { // a recursive function
    if (dp[h][t] != INT_MAX) { // cache hit
      //cout << h << "," << t << endl;
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


  SecondSmallest sln(v);
  assert(sln._2ndsmallest() == 5);
  int r = v.size() + ceil(log2(v.size())) - 2;
  cout << "size:"<<v.size() <<",comp:"<< sln.comp_num() << endl;
  assert(sln.comp_num() == (v.size() + ceil(log2(v.size())) - 2));
  assert(sln.smallest() == 1);
}

} // namespace _winner_tree
