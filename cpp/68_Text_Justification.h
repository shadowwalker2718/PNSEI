#pragma once
#include "henry.h"

namespace _68 {

int Justify_Text_Line(string s, int len) {
  istringstream ss(s);
  vector<string> tokens;
  string e;
  while (getline(ss, e, ' ')) //注意如果有多个空格要忽略空格
    if(!e.empty())
      tokens.push_back(e);

  int L = tokens.size();
  int t = 0;
  for (int i = 0; i<L; ++i)
    t += tokens[i].size();
  if (t>len) return -1;
  int spaces = len - t;
  int gap = L - 1;
  if (gap <= 1) return 1;
  int k = spaces%gap;
  int r = 1;
  while (k <= gap) // Calculate n choose k
    r *= k++;
  return r;
}

struct Solution {                                                // 0ms
  vector<string> fullJustify(vector<string> &ws, int maxWidth) { // 0ms
    vector<string> r;
    int L = ws.size(), m = 0, sumlen = 0, i = 0;

    while (i < L) { // sumlen:该行所有单词长度和，m:该行单词数目=gap+1
      // 1. 找到填满一行需要的单词
      m = 0, sumlen = 0;
      // 1个单词0个空格,2个单词至少1个空格,3个单词至少2个空格
      while (i + m != L && m + sumlen + ws[i + m].size() <= maxWidth)
        sumlen += ws[i + m].size(), m++;

      // 2. 用找到的单词填满一行
      string s(ws[i]); // spaces:需要填的空格的数目
      int gap = m - 1, spaces = maxWidth - sumlen;
      for (int j = 0; j < gap; j++) {
        if (i + m == L) { // last line每个单词后只跟一个space
          s += " ";
        } else {
          s.append(spaces / gap + (j < spaces % gap), ' '); // append
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
  int r=Justify_Text_Line("justify    this line", 20);
  cout << r << endl;
  Solution sln;
  vector<string> v(
      {"This", "is", "an", "example", "of", "text", "justification."});
  assert(sln.fullJustify(v, 16) ==
         vector<string>(
             {"This    is    an", "example  of text", "justification.  "}));
}
} // namespace _68
