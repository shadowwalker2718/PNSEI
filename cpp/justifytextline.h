#pragma once
#include "henry.h"

namespace justify_text_line {

vector<string> split_space(string s) {
  vector<string> r;
  int pos = 0;
  while ((pos = s.find(' ')) != string::npos) {
    string t = s.substr(0, pos);
    r.push_back(t);
    s.erase(0, pos + 1);
  }
  if (!s.empty())
    r.push_back(s);
  return r;
}

int comb(int n, int k) { // C(n,k)
  int r = 1;
  while (k <= n)
    r *= k++;
  return r;
}

int Justify_Text_Line(string s, int len) {
  istringstream ss(s);
  vector<string> tokens;
  string e;
  while (getline(ss, e, ' '))
    if (!e.empty())
      tokens.push_back(e);

  int L = tokens.size();
  int t = 0;
  for (int i = 0; i < L; ++i)
    t += tokens[i].size();
  if (t > len)
    return -1;
  int spaces = len - t;
  int gap = L - 1;
  if (gap <= 1)
    return 1;
  int k = spaces % gap;
  int r = 1;
  while (k <= gap)
    r *= k++;
  return r;
}

void test() {
  /*int len = 0, num = 0;
  cin >> len;
  cin >> num;
  cin.ignore();
  for (int i = 0; i<num; i++) {
    string s;
    getline(cin, s, '\n');
    int r=f(s, len);
  }
  return 0;*/
  assert(Justify_Text_Line("justify this line", 20) == 2);
  assert(Justify_Text_Line("justify   this line", 20) == 2);
  assert(Justify_Text_Line("justify   this           line", 20) == 2);
  assert(Justify_Text_Line("justify", 20) == 1);
  assert(Justify_Text_Line("justify  ", 20) == 1);
  assert(Justify_Text_Line("justify  this", 20) == 1);
  assert(Justify_Text_Line("justify  this very very long line", 20) == -1);
}

} // namespace justify_text_line