#pragma once
#include "henry.h"

// https://www.geeksforgeeks.org/word-wrap-problem-dp-19/

namespace _68 {

int Justify_Text_Line(string s, int len) {
  istringstream ss(s);
  vector<string> tokens;
  string e;
  while (getline(ss, e, ' ')) //consider all continuous spaces
    if(!e.empty())
      tokens.push_back(e);

  int L = tokens.size();
  int t = 0;
  for (int i = 0; i<L; ++i)
    t += tokens[i].size();
  if (t>len) return -1;
  int spaces = len - t;
  int groove = L - 1;
  if (groove <= 1) return 1;
  int extra = spaces%groove, d=extra;
  int r = 1, z=1;
  while (extra--) // Calculate groove choose extra
    r *= groove--;
  while(d){
    z*=d--;
  }
  return r/z;
}

struct Solution {                                                // 0ms
  vector<string> fullJustify(vector<string> &ws, int maxWidth) { // 0ms
    vector<string> r;
    int L = ws.size(), m = 0, sumlen = 0, i = 0;

    while (i < L) { // sumlen:该行所有单词长度和，m:该行单词数目=groove+1
      // 1. 找到填满一行需要的单词
      m = 0, sumlen = 0;
      // 1个单词0个空格,2个单词至少1个空格,3个单词至少2个空格
      while (i + m != L && m + sumlen + ws[i + m].size() <= maxWidth)
        sumlen += ws[i + m].size(), m++;

      // 2. 用找到的单词填满一行
      string s(ws[i]); // spaces:需要填的空格的数目
      int groove = m - 1, spaces = maxWidth - sumlen;
      for (int j = 0; j < groove; j++) {
        if (i + m == L) { // last line每个单词后只跟一个space
          s += " ";
        } else {
          s.append(spaces / groove + (j < spaces % groove), ' '); // append
        }
        s += ws[i + j + 1];
      }
      // edge case: one word in one line or lastline,填满一行
      if (m == 1 || i + m == L)
        s.append(maxWidth - s.size(), ' ');

      // 3. 把这一行加入最终结果
      r.push_back(s);

      i += m;
    }
    return r;
  }
};

void test() {
  int r=Justify_Text_Line("justify    th is line", 22);
  cout << r << endl;
  Solution sln;
  vector<string> v(
      {"This", "is", "an", "example", "of", "text", "justification."});
  assert(sln.fullJustify(v, 16) ==
         vector<string>(
             {"This    is    an", "example  of text", "justification.  "}));
}
} // namespace _68
