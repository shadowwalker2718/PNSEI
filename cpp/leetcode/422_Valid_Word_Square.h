#pragma once

#include "henry.h"

namespace _422 {

class Solution {
public:
  bool validWordSquare(vector<string> &w) {
    for (int i = 0; i < w.size(); i++)
      for (int j = 0; j < w[i].size(); j++)
        if (j >= w.size() || i >= w[j].size() || w[i][j] != w[j][i])
          return false;
    return true;
  }
};

void test() {
  Solution s;
  VS v = {"papa", "amazon", "papa", "azan"};
  assert(!s.validWordSquare(v));
}
} // namespace _422