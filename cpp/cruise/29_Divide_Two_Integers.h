//
// Created by Henry Wu on 12/9/18.
//

#ifndef PNSEI_29_DIVIDE_TWO_INTEGERS_H
#define PNSEI_29_DIVIDE_TWO_INTEGERS_H

#include "henry.h"

namespace _29 {

// without using multiplication, division and mod operator

class Solution {
public:
  int divide(int x/*dividend*/, int y/*divisor*/) { // 15 = 3 * 5 (=0b1001)
    if (x == 0) return 0;
    if (y == 0) return INT_MIN;
    if (x == INT_MIN and y == -1) return INT_MAX;
    int sign = ((x ^ y) < 0) ? -1 : 1;
    x = abs(x), y = abs(y);
    int r = 0, t = 1;
#ifdef NAIVE
    while(t<x){
      t+=y, r++;
    }
#else
    vector<int> vi;
    int p = y;
    while (x >= p) {
      t += t;
      p += p;
    }
    t /= 2, p /= 2;
    int sum = 0;
    while (t) {
      if (sum + p <= x) {
        sum += p;
        r += t;
      }
      t /= 2, p /= 2;
    }

#endif
    return r * sign;
  }
};

void test() {
  int r = Solution().divide(15, 3);
  assert(r == 5);
}

}

#endif //PNSEI_29_DIVIDE_TWO_INTEGERS_H
