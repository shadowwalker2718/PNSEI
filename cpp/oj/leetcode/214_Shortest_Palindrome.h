#pragma once
#include "pnsei.h"

namespace _214 {
struct Solution {
  string shortestPalindrome_spurious_check(string s) {
    if (s.size() <= 1)
      return s;
    int r = 0;
    int hash1 = 0, hash2 = 0, BASE = 13, MOD = 1000000007, POW = 1;
    for (int i = 0; i < s.size(); ++i) {
      hash1 = hash1 * BASE + s[i];
      hash2 = hash2 + s[i] * POW;
      if (hash1 == hash2) {
        int j = 0, k = i, spurious = 0;
        while (j < k)
          if (s[j++] != s[k--]) {
            spurious = 1;
            break;
          }
        if (spurious == 0)
          r = i;
      }
      POW *= BASE;
    }
    string tmp = s.substr(r + 1);
    reverse(tmp.begin(), tmp.end());
    return tmp + s;
  }

  string shortestPalindrome(string s){
    if (s.size() <= 1) return s;
    int r = 0, hash1 = 0, hash2 = 0, BASE=37, POW=1;//
    for (int i = 0; i < s.size(); ++i) {
      hash1 = hash1*BASE+s[i];
      hash2 = hash2 + s[i] * POW;
      if (hash1 == hash2)
        r = i;
      POW *= BASE;
    }
    string tmp = s.substr(r+1);//
    reverse(tmp.begin(), tmp.end());
    return tmp + s;
  }
};

void test() {
  Solution sln;
  assert(sln.shortestPalindrome("aacecaaa") == "aaacecaaa");
  assert(sln.shortestPalindrome_spurious_check("aba") == "aba");
  assert(sln.shortestPalindrome_spurious_check("abc") == "cbabc");
}
} // namespace _214