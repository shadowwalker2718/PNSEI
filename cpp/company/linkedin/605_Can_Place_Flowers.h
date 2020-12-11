#pragma once

#include "pnsei.h"

/*
  Suppose you have a long flowerbed in which some of the plots are planted and some are not. However, flowers cannot be
  planted in adjacent plots - they would compete for water and both would die.
  Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), and a number
  n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

  Example 1:
  Input: flowerbed = [1,0,0,0,1], n = 1
  Output: True

  Example 2:
  Input: flowerbed = [1,0,0,0,1], n = 2
  Output: False

  Note:
      The input array won't violate no-adjacent-flowers rule.
      The input array size is in the range of [1, 20000].
      n is a non-negative integer which won't exceed the input array size.

https://leetcode.com/problems/can-place-flowers/
*/

namespace _canPlaceFlower {

class Solution {
public:
  bool canPlaceFlowers(vector<int> &bed, int n) {
    int L = bed.size();
    for (int i = 0, k = 0; i < L; i++) {
      if (!bed[i] && (i == 0 || !bed[i - 1]) && (i == L - 1 || !bed[i + 1])) {
        bed[i] = true;
        if (++k >= n) return true;
      }
    }
    return n == 0;
  }
};


bool placeflower(forward_list<int> flowerbed, int t) {
  auto i = flowerbed.begin();
  int count = 0, pp = -1, p = -1;
  while (i != flowerbed.end()) {
    if (1 != pp && 0 == p && *i == 0) {
      p = 1, count++; // when pp!=1 and p==0 and current==0, mark p as 1
      if (count == t)
        return true;
    }
    pp = p, p = *i, ++i;
  }
  if (0 == p && 1 != pp)
    count++;
  return count >= t;
}

// http://sde.quant365.com/linkedin-before-2015.html#place-flowers
int placeflower_v1(vector<bool> &flowerbed) { // by observation, but not efficient
  if (find(flowerbed.begin(), flowerbed.end(), 1) == flowerbed.end()) {
    return (flowerbed.size() + 1) / 2;
  }
  int status = -1;
  int r = 0;
  int count_bed = 0;
  for (bool i : flowerbed) {
    if (i == 0) {
      count_bed++;
    } else {
      if (-1 == status) {
        r += count_bed / 2;
        status = 0, count_bed = 0;
      } else {
        r += (count_bed - 1) / 2;
        count_bed = 0;
      }
    }
  }
  if (count_bed > 0)
    r += count_bed / 2;
  return r;
}


void test() {
  assert(placeflower({0}, 1));
  forward_list<int> flowerbed = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                 0, 0, 1, 0, 0, 0, 0, 0, 0};

  assert(placeflower(flowerbed, 4));
  assert(placeflower(flowerbed, 7));
  assert(!placeflower(flowerbed, 8));
}
} // namespace _canPlaceFlower
