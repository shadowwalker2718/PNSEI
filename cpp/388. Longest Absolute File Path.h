#pragma once

#include "henry.h"

namespace _388 {

// http://www.cnblogs.com/grandyang/p/5806493.html

class Solution {
public:
  int lengthLongestPath(string input) {
    int res = 0, L = input.size(), level = 0;
    unordered_map<int, int> m{{0, 0}};
    for (int i = 0; i < L; ++i) {
      int start = i;
      while (i < L && input[i] != '\n' && input[i] != '\t')
        ++i;
      if (i >= L || input[i] == '\n') {
        string t = input.substr(start, i - start);
        if (t.find('.') != string::npos) { // dir
          res = max(res, m[level] + (int)t.size());
        } else {
          ++level;
          m[level] = m[level - 1] + (int)t.size() + 1;
        }
        level = 0;
      } else {
        ++level;
      }
    }
    return res;
  }
};

void test() {
  string s = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\t"
             "subsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
  Solution sln;
  assert(sln.lengthLongestPath(s) == 32);
}
} // namespace _388
