#pragma once

#include "henry.h"

namespace _shortest_non_substring {

// 1. string to integer with base 2
// 2. int to binary conversion
string shortest(string s) {
  for (int i = 1; i <= s.size(); ++i) {
    set<string> st;
    int h = 0;
    while (h + i <= s.size()) {
      if (st.size() == (1 << i))
        break;
      st.insert(s.substr(h, i)), h++;
    }
    if (st.size() != (1 << i)) {
      auto it = st.begin();
      for (int g = 0; g < (1 << i); ++g) {
        if (it == st.end() || stoi(*it, 0, 2) != g) {
          string r(i, '0');
          while (g)
            r[--i] = (g & 1) ? '1' : '0', g >>= 1;
          return r;
        }
        ++it;
      }
    }
  }
  return "";
}

void test() {
  assert(shortest("") == "");
  assert(shortest("0") == "1");
  assert(shortest("1") == "0");
  assert(shortest("01000010") == "11");
  assert(shortest("000000") == "1");
  assert(shortest("111111") == "0");
  assert(shortest("111011") == "00");
  cout << shortest("11010100000001") << endl;
  cout << shortest("011010100000001") << endl;
  cout << shortest("0111010100000001") << endl;
}

} // namespace _shortest_non_substring
