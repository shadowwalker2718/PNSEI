//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_480_SLIDING_WINDOW_MEDIAN_H
#define PNSEI_480_SLIDING_WINDOW_MEDIAN_H

#include "henry.h"

namespace _480_medianSlidingWindow{

// https://leetcode.com/problems/sliding-window-median/

struct Solution {

  // http://www.cplusplus.com/reference/set/multiset/insert/ check C++98 and C++11's difference
  // multiset insert only when and after C++11:
  // The relative ordering of equivalent elements is preserved, and newly inserted elements follow their equivalents
  // already in the container.

  //  upper_median is our friend in this case!!!
  VI medianSlidingWindow(vector<int>& nums, int K) { // O((N-K)LogK)
    if(K<=0) return {};
    multiset<int> BoundedBST(nums.begin(), nums.begin() + K); // O(KLogK)
    //https://en.cppreference.com/w/cpp/iterator/next
    //Return the nth successor of iterator it.
    // rename it to umedian coz it could be upper_median or unique_median
    multiset<int>::iterator umedian = next(BoundedBST.begin(), K / 2);
    VI medians;
    for (int i=K; ; i++) { // N-K
      if (K&1)
        medians.push_back(*umedian);
      else
        medians.push_back((*umedian + *prev(umedian)) / 2);
      if (i == nums.size())
        return medians;
      int go = nums[i-K], come=nums[i];
      // insert come
      BoundedBST.insert(come);

      if (come < *umedian) // incoming
        umedian--; // pre - O(LogK) - umedian becomes unique_median or lower_median(1,(3),4 => 1,(2),3,4)
      if (go <= *umedian) // outgoing  //  this will make umedian becomes unique_median or upper_median again!!!
        umedian++; // suc O(LogK)

      // erase go
      BoundedBST.erase(BoundedBST.lower_bound(go)); // how to erase element from multiset BST
    }
    return medians;
  }
};

// Can we use lower median, why not?



class SolutionX {
public:
  vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    vector<double> res;
    multiset<int> small, large;
    for (int i = 0; i < nums.size(); ++i) {
      if (i >= k) {
        if (small.count(nums[i - k])) small.erase(small.find(nums[i - k]));
        else if (large.count(nums[i - k])) large.erase(large.find(nums[i - k]));
      }
      if (small.size() <= large.size()) {
        if (large.empty() || nums[i] <= *large.begin()) small.insert(nums[i]);
        else {
          small.insert(*large.begin());
          large.erase(large.begin());
          large.insert(nums[i]);
        }
      } else {
        if (nums[i] >= *small.rbegin()) large.insert(nums[i]);
        else {
          large.insert(*small.rbegin());
          small.erase(--small.end());
          small.insert(nums[i]);
        }
      }
      if (i >= (k - 1)) {
        if (k % 2) res.push_back(*small.rbegin());
        else res.push_back(((double)*small.rbegin() + *large.begin()) / 2);
      }
    }
    return res;
  }
};
struct xxx{
  int v, e;
  xxx(int a, int b):v(a),e(b){}
};
struct comp{
  bool operator()(const xxx& a, const xxx& b){
    return a.v < b.v;
  }
};


void test(){
  VI vi;
  SolutionX x;
  vi={6,5,9,5,4,9,1,7,5,5};
  auto rx=x.medianSlidingWindow(vi,4);
  // the behavior of multiset with dup numbers
  // If the container has elements with equivalent key, inserts at the upper bound of that range.
  // But erase will erase all with the same key!!!!!
  multiset<xxx,comp> mp;
  mp.emplace(1,1),mp.emplace(1,0),mp.emplace(1,-1),mp.emplace(1,-100);
  for(auto pr: mp){
    cout << pr.v << "," << pr.e << endl;
  }
  // The above proves in STL BBST(multiset), equal nodes goes to the right.

  Solution sln;
  vi = {1,3,-1,-3,5,3,6,7};
  //auto r=sln.medianSlidingWindow2(vi, 3);
  //assert(r == VI({1,-1,-1,3,5,6}));
  //auto r2=sln.medianSlidingWindow3(vi, 3);
  //assert(r == r2);
  vi = {1,3,-1,-3,5,3,6,7};
  //assert(sln.medianSlidingWindow2(vi, 4) == VI({0,1,1,2,5}));
  //assert(sln.medianSlidingWindow2(vi, 4) == sln.medianSlidingWindow3(vi, 4));
}

}

#endif //PNSEI_480_SLIDING_WINDOW_MEDIAN_H
