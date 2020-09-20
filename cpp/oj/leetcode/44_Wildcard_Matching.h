//
// Created by Henry Wu on 10/31/18.
//

#ifndef PNSEI_44_WILDCARD_MATCHING_H
#define PNSEI_44_WILDCARD_MATCHING_H

#include "henry.h"

namespace _44 {

/*
 * 外卡匹配和正则匹配最大的区别就是在星号的使用规则上,对于正则匹配来说,星号不能单独存在,前面必须要有一个字符,
 * 而星号存在的意义就是表明前面这个字符的个数可以是任意个,包括0个,那么就是说即使前面这个字符并没有在s中出现过也无
 * 所谓,只要后面的能匹配上就可以了.而外卡匹配就不是这样的,外卡匹配中的星号跟前面的字符没有半毛钱关系,如果前面
 * 的字符没有匹配上,那么直接返回false了,根本不用管星号.而星号存在的作用是可以表示任意的字符串,当然只是当匹配
 * 字符串缺少一些字符的时候起作用,当匹配字符串包含目标字符串没有的字符时,将无法成功匹配.*/
// https://leetcode.com/problems/wildcard-matching/
/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching
with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ?
or *. Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match
'b'. Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*'
matches the substring "dce". Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/

class Solution_REC { // TLE
public:
  bool isMatch(string s, string p) {
    // p.erase(unique(p.begin(), p.end(), [](char x, char y) { return x == y &&
    // x == '*'; }), p.end());
    return rec(s, p);
  }

  bool rec(string s, string p) {
    if (p.empty())
      return s.empty();
    if (s.empty()) { //"*****" can match ""
      return p.empty() || (p[0] == '*' && rec(s, p.substr(1)));
    }

    if (p[0] == '?') {
      return rec(s.substr(1), p.substr(1));
    } else if (p[0] == '*') {
      /*string np = p.substr(1);
      for (int i = 0; i <= s.size(); i++) {
        if (rec(s.substr(i), np))
          return true;
      }
      return false;*/
      return rec(s.substr(1), p);
    } else if (isalpha(p[0])) {
      return p[0] == s[0] && rec(s.substr(1), p.substr(1));
    }
  }
};

class Solution_REC_OPT { // TLE
public:
  bool isMatch(string s, string p) {
    if (p.empty())
      return s.empty();
    if (s.empty()) { // p="*****" can match s=""
      return p.empty() ||
             (p[0] == '*' &&
              isMatch(
                  s, p.substr(
                         1))); // p.back()=='*' && p.pop_back() && isMatch(s,p))
    }
    if (p[0] == '?') { // * can appear anywhere
      return isMatch(s.substr(1), p.substr(1));
    } else if (p[0] == '*') {
      return isMatch(s.substr(1), p) /*1+ char of s*/ ||
             isMatch(s, p.substr(1)) /*0 char of s*/;
    } else if (isalpha(p[0])) {
      return p[0] == s[0] && isMatch(s.substr(1), p.substr(1));
    }
  }
};

// https://www.youtube.com/watch?v=3ZDZ-N0EPV0
class Solution_DP {
public:
  bool isMatch(string s, string p) { // Bottom up DP
    int m = s.size(), n = p.size();
    // dp means `s from 0 to i matches p from 0 to j?`
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
    dp[0][0] = true; // empty s matches empty p
    for (int i = 1; i <= n;
         ++i) { // empty s matches multiple stars("*" || "**" ...)
      if (p[i - 1] == '*')
        dp[0][i] = dp[0][i - 1]; // p erase the last one char
    }
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n;
           ++j) { // j start from 1 because dp[*][0] are also false
        if (p[j - 1] == '*') {
          dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; // either left || top cell
        } else if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
          dp[i][j] = dp[i - 1][j - 1];
        } // else <=false
      }
    }
    return dp[m][n];
  }
};

} // namespace _44

#endif // PNSEI_44_WILDCARD_MATCHING_H
