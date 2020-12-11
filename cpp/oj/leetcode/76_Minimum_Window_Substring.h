#pragma once

#include "pnsei.h"

namespace minwindowsub {
struct Solution {
  string minWindow(string s, string t) {
    unordered_map<char, int> mp;
    for (char now : t)
      mp[now]++; // counter

    int count = mp.size(); // unique char #
    int j = 0, ans = INT_MAX;
    string res;
    for (int i = 0; i < s.size(); i++) { // loop through s
      if (mp.count(s[i]) == 0) {
        continue;
      }
      while (count > 0 && j < s.size()) {
        if (mp.count(s[j]) == 0) {
          j++;
          continue;
        }
        mp[s[j]]--;
        if (mp[s[j]] == 0)
          count--;
        j++;
      }
      if (count == 0)
        if (j - i < ans)
          ans = j - i, res = s.substr(i, ans);
      if (mp[s[i]] == 0)
        count++;
      mp[s[i]]++;
    }
    return res;
  }
};

struct Solution2 {
  string minWindow(string s, string t) {
    // int m[128] = {};
    unordered_map<char, int> m;
    for (auto c : t)
      m[c]++; // m is a dynamic counter
    int counter = t.size(), hd = 0, tl = 0, len = INT_MAX, h = 0;
    while (tl < s.size()) {
      char dc = s[tl];
      if (m[s[tl]] > 0)
        counter--; // in t
      m[s[tl]]--;
      while (counter == 0) { // valid window is found
        if (tl - hd < len) {
          h = hd;
          len = tl - hd + 1;
        }
        dc = s[hd];
        if (m[s[hd]] == 0) {
          counter++; // make it invalid
        }
        m[s[hd]]++;
        hd++;
      }
      tl++;
    }
    return len == INT_MAX ? "" : s.substr(h, len);
  }
};

void test() {
  Solution2 sln2;
  assert(sln2.minWindow("bacbbaxca", "aba") == "baxca");
  Solution sln;
  assert(sln.minWindow("acbbaca", "aba") == "baca");
}
} // namespace minwindowsub
