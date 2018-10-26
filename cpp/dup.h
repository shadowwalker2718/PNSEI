#pragma once

#include "henry.h"

namespace _find_dup {

int find_dup(vector<int> v) {
  for (int i = 0; i < v.size(); ++i) {
    while (i != v[i]) {
      if (v[i] == v[v[i]])
        return v[i];
      swap(v[i], v[v[i]]); // put v[v[i]] to correct place
    }
  }
  return INT_MAX;
}

void test() { assert(find_dup({6, 0, 4, 5, 2, 7, 9, 7, 8, 1}) == 7); }

} // namespace _find_dup
