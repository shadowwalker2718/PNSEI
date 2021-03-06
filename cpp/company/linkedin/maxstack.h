#pragma once

#include "pnsei.h"

namespace _minmaxstack {

class minstack {
  priority_queue<int, vector<int>, greater<int>> Q;
  list<int> l;

public:
  minstack() {}

  void push(int i) {
    l.push_back(i);
    Q.push(i);
  }
};

// http://sde.quant365.com/linkedin-2016-11.html#medianmaxmin-stack
struct MaxStack {
  list<int> stk;
  list<list<int>::iterator> max_itr;
  unordered_map<int, list<list<int>::iterator>::iterator> val2itr;

  void push(int i) { // O(N) average
    stk.push_back(i);
    // https://stackoverflow.com/questions/2678175/iterator-to-last-element-in-stdlist
    auto back_iter = prev(stk.end());
    for (auto it = max_itr.begin(); it != max_itr.end(); ++it) {
      if (**it < i) {
        auto nit = max_itr.insert(it, back_iter);
        val2itr[i] = nit;
        return;
      }
    }
    max_itr.push_back(back_iter);
    val2itr[i] = max_itr.end();
    --val2itr[i];
  }

  int pop() { // O(1) average
    if (stk.empty())
      return INT_MIN;
    int val = stk.back();
    max_itr.erase(val2itr[val]); // cannot use remove
    val2itr.erase(val);
    stk.pop_back();
    return val;
  }

  int pop_max() { // O(1) average
    if (stk.empty())
      return INT_MIN;
    list<int>::iterator m = max_itr.front();
    int r = *m;
    val2itr.erase(r);
    stk.erase(m);
    max_itr.pop_front();
    return r;
  }
};

void test() {
  MaxStack mstk;
  mstk.push(3);
  mstk.push(1);
  mstk.push(2);
  mstk.push(4);
  mstk.push(6);
  mstk.push(5);
  mstk.push(0);

  assert(mstk.pop_max() == 6);
  assert(mstk.pop_max() == 5);
  assert(mstk.pop() == 0);
  assert(mstk.pop_max() == 4);
  assert(mstk.pop_max() == 3);
  assert(mstk.pop_max() == 2);
  assert(mstk.pop_max() == 1);
  assert(mstk.pop_max() == INT_MIN);
}

} // namespace _minmaxstack
