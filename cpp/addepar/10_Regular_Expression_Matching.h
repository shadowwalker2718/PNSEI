//
// Created by root on 10/31/18.
//

#ifndef PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
#define PNSEI_10_REGULAR_EXPRESSION_MATCHING_H

#include "henry.h"

namespace _10 {

// https://leetcode.com/problems/regular-expression-matching/description/
// substr(N) - N could be the size of the string, but cannot more than that
class Solution {
public:
  bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();
    if (p.size() == 1) return s.size() == 1 and (p[0] == s[0] or p[0] == '.');

    if ('*' == p[1])
      // x* matches empty string or at least one character: x* -> xx*
      // *s is to ensure s is non-empty
      if (isMatch(s, p.substr(2))) { // [x*] matches 0 char
        return true;
      } else if (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)) { //[x*] matches 1 char
        return true;
      } else {
        return false;
      }
    else
      return !s.empty() &&
             (s[0] == p[0] || '.' == p[0]) &&
             isMatch(s.substr(1), p.substr(1));
  }
};

// https://www.youtube.com/watch?v=l3hda49XcDE
class Solution_DP {
public:
  bool isMatch(const string& s, const string& p) {
    const int M = s.size(), N = p.size();
    bool dp[M + 1][N + 1] = {};
    dp[0][0] = true;
    for (int i = 1; i <= N; ++i) { // empty s matches "*" or "**" ...
      if (p[i - 1] == '*' and i>=2)
        dp[0][i] = dp[0][i - 2];
    }

    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= N; j++) {
        if (s[i - 1] == p[j - 1] or p[j - 1] == '.') {
          dp[i][j] = dp[i - 1][j - 1];
        }else if (p[j - 1] == '*') {
          dp[i][j] = (j - 2 >= 0 and dp[i][j - 2]) or
              ((s[i - 1] == p[j - 2] or p[j - 2] == '.') and dp[i - 1][j]);
        }
      }
    }
    return dp[M][N];
  }
};

void test() {
  string s = "mississippi";
  string p = "mis*is*p*.";
  Solution sln;
  assert(sln.isMatch(s, p) == false);

  Solution_DP sln2;
  s="aa", p="a*";
  assert(sln2.isMatch(s, p) == 1);
}
}

#endif //PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
