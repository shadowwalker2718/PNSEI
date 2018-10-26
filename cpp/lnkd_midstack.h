#pragma once

#include "henry.h"

namespace _midstack {

// stack with O(1) peek and pop (not at top)
// http://stackoverflow.com/questions/10793404/behaviour-of-stdlistbegin-when-list-is-empty
struct midstack {
  list<int> stk;
  list<int>::iterator it;

  int top() { return stk.back(); }

  /* Change mid pointer in two cases
  1) Linked List is empty
  2) Number of nodes in linked list is odd */
  void push(int i) {
    stk.push_back(i);
    if (stk.size() == 1)
      it = stk.begin();
    else if (stk.size() & 1)
      it++;
  }

  void pop() {
    stk.pop_back();
    if (stk.size() && ((stk.size() & 1) == 0))
      it--;
  }

  // O(1) - empty return INT_MIN
  int peek_median() {
    if (stk.empty())
      return INT_MIN;
    return *it;
  }

  // O(1)
  void pop_median() {
    if (!stk.empty())
      stk.erase(it);
  }
};

void test() {
  midstack mt;
  assert(mt.peek_median() == INT_MIN);
  mt.push(3);
  assert(mt.peek_median() == 3);
  mt.pop_median();

  assert(mt.peek_median() == INT_MIN);
  mt.push(3);
  assert(mt.peek_median() == 3);
  mt.push(5);
  assert(mt.peek_median() == 3);
  mt.push(2);
  assert(mt.peek_median() == 5);
  mt.push(4);
  assert(mt.peek_median() == 5);

  mt.pop();
  assert(mt.peek_median() == 5);
  mt.pop();
  assert(mt.peek_median() == 3);
  mt.pop();
  assert(mt.peek_median() == 3);
  mt.pop();
  assert(mt.peek_median() == INT_MIN);
}

struct maxstack {

  void popmax() {}
};

} // namespace _midstack
