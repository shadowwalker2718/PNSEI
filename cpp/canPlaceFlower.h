#pragma once

#include "henry.h"


namespace _canPlaceFlower {
  int placeflower_v1(vector<bool>& flowerbed) {
    //vector<bool> flowerbed = {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};
    int status = -1;
    int r = 0;
    int count = 0;
    for (int i : flowerbed) {
      if (i == 0) {
        count++;
      } else {
        if (-1 == status) { r += count / 2; status = 0, count=0; }
        else { r += (count - 1) / 2; count = 0; }
      }
    }
    if (count > 0) r += count / 2;
    return r;
  }

  bool placeflower(forward_list<int>& flowerbed, int t) {
    auto i = flowerbed.begin();
    int count = 0;
    int pp = -1, p=-1;
    while (i != flowerbed.end()) {
      if (*i == 0) {
        if (0 == p && (-1 == pp || 0 == pp)) {
          count++;
          if (count == t)
            return true;
          pp = 1;
        }else { pp = p; }
      } else { pp = p; }
      p = *i;
      ++i;
    }
    if (0 == p && 0 == pp) count++;
    return count==t;
  }

  void test() {
    forward_list<int> flowerbed = { 0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 };
    assert(placeflower(flowerbed, 4));
    assert(placeflower(flowerbed, 7));
    assert(!placeflower(flowerbed, 8));
  }
}


