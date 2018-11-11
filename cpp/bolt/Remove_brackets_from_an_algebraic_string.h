//
// Created by root on 11/2/18.
//

#ifndef PNSEI_REMOVE_BRACKETS_FROM_AN_ALGEBRAIC_STRING_H
#define PNSEI_REMOVE_BRACKETS_FROM_AN_ALGEBRAIC_STRING_H

// https://www.geeksforgeeks.org/remove-brackets-algebraic-string-containing-operators/

#include "henry.h"

namespace bolt {

// DFS ===>> stack
string simplify_algebraic_string(const string &s) {
  string r;
  int d = 0;
  stack<bool> stk;
  stk.push(true);
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c == '(') {
      bool b = stk.top();
      stk.push(s[i - 1] == '-' ? (!b) : b);
    } else if (c == ')') {
      stk.pop();
    } else if (c == '+' or c == '-') {
      r += stk.top() ? c : (c == '+' ? '-' : '+');
    } else {
      r += c;
    }

  }
  return r;
}

void test() {
  assert(simplify_algebraic_string("a-(b+c)") == "a-b-c");
  assert(simplify_algebraic_string("a-(b-c-(d+e))-f") == "a-b+c+d+e-f");
  assert(simplify_algebraic_string("-(a+b)") == "-a-b");
  assert(simplify_algebraic_string("a-(b-(c-d))") == "a-b+c-d");
  assert(simplify_algebraic_string("a-(b-(c-d)-e+(f+g))") == "a-b+c-d+e-f-g");
}

};

#endif //PNSEI_REMOVE_BRACKETS_FROM_AN_ALGEBRAIC_STRING_H
