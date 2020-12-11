#pragma once

#include "pnsei.h"

namespace _34 {
struct Solution {
  vector<int> searchRange(vector<int> &nums, int target) { // O(LogN)
    vector<int> r = {-1, -1};
    if (nums.empty())
      return r;
    int lh = 0, rh = 0, L = nums.size(), lt = L - 1, rt = lt;
    while (lh <= lt) { // 1st one >=8
      int m = lh + (lt - lh) / 2;
      if (target <= nums[m])
        lt = m - 1; //等于的时候也不要停继续往小的方向走
      else
        lh = m + 1;
    } // lh
    cout << lh << "," << lt << endl;
    while (rh <= rt) { // last one <=8
      int m = rh + (rt - rh) / 2;
      // if (target < nums[m]) rt = m - 1;
      // else rh = m + 1; //等于的时候也不要停继续往大的方向走
      if (target >= nums[m])
        rh = m + 1;
      else
        rt = m - 1;
    } // rt
    cout << rh << "," << rt <<endl;
    if (lh <= rt)
      r[0] = lh, r[1] = rt;
    return r;
  }
};

#if 0
int _1st_greater(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] <= T)
      h = m + 1;
    else
      t = m - 1;
  }
  if (h < v.size())
    return h;
  return -1;
}
int _1st_equal_or_greater(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] < T)
      h = m + 1;
    else
      t = m - 1;
  }
  if (h < v.size())
    return h;
  return -1;
}
int _1st_equal(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] < T)
      h = m + 1;
    else
      t = m - 1;
  }
  if (h < v.size() && v[h] == T)
    return h;
  return -1;
}

//////////////////////////////////////////////////////////

int _last_less(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] < T)
      h = m + 1;
    else
      t = m - 1; //等于的时候应用这个logic
  }
  if (t < v.size())
    return t;
  return -1;
}

int _last_equal(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] <= T)
      h = m + 1;
    else
      t = m - 1;
  }
  if (t < v.size() && v[t] == T)
    return t;
  return -1;
}

int _last_equal_or_less(const vector<int> &v, int T) {
  int h = 0, t = v.size() - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (v[m] <= T)
      h = m + 1;
    else
      t = m - 1;
  }
  if (t < v.size())
    return t;
  return -1;
}
#else
    int _1st_greater(const vector<int> &v, int T) {
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h) / 2;
        if (v[m] <= T)
          h = m + 1;
        else
          t = m;
      }
      if (h < v.size() && v[h]>T)
        return h;
      return -1;
    }
    int _1st_equal_or_greater(const vector<int> &v, int T) {
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h) / 2;
        if (v[m] < T)
          h = m + 1;
        else
          t = m;
      }
      if (h < v.size() && v[h]>=T)
        return h;
      return -1;
    }
    int _1st_equal(const vector<int> &v, int T) {
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h) / 2;
        if (v[m] < T)
          h = m + 1;
        else if(v[m]>T)
          t = m - 1;
        else
          t=m;
      }
      if (h < v.size() && v[h] == T)
        return h;
      return -1;
    }
    int _last_less(const vector<int> &v, int T) { // v:{1,2}, T: 12
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h + 1) / 2; //lower median
        if (v[m] < T)
          h = m;
        else
          t = m - 1; //等于的时候应用这个logic
      }
      if (h < v.size() && v[h]<T)
        return h;
      return -1;
    }
    int _last_equal(const vector<int> &v, int T) {
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h + 1) / 2;
        if (v[m] < T)
          h = m + 1;
        else if(v[m]>T)
          t = m - 1;
        else
          h=m;
      }
      if (h < v.size() && v[t] == T)
        return h;
      return -1;
    }
    int _last_equal_or_less(const vector<int> &v, int T) {
      int h = 0, t = v.size() - 1;
      while (h < t) {
        int m = h + (t - h + 1) / 2;
        if (v[m] <= T)
          h = m;
        else
          t = m - 1;
      }
      if (h < v.size() && v[h]<=T)
        return h;
      return -1;
    }
#endif





void test() {
  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, 5},
                                {{2, 3, 5, 6, 12, 13, 17}, 5},
                                {{13, 13, 15, 16, 112, 113, 117}, 0},
                                {{1, 2, 3, 4, 5, 6, 7}, -1}};

    for (auto &pr : ts) {
      int r=_1st_greater(pr.first, 12);
      assert((r == pr.second));
    }
  }

  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, 5},
                                {{2, 3, 5, 6, 12, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 12, 12, 13, 17}, 4},
                                {{13, 13, 15, 16, 112, 113, 117}, 0},
                                {{1, 2, 3, 4, 5, 6, 7}, -1}};

    for (auto &pr : ts) {
      assert((_1st_equal_or_greater(pr.first, 12) == pr.second));
    }
  }

  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, -1},
                                {{2, 3, 5, 6, 12, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 12, 12, 13, 17}, 4},
                                {{13, 13, 15, 16, 112, 113, 117}, -1},
                                {{1, 2, 3, 4, 5, 6, 7}, -1},
                                {{11, 13}, -1},
                                {{11}, -1},
                                {{12}, 0},
                                {{12, 12}, 0},
                                {{1, 2}, -1},
                                {{}, -1}};

    for (auto &pr : ts) {
      assert((_1st_equal(pr.first, 12) == pr.second));
    }
  }

  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 13, 17}, 3},
                                {{2, 3, 5, 6, 12, 12, 12, 13, 17}, 3},
                                {{13, 13, 15, 16, 112, 113, 117}, -1},
                                {{1, 2, 3, 4, 5, 6, 7}, 6},
                                {{11, 13}, 0},
                                {{11}, 0},
                                {{12}, -1},
                                {{12, 12}, -1},
                                {{1, 2}, 1},
                                {{}, -1}};

    for (auto &pr : ts) {
      assert((_last_less(pr.first, 12) == pr.second));
    }
  }

  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, -1},
                                {{2, 3, 5, 6, 12, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 12, 12, 13, 17}, 6},
                                {{13, 13, 15, 16, 112, 113, 117}, -1},
                                {{1, 2, 3, 4, 5, 6, 7}, -1},
                                {{11, 13}, -1},
                                {{11}, -1},
                                {{12}, 0},
                                {{12, 12}, 1},
                                {{1, 2}, -1},
                                {{}, -1}};

    for (auto &pr : ts) {
      assert((_last_equal(pr.first, 12) == pr.second));
    }
  }

  {
    map<vector<int>, int> ts = {{{2, 3, 5, 6, 11, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 13, 17}, 4},
                                {{2, 3, 5, 6, 12, 12, 12, 13, 17}, 6},
                                {{13, 13, 15, 16, 112, 113, 117}, -1},
                                {{1, 2, 3, 4, 5, 6, 7}, 6},
                                {{11, 13}, 0},
                                {{11}, 0},
                                {{12}, 0},
                                {{12, 12}, 1},
                                {{1, 2}, 1},
                                {{}, -1}};

    for (auto &pr : ts) {
      assert((_last_equal_or_less(pr.first, 12) == pr.second));
    }
  }

  Solution sln;
  {
    vector<int> v = {1, 2, 3, 8, 8, 9, 10};
    assert(sln.searchRange(v, 8) == vector<int>({3,4}));
  }
  {
    vector<int> v = {1, 2, 3, 5, 7, 9, 10};
    assert(sln.searchRange(v, 8) == vector<int>({-1,-1}));
  }
}
} // namespace _34