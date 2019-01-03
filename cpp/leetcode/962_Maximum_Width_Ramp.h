//
// Created by henry on 12/29/18.
//

#ifndef PNSEI_962_MAXIMUM_WIDTH_RAMP_H
#define PNSEI_962_MAXIMUM_WIDTH_RAMP_H

#include "henry.h"

namespace _962{

class Solution {
public:
  int maxWidthRamp(vector<int>& A) {
    vector<pair<int,int>> vp;
    for(int i=0;i<A.size();i++)
      vp.emplace_back(A[i],i);
    sort(vp.begin(), vp.end());
    int mi=INT_MAX, r=0;
    for(auto pr: vp){
      if (pr.second<mi)
        mi=pr.second;
      r=max(r,pr.second-mi);
    }
    return r;
  }
};

}

#endif //PNSEI_962_MAXIMUM_WIDTH_RAMP_H
