#pragma once
#include "henry.h"

/* http://hzwer.com/1905.html

http://sxysxy.org/blogs/45
https://oi.men.ci/scoi2003-fold/
*/

namespace _bzoj1090 {

class solution {
  string s;
  vector<vector<int>> results;

  bool EdgeCase(int l, int r, int cl, int cr) {
    if ((r - l + 1) % (cr - cl + 1) != 0)
      return 0;
    for (int i = l; i <= r; i++)
      if (s[i] != s[(i - l) % (cr - cl + 1) + cl])
        return 0;
    return 1;
  }

  int IntLen(int x) {
    int t = 0;
    while (x) {
      x /= 10;
      t++;
    }
    return t;
  }

  int dp(int l, int r) {
    if (l == r)
      return 1;
    if (results[l][r])
      return results[l][r];
    int t = r - l + 1;
    for (int i = l; i < r; i++) {
      t = min(t, dp(l, i) + dp(i + 1, r));
      if (EdgeCase(i + 1, r, l, i))
        t = min(t, dp(l, i) + 2 + IntLen((r - i) / (i - l + 1) + 1));
    }
    return results[l][r] = t;
  }

public:
  int run(const string &s_) {
    s = s_;
    int L = s.size();
    results = vector<vector<int>>(L, vector<int>(L, 0));
    return dp(0, L - 1);
  }
};

void test() {

  {
    string s = "aaabcabcbc";
    solution sln;
    int r = sln.run(s);
    assert(r == 10);
  }

  {
    string s = "aaaaaaaabcabcbc";
    solution sln;
    int r = sln.run(s);
    assert(r == 11); // 8[a]bcabcbc
  }

  {
    string s = "aabcabcbc";
    solution sln;
    int r = sln.run(s);
    assert(r == 9);
  }

  {
    string s = "aaaaaaaaaa";
    solution sln;
    int r = sln.run(s);
    assert(r == 5);
  }

  {
    string s = "abcabcabcabcabcabcabc";
    solution sln;
    int r = sln.run(s); // 7[abc]
    assert(r == 6);
  }
}
} // namespace _bzoj1090

/*

The first formula has a loophole:

Say 'abc'*3 + 'abc'*4 will ended with "abc6[abc]"

In [10]: s='2[a]bca2[bc]'

In [11]: s
Out[11]: '2[a]bca2[bc]'

In [12]: len(s)
Out[12]: 12

In [13]: a='a2[abc]bc'

In [14]: len(a)
Out[14]: 9
*/