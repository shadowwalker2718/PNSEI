//
// Created by Henry Wu on 10/31/18.
//

#ifndef PNSEI_10_REGULAR_EXPRESSION_MATCHING_H
#define PNSEI_10_REGULAR_EXPRESSION_MATCHING_H

#include "henry.h"

/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

 Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

namespace _10 {

// https://leetcode.com/problems/regular-expression-matching/description/
// substr(N) - N could be the size of the string, but cannot more than that
class Solution {
public:
  bool isMatch(string s, string pattern) {
    // check p's size
    if (pattern.empty())
      return s.empty();
    /*else if (p.size() == 1) // cannot be `*`
      return s.size() == 1 and (p[0] == s[0] || p[0] == '.');*/
    if(s.empty()){ // if s empty, p .* || a*a*a*.*
      return pattern.empty() || (pattern[1]=='*' && isMatch(s, pattern.substr(2)));
    }

    if ('*' == pattern[1]) { // .*xxxxxxxxxxxx || a*xxxxxxxxxxxxxx
      // x* matches empty string || at least one character: x* -> xx*
      // *s is to ensure s is non-empty
      if (isMatch(s, pattern.substr(2))) { // [x*] matches 0 char
        return true; /////.*.*.*.*x
      } else //
        if (!s.empty() && (s[0] == pattern[0] || '.' == pattern[0]) && isMatch(s.substr(1), pattern)) { //[x*] matches 1+ char
        return true;
      } else {
        return false; // return for (abc, .*wq)
      }
    }else
      return !s.empty() &&
             (s[0] == pattern[0] || '.' == pattern[0]) &&
             isMatch(s.substr(1), pattern.substr(1));
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
        if (p[j - 1] == s[i - 1] || p[j - 1] == '.') { // a => a*
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
