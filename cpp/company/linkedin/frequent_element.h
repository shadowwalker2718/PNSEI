#pragma once

#include "henry.h"

// https://leetcode.com/problems/majority-element/
namespace _frequent_element {
// TODO this algo is incorrect!!!
vector<int> frequent_element_greater_than_one_kth(vector<int> nums, int k) {
  map<int, int> m;
  for (int i : nums) {
    if (m.size() < k - 1)
      m[i]++;
    else {
      for (auto it = m.begin(); it != m.end();)
        if (--m[it->first] == 0)
          it = m.erase(it);
        else
          ++it;
    }
  }
  if (m.size() > 1) {
    for (auto it = m.begin(); it != m.end();)
      if (--m[it->first] == 0)
        it = m.erase(it);
      else
        ++it;
  }
  vector<int> r;
  for (auto pr : m) {
    cout << pr.first << "," << pr.second << endl;
    r.push_back(pr.first);
  }
  return r;
}

void test() {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 1, 1};
  assert(frequent_element_greater_than_one_kth(nums, 4) == vector<int>{1});

  // 4 is more than one fourth of the numbers in vector nums
  nums = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  assert(frequent_element_greater_than_one_kth(nums, 4) == vector<int>{4});

  nums = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
  assert(frequent_element_greater_than_one_kth(nums, 4) == vector<int>{});

  //nums = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
  //assert(frequent_element_greater_than_one_kth(nums, 4 + 1) == vector<int>({1, 2, 3, 4}));
}

} // namespace _frequent_element