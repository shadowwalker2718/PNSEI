#pragma once

#include "henry.h"

namespace _google_MaxWithOneFlip {

// http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=216404&page=1#pid2701309

/*public int findMaxWithFlip(int[] input) {
    if (input == null || input.length == 0)
        return 0;
    int maxLen = Integer.MIN_VALUE;
    int curLen = 0;
    int spareLen = 0;

    boolean zero = false;

    for (int i = 0; i < input.length; ++i) {
        if (input[i] == 1) {
            //curLen++;
            spareLen++;
        } else {
            maxLen = Math.max(maxLen, curLen + spareLen + 1);
            curLen = spareLen;
            spareLen = 0;
        }
    }
    maxLen = Math.max(maxLen, zero ? curLen + spareLen + 1 : curLen);
    return maxLen;
}*/

int findMaxWithOneFlip(vector<int> &v) { // T: O(N), S:O(N)
  if (v.empty())
    return 0;
  vector<int> r(1, 0);
  for (int i = 0; i < v.size(); ++i)
    if (v[i])
      if (r.back())
        r.back()++;
      else
        r.push_back(v[i]); //!!
    else
      r.push_back(0);
  r.push_back(0);

  int m = INT_MIN;
  for (int i = 1; i < r.size() - 1; ++i)
    if (r[i])
      m = max(m, r[i]);
    else
      m = max(m, r[i - 1] + 1 + r[i + 1]);
  return m;
}

int findMaxWithOneFlip2(vector<int> &v) { // buggy
  if (v.empty())
    return 0;
  int maxLen = INT_MIN;
  int curLen = 0;
  int spareLen = 0;

  bool zero = false;

  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == 1) {
      spareLen++;
    } else {
      maxLen = max(maxLen, curLen + spareLen + 1);
      curLen = spareLen;
      spareLen = 0;
      zero = true;
    }
  }
  maxLen = max(maxLen, zero ? curLen + spareLen + 1 : curLen);
  return maxLen;
}

void test() {

  vector<int> v = {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
                   1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
                   0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1};

  assert(findMaxWithOneFlip(v) == 16);
  // assert(findMaxWithOneFlip2(v) == 16);

  v = {};
  assert(findMaxWithOneFlip(v) == 0);
  // assert(findMaxWithOneFlip2(v) == 0);

  v = {0};
  assert(findMaxWithOneFlip(v) == 1);
  // assert(findMaxWithOneFlip2(v) == 1);

  v = {1};
  assert(findMaxWithOneFlip(v) == 1);
  // assert(findMaxWithOneFlip2(v) == 1);

  v = {0, 1};
  assert(findMaxWithOneFlip(v) == 2);
  // assert(findMaxWithOneFlip2(v) == 2);
}

} // namespace google