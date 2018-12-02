//
// Created by Henry Wu on 11/14/18.
//

#ifndef PNSEI_22_GENERATE_PARENTHESES_H
#define PNSEI_22_GENERATE_PARENTHESES_H

#include "henry.h"

namespace _22 {

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> r;
    string s;
    dfs(r, s, 0, n);
    return r;
  }

  // l is how many left is greater than right; n is matching number
  void dfs(vector<string> &vs, string s, int l, int n) {
    if (l == 0) {
      if (n == 0) {
        vs.push_back(s);
        return;
      } // base condition 1
      dfs(vs, s + '(', 1, n);
    } else {
      if (l > n || n == 0)
        return; //base condition 2
      dfs(vs, s + ")", l - 1, n - 1);
      dfs(vs, s + "(", l + 1, n);
    }
  }
};

void test() {
  Solution().generateParenthesis(3);
}
}


#endif //PNSEI_22_GENERATE_PARENTHESES_H
