#pragma once

#include "pnsei.h"

namespace bbg_encode_list_with_dups {

// http://www.1point3acres.com/bbs/thread-247535-1-1.html
/*
 * 2017(1-3月) 码农类General 硕士 全职@Bloomberg - 网上海投 - 技术电面  | Other | fresh grad应届毕业生
电面:
简历扯了25分钟,结果后来时间不够
一道链表题:
输入a->b->b->b->c;
输出a->3->b->c;

还问了两个char连续的情况怎么输出,最后怎么测试你的代码...
 * */

string encode_list_with_dups(const string &s) {
  string r;
  char last = 0;
  int count = 0;
  for (char c : s) {
    if (c == last) {
      count++;
    } else if (count > 0) {
      r += (count > 1 ? to_string(count) : string("")) + last;
      last = c, count = 1;
    } else {
      last = c, count++;
    }
  }
  if (count > 0)
    r += (count > 1 ? to_string(count) : string("")) + last;
  return r;
}

void test() {
  string s = "abbbc";
  assert(encode_list_with_dups(s) == "a3bc");
}

} // namespace bbg_encode_list_with_dups