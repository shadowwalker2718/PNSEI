//
// Created by Henry Wu on 12/4/18.
//

#ifndef PNSEI_BINARY_SEARCH_H
#define PNSEI_BINARY_SEARCH_H

#include "henry.h"

namespace _binary_search {

// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=461616

/*
2. binary search 的应用， 找到比自己大一号的字母
arr = [a,b,d,f,v,z], key = z, ret= a
arr = [a,b,d,f,v,z], key = b, ret= d
*/

char find_greater_char(string s, char b) {
  if (s.empty()) return 0;
  int h = 0, L = s.size(), t = L - 1;
  while (h <= t) {
    int m = h + (t - h) / 2;
    if (s[m] <= b) {
      h = m + 1;
    } else {
      t = m - 1;
    }
  }
  if (h == L) return s[0] == b ? 0 : s[0];
  return s[h];
}

char find_greater_char_v2(string s, char b) {
  if (s.empty()) return 0;
  int h = 0, L = s.size(), t = L - 1;
  while (h < t) {
    int m = h + (t - h) / 2;
    if (s[m] <= b) {
      h = m + 1;
    } else {
      t = m;
    }
  }
  if (s[h]>b) return s[h];
  //if(s[h]==b && s[(h+1)%L]!=b) return s[(h+1)%L];
  if(s[h]==b && s[0]!=b) return s[0];
  return 0;
}

void test() {
  assert(find_greater_char("", 'z') == 0);
  assert(find_greater_char("z", 'z') == 0);
  assert(find_greater_char("abdfvz", 'z') == 'a');
  assert(find_greater_char("abdfvz", 'b') == 'd');

  assert(find_greater_char_v2("", 'z') == 0);
  assert(find_greater_char_v2("z", 'z') == 0);
  assert(find_greater_char_v2("zzzzzzzzzz", 'z') == 0);
  assert(find_greater_char_v2("abdfvz", 'z') == 'a');
  assert(find_greater_char_v2("abdfvz", 'b') == 'd');
  assert(find_greater_char_v2("abbbbbddddfvz", 'b') == 'd');
}

}

#endif //PNSEI_BINARY_SEARCH_H
