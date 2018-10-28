#pragma once

#include "henry.h"

namespace lc_438 {

class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    if (s.empty())
      return {};
    vector<int> r;
    int m[128] = {};
    for (char c : p)
      ++m[c];
    int hd = 0, tl = 0, L = s.size(), N = p.size(), cnt = N;
    while (tl < L) {
      if (m[s[tl]] > 0)
        --cnt;
      m[s[tl]]--;
      if (cnt == 0)
        r.push_back(hd);
      if (tl - hd + 1 == N) { // move head
        ++m[s[hd]];
        if (m[s[hd]] > 0) {
          ++cnt;
        }
        ++hd;
      }
      tl++;
    }
    return r;
  }
};

class Solution2 {
public:
  vector<int> findAnagrams(string s, string p) {
    if (s.empty())
      return {};
    vector<int> res, m1(128, 0), m2(128, 0);
    int N = p.size();
    for (int i = 0; i < N; ++i)
      ++m1[s[i]], ++m2[p[i]];
    if (m1 == m2)
      res.push_back(0);
    for (int i = N; i < s.size(); ++i) {
      ++m1[s[i]], --m1[s[i - N]]; // Add one, Subtract one
      if (m1 == m2)               // compare two vectors
        res.push_back(i - N + 1);
    }
    return res;
  }
};

void test() {
  Solution sln;
  sln.findAnagrams("abacbabc", "abc");
}

} // namespace lc_438
