#pragma once

#ifndef PNSEI_PROBABILITY_H
#define PNSEI_PROBABILITY_H

#include "henry.h"

namespace _probability {

// return 0 with probability p and return 1 with probability q
int get_01_pq() { return rand() % 2; }

//////////////////////////////////////////////////////////////////
/*
1. coding: 给定一个函数getbiasrandom(), 以p概率返回1，
（p-1）概率返回0。实现一个getrandom()函数，以相同概率返回0-6中的一个数
        我懵了，特别懵，，提示下只实现了以相同概率返回0/1，没做过的题脑子不转了，当场觉得挂了。
*/
int get_01_uniform() {
  int prev = get_01_pq(), cur = get_01_pq();
  while (true) {
    if (prev == 1 && cur == 0)
      return 1;
    if (prev == 0 && cur == 1)
      return 0;
    prev = cur, cur = get_01_pq();
  }
}

int get_01_uniform2() {
  while (true) {
    int prev = get_01_pq(), cur = get_01_pq();
    if (prev == 1 && cur == 0)
      return 1;
    if (prev == 0 && cur == 1)
      return 0;
  }
}

int get_0_to_N_uniform(int n = 6) {
  if (n < 0)
    return -1;
  int num_bit = 0, N = n;
  while (n) {
    n >>= 1, num_bit++;
  }
  // to call get_01_uniform() num_bit times to construct a number
  int r = 0, k = num_bit;
  while (num_bit--) {
    r = (r << 1) | get_01_uniform();
    if (r > N) { // 0b111
      num_bit = k, r = 0;
    }
  }
  return r;
}

int get_A_to_B_uniform(int a, int b) { return a + get_0_to_N_uniform(b - a); }


// r()函数等概率随机产生1到5,如何等概率随机产生1-7?
int get_1toM_uniform(int a = 1, int M = 5) { return get_A_to_B_uniform(a, M); }
// N > M
// Sum of two uniform random var is not uniform, to get a uniform distribution, we need to use 插孔法.
int get_1toN_uniform_by_1toM(int M = 5, int N = 7) {
  int t = (get_1toM_uniform(1, M) - 1) * M; // 0,5,10,15,20
  t += get_1toM_uniform(1, M) - 1;          // t ~ [0,24], t must be uniform in [0 ~ M*M-1]
  if (t >= (M * M / N * N)) //Potential BUG
    return get_1toN_uniform_by_1toM(M, N);
  return t % N + 1;
}

void test() {
  std::string s = std::bitset<64>(12345).to_string();
  srand(time(NULL));

  AutoProfiler ap(__FUNCTION__);
  static const int LEN = 102400*5;
  bitset<LEN> bs;
  REP(i, 0, LEN) {
    if (get_01_uniform())
      bs.set(i);
  }
  int t = bs.count();
  assert(abs(0.5 - double(t) / LEN) < 0.01);

  {
    map<int, int> counter;
    int N = 6;
    REP(i, 0, LEN) { counter[get_0_to_N_uniform(N)]++; }
    for (auto pr : counter) {
      assert(abs(double(pr.second) / LEN - double(1) / (N + 1)) < 0.005);
    }
  }

  {
    map<int, int> counter;
    REP(i, 0, LEN) { counter[get_1toN_uniform_by_1toM(5,7)]++; }
    for (auto pr : counter) {
      assert(abs(double(pr.second) / LEN - double(1) / 7) < 0.005);
    }
  }

  {// if N is greater than M*M, try M^2 * M^2
    map<int, int> counter;
    REP(i, 0, LEN) { counter[get_1toN_uniform_by_1toM(6, 8)]++; }
    for (auto pr : counter) {
      cout << (abs(double(pr.second) / LEN - double(1) / 7)) << endl;
    }
  }
}

} // namespace _probability
#endif
