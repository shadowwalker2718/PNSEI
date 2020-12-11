//
// Created by Henry Wu on 12/2/18.
//

#ifndef PNSEI_668_KTH_SMALLEST_NUMBER_IN_MULTIPLICATION_TABLE_H
#define PNSEI_668_KTH_SMALLEST_NUMBER_IN_MULTIPLICATION_TABLE_H

#include "pnsei.h"

namespace _668 {

// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/

struct Solution {
  int findKthNumber(int m, int n, int k) {
    int l = 1, r = m * n;
    while (l <= r) {
      int md = l + (r - l) / 2, c = 0;
      for (int i = 1; i <= m; ++i) {
        int t = md / i;
        c += t <= n ? t : n;
      }
      if (c < k)
        l = md + 1;
      else
        r = md - 1;
    }
    return l;
  }
};

void test() {
  Solution sln;
  int r = sln.findKthNumber(3, 3, 5);
  assert(r == 3);
}

}

#endif //PNSEI_668_KTH_SMALLEST_NUMBER_IN_MULTIPLICATION_TABLE_H
