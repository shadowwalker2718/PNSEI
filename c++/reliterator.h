#pragma once

#include "henry.h"

namespace _RLEIterator {
  //http://sde.quant365.com/bloomberg-2016.html#histogram-iterator

  //{1 1 2 2 3 3 3 5 5}
  //{1 2 2 2 3 3 5 2}
  struct myiterator {
    const vector<int>& v;
    int i; // idx of counter
    int j; // val of counter
    myiterator(const vector<int>& vi) :v(vi), i(1), j(v[i]) {}
    int next() {
      if (j>0) {
        --j;
      } else {
        ++++i;
        if (i >= v.size()) { throw "stop"; }
        j = v[i] - 1;
      }
      return v[i - 1];
    }
    bool hasNext() {
      return i<v.size() - 1 || ((i == v.size() - 1) && j>0);
    }
  };
  int test() {
    vector<int> vi = { 1, 2, 2, 2, 3, 3, 5, 2 , 9, 0};
    myiterator it(vi);
    vector<int> r;
    while (it.hasNext())
      r.push_back(it.next());
    assert(r == vector<int>({1,1,2,2,3,3,3,5,5}));
    return 0;
  }

}

