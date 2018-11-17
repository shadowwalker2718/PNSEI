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
    // check p's size
    if (p.empty()) return s.empty();
    /*else if (p.size() == 1) // cannot be `*`
      return s.size() == 1 and (p[0] == s[0] || p[0] == '.');*/
    if(s.empty()){ // if s empty, p .* || a*a*a*.*
      return p.empty() || (p[1]=='*' && isMatch(s, p.substr(2)));
    }

    if ('*' == p[1]) { // .*xxxxxxxxxxxx || a*xxxxxxxxxxxxxx
      // x* matches empty string || at least one character: x* -> xx*
      // *s is to ensure s is non-empty
      if (isMatch(s, p.substr(2))) { // [x*] matches 0 char
        return true; /////.*.*.*.*x
      } else //
        if (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)) { //[x*] matches 1+ char
        return true;
      } else {
        return false; // return for (abc, .*wq)
      }
    }else
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
    VVB dp(M + 1, VB(N + 1)); // matching result cache, index is size/length
    dp[0][0] = true;
    for (int i = 1; i <= N; ++i) { // empty s matches "a*" || "a*.*" ...
      if (p[i - 1] == '*' && i>=2)
        dp[0][i] = dp[0][i - 2]; // '' => '.*' || 'a*'
    }

    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= N; j++) {
        if (s[i - 1] == p[j - 1] || p[j - 1] == '.') { // a => a*
          dp[i][j] = dp[i - 1][j - 1];
        }else if (p[j - 1] == '*') {
#ifdef COMPACTCODE
          dp[i][j] = (j>=2 && dp[i][j - 2]) ||
              ((s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
#else
          dp[i][j] = (j>=2 && dp[i][j - 2]); // match 0 char
          if (s[i - 1] == p[j - 2] || p[j - 2] == '.'){ // match 1+ char but no erase in p, '' => '' true
            //dp[i][j] |= dp[i - 1][j]; // |= works but not ||=
              dp[i][j] = dp[i][j] | dp[i - 1][j];
          }
#endif
        }
      }
    }
    return dp[M][N];
  }
};

void test() {
  Solution    sln;
  Solution_DP sln2;

  string s = "mississippi";
  string p = "mis*is*p*.";
  assert(sln.isMatch(s, p) == sln2.isMatch(s, p));

  s="aa", p="a*";
  assert(sln2.isMatch(s, p) == 1);

  // invalid example as we require all inputs are valid
  //s="aa", p="*a";
  //assert(sln2.isMatch(s, p) == 1);
}
}

#endif //PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
