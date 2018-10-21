#pragma once

#include "henry.h"

namespace _frequent_element {

  void frequent_element(vector<int> nums, int k) {
    map<int, int> m;
    for (int i : nums) {
      if (m.size() < k-1)
        m[i]++;
      else
        for (auto it = m.begin(); it != m.end();)
          if (--m[it->first] == 0)
            it = m.erase(it);
          else
            ++it;
    }
    if(m.size()>1)
      for (auto it = m.begin(); it != m.end();)
        if (--m[it->first] == 0)
          it = m.erase(it);
        else
          ++it;

    for (auto pr : m)
      cout << pr.first << "," << pr.second << endl;
  }

  void test() {
    //vector<int> nums = {1,2,3,4,5,6,7,8,9,1,1,1,1};
    vector<int> nums = { 1,1,1,2,2,2,3,3,3,4,4,4,4 };
    frequent_element(nums, 4);
  }

}