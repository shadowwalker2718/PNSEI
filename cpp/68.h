#pragma once

#include "henry.h"

namespace _68_2 {

struct Solution {
  vector<string> fullJustify(vector<string> &words, int maxwidth) {
    vector<string> r;
    int L = words.size();
    int start = 0;
    while (start < L) {
      int wordlen = 0, m = 0;
      while (start + m < L && wordlen + words[start + m].size() + m <= maxwidth)
        wordlen += words[start + m].size(), m++;
      string oneline(words[start]);
      int gap = m - 1, spaces = maxwidth - wordlen;
      for (int i = 0; i < gap; ++i) {
        if (start + m == L) {
          oneline += " ";
        } else {
          int x = spaces / gap, y = spaces % gap;
          oneline.append(x + (i < y), ' ');
        }
        oneline += words[start + i + 1];
      }
      if (m == 1 || start + m == L)
        oneline.append(maxwidth - oneline.size(), ' ');
      r.push_back(oneline);
      start += m;
    }
    return r;
  }
};

class Solution2 {
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

void test() {

  Solution2 s2;
  s2.findAnagrams("abacbabc", "abc");

  Solution sln;
  vector<string> r;

  {
    vector<string> vs = {"This",          "is", "an", "example", "of", "text",
                         "justification."};
    r = sln.fullJustify(vs, 16);
  }

  {
    vector<string> vs = {""};
    r = sln.fullJustify(vs, 2);
  }

  for (auto s : r) {
    cout << s << endl;
  }
}

} // namespace _68_2
