#pragma once

#include "pnsei.h"

// https://leetcode.com/problems/valid-number/
// why it is correct?
// Regular Expression: [\s]*[-+]?(\\d+\\.?|\\.\\d+)\\d*(e[-+]?\\d+)?[\s]*
// Actual this is to write program according to regexp

namespace _65 {
class Solution {
public:
  bool isNumber(string s) {
    int i = 0, L = s.size();
    while (isspace(s[i]))
      i++;
    if (s[i] == '+' || s[i] == '-')
      i++;
    bool b = false;
    while (isdigit(s[i]))
      i++, b = true;
    if (s[i] == '.')
      i++;
    while (isdigit(s[i]))
      i++, b = true;
    if (s[i] == 'e' || s[i] == 'E') {
      if (!b)
        return false;
      b = false, i++;
      if (s[i] == '+' || s[i] == '-')
        i++;
      while (isdigit(s[i]))
        i++, b = true;
    }
    while (isspace(s[i]))
      i++;
    return b && i == s.size();
  }
};

void test() {
  Solution sln;
  assert(sln.isNumber("1E2") == true);
  cout << 1E2 << endl;
}
} // namespace _65