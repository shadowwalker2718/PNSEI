#ifndef PNSEI_53_MAXIMUM_SUBARRAY_H
#define PNSEI_53_MAXIMUM_SUBARRAY_H

#include "henry.h"

namespace _53{

class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int mx = *max_element(nums.begin(), nums.end());// all negative
    partial_sum(nums.begin(), nums.end(), nums.begin()); // cum sum
    int mi=nums[0], r=mi;
    for(int i=1; i<nums.size(); ++i)
      r=max(r, nums[i]-mi), mi=min(mi, nums[i]); // best time to buy-sell stock
    // max subarray sum by cum sum array
    return max(max(mx,r),*max_element(nums.begin(), nums.end()));
  }

  int maxSubArray2(vector<int>& nums) {
    int global_sum=INT_MIN, tmp_sum =0;
    for(auto i: nums){
      tmp_sum +=i;
      global_sum=max(global_sum, tmp_sum);
      if (tmp_sum <0)
        tmp_sum =0;
    }
    return global_sum;
  }

  tuple<int,int,int> maxSubArray_followup(vector<int> nums) {
    auto mx = max_element(nums.begin(), nums.end());// all negative
    int tmp_mx = *mx, tmp_idx = mx-nums.begin();
    pair<int,int> res = {0, 0};
    partial_sum(nums.begin(), nums.end(), nums.begin()); // cum sum
    int mi=nums[0], r=mi;
    if (r < tmp_mx){
      r = tmp_mx, res = {tmp_idx, tmp_idx};
    }
    int mi_idx = 0;
    for(int i=1; i<nums.size(); ++i){
      if (r < nums[i]-mi) {
        r = nums[i]-mi, res = {mi_idx+1, i};
      }
      if (mi > nums[i]) {
        mi = nums[i], mi_idx = i;
      }
    }
    for(int i=0;i<nums.size();i++){
      if (r<nums[i]){
        r = nums[i];
        res = {0, i};
      }
    }
    // max subarray sum by cum sum array
    return {res.first, res.second, r};
  }

  tuple<int,int,int> maxSubArray_followup2(vector<int> nums) {
    int mx=INT_MIN, j;
    for(int i=0;i<nums.size();++i)
      if(mx<nums[i])
        mx=nums[i], j=i;
    if(mx<=0){
      return {j,j,mx};
    }
    int g=INT_MIN, l=0, p=-1;
    int ps=0/*previous start*/, s=0/*newest start*/, e=0/*end*/;
    for(int i=0; i<nums.size(); ++i){
      l += nums[i];
      g = max(g,l);
      if(g==l) e=i; ///
      if(l<0) l=0, ps=s, s=i+1;
    }
    return {(s>e?ps:s), e, g};
  }
};

}

#endif // PNSEI_53_MAXIMUM_SUBARRAY_H
