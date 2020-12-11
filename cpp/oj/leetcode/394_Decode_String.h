#pragma once
#include "pnsei.h"

namespace _394 {
class Solution {
public:
  string decodeString(string s) {
    vector<string> buf(1);
    vector<int> ms; // multipliers
    int status = 0;
    for (char c : s) {
      if (status == 0) {
        if (isdigit(c))
          ms.push_back(c - '0'), status = 1;
        else if (isalpha(c))
          buf.back() += c;
        else if (c == ']')
          goto _2_close_bracket;
      } else if (status == 1) {
        if (isdigit(c))
          ms.back() = ms.back() * 10 + c - '0';
        else if (c == '[')
          buf.push_back(""), status = 2;
      } else if (status == 2) {
        if (isdigit(c))
          status = 1, ms.push_back(c - '0');
        else if (isalpha(c))
          buf.back() += c;
        else if (c = ']') {
        _2_close_bracket:
          while (ms.back()--)
            buf.rbegin()[1] += buf.back();
          ms.pop_back(), buf.pop_back(), status = 0;
        }
      }
    }
    return buf.front();
  }
};

class Solution2 {
public:
  string DFS(string s, int &k) {
    string ans;
    int cnt = 0;
    while (k < s.size()) {
      if (isdigit(s[k]))
        cnt = cnt * 10 + (s[k++] - '0');
      else if (s[k] == '[') {
        string tem = DFS(s, ++k);
        while (cnt)
          ans += tem, cnt--;
      } else if (s[k] == ']') {
        k++;
        return ans;
      } else
        ans += s[k++];
    }
    return ans;
  }

  string decodeString(string s) {
    int k = 0;
    return DFS(s, k);
  }
};

class Solution3 {
public:
  string decodeString(string s) {
    int i = 0;
    return rec(s, i);
  }
  string rec(const string &s, int &i) {
    string r;
    int m = 0;
    for (; i < s.size(); i++) {
      if (isalpha(s[i]))
        r += s[i];
      else if (isdigit(s[i]))
        m = m * 10 + s[i] - '0';
      else if (s[i] == '[') {
        i++;
        string t = rec(s, i);
        while (m)
          r += t, m--;
      } else if (s[i] == ']')
        return r;
    }
    return r;
  }
};

void test() {
  Solution3 s;
  string t = "3[a]2[bc]";
  assert(s.decodeString(t) == "aaabcbc");
  t = "3[a2[c]]";
  assert(s.decodeString(t) == "accaccacc");
  t = "sd2[f2[e]g]i";
  assert(s.decodeString(t) == "sdfeegfeegi");
  t = "10[ab]";
  assert(s.decodeString(t) == "abababababababababab");
}

} // namespace _394
