//
// Created by Henry Wu on 11/30/18.
//

#ifndef PNSEI_FIBONACCI_NUMBER_H
#define PNSEI_FIBONACCI_NUMBER_H

#include "pnsei.h"

namespace _fib {

VVL multiply(const VVL &l, const VVL &r) { // O(1) - 8 times
  VVL res(2, VL(2));
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      for (int k = 0; k < 2; ++k)
        res[i][k] += l[i][j] * r[j][k];
  return res;
}

VVL matrix_power(int n) { // O(LogN)
  // FIBONACCI matrix
  static const VVL fib_mat = {{1, 1}, {1, 0}};
  if (n == 1) {
    return fib_mat;
  } else if (n == 2) {
    return multiply(fib_mat, fib_mat);
  } else {
    auto res = matrix_power(n / 2);
    if (n & 1) {
      auto t = multiply(res, res);
      return multiply(t, fib_mat);
    } else
      return multiply(res, res);
  }
}

long long fib_BigOLogN(int n) {
  if (n == 0) return 0;
  if (n < 3) return 1;
  auto m = matrix_power(n - 2);
  return m[0][0] + m[0][1];
}

long long fib_BigON(int n) {
  if (n == 0) return 0;
  if (n < 3) return 1;
  long long p = 1LL, pp = 1LL, r;
  for (int i = 3; i <= n; ++i)
    r = p + pp, pp = p, p = r;
  return r;
}

void test() {
  /* When n=660000, FMatrix is faster than Sequential; For small n, Sequential is faster.
    3986953188624533888
    FMatrix : 373 us
    3986953188624533888
    Sequential : 3553 us
  */
  {
    AutoProfiler ap("FMatrix");
    assert(fib_BigOLogN(66) == 27777890035288LL);
    //cout << fib_BigOLogN(660000) << endl;
  }
  {
    AutoProfiler ap("Sequential");
    assert(fib_BigON(66) == 27777890035288LL);
    //cout << fib_BigON(660000) << endl;
  }
}

}

#endif //PNSEI_FIBONACCI_NUMBER_H
