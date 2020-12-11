#pragma once

#include "pnsei.h"

namespace _reverse_string {

struct Solution {
  void reverseWords(string &s) { // Inplace Method
    // clean string with two pointers
    int k = 0, c = 0, L = s.size();
    for (int i = 0; i < L; ++i) {
      if (isspace(s[i]))
        if (++c >= 2)
          continue;
        else
          c = 0;
      s[k++] = s[i];
    }
    s = s.substr(0, k);
    cout << '|' << s << '|' << endl;
    //////////////////////////////////////////////

    // reverse twice
    auto reverse_ = [](string &s, int i, int j) {
      while (i < j)
        swap(s[i++], s[j--]);
    };
    reverse_(s, 0, s.size() - 1);

    int prev = -1;
    int i = 0;
    for (; i < s.size() + 1; ++i) {
      if (isspace(s[i]) || i == s.size()) {
        if (prev >= 0) {
          reverse_(s, prev, i - 1);
          prev = -1;
        }
      } else {
        if (prev == -1)
          prev = i;
      }
    }

    // strip string
    while (s.back() == ' ')
      s.pop_back();
    while (s.front() == ' ')
      s.erase(s.begin());
  }
};

void test() {
  Solution sln;
  string s = "   a  b ";
  sln.reverseWords(s);
  assert(s == "b a");
}

} // namespace _reverse_string
