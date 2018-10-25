#pragma once

#include "henry.h"

namespace K_th_Smallest_in_Lexicographical_Order{

  struct Solution {
    int findKthNumber(int n, int k) {
      int cur = 1;
      --k;
      while (k) {
        int steps = calsteps(n, cur);
        if (steps <= k)
          ++cur, k -= steps;
        else
          cur *= 10, --k;
      }
      return cur;
    }
    // 在boundary condition n的情况下,找head到head+1之间的距离
    int calsteps(long n, long head) {////
      int steps = 0;
      long tail = head + 1;
      while (head <= n) {
        if (tail <= n)
          steps += tail - head;
        else
          steps += n - head + 1;
        head *= 10, tail *= 10;
      }
      return steps;
    }
  };


  void test() {
    Solution s;
    assert(s.findKthNumber(13, 8) == 4);
    assert(s.findKthNumber(13, 2) == 10);
  }

}




