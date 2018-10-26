#pragma once

#include "henry.h"

namespace _multi_dimension_array {

struct MDA {};

#define VI vector<int>
int getval(MDA *p, VI vi) {
  for (int i = 0; i < vi.size(); ++i)
    printf("%d,", vi[i]);
  printf("\n");
  return 1;
}

void dfs(MDA *mda, int &sum, VI &p, VI &ds, int idx, int L) {
  if (p.size() == L) {
    sum += getval(mda, p);
    return;
  }
  for (int i = 0; i < ds[idx]; i++) {
    p.push_back(i);
    dfs(mda, sum, p, ds, idx + 1, L);
    p.pop_back();
  }
}

int getsum(MDA *mda, vector<int> ds) {
  int sum = 0;
  int L = ds.size(); // dimension
  vector<int> p;
  dfs(mda, sum, p, ds, 0, L);
  return sum;
}

void test() { assert(getsum(0, {2, 3, 4}) == 2 * 3 * 4); }

} // namespace _multi_dimension_array
