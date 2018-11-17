//
// Created by root on 11/11/18.
//

#ifndef PNSEI_816_AMBIGUOUS_COORDINATES_H
#define PNSEI_816_AMBIGUOUS_COORDINATES_H

#include "henry.h"

// https://leetcode.com/problems/ambiguous-coordinates/description/

namespace _816{

class Solution {
public:
  vector<string> ambiguousCoordinates(string S) {
    vector<string> res;
    S=S.substr(1,S.length()-2);
    auto insert_dot=[](string x){
      vector<string> vs;
      // add dot
      for(int i=1;i<x.size();i++){
        auto l=x.substr(0,i);
        auto r=x.substr(i);
        if(l[0]=='0' && l.size()>1) continue;
        if(r.back()=='0') continue;
        vs.push_back(l+"."+r);
      }
      // no dot to add
      if(x[0]!='0' || x=="0")
        vs.push_back(x);
      return vs;
    };
    for(int i=1;i<S.size();i++){
      string l=S.substr(0,i);
      string r=S.substr(i);
      auto x=insert_dot(l);
      auto y=insert_dot(r);
      for(auto m: x){
        for(auto n: y){
          res.push_back("(" + m + ", " + n +")");
        }
      }
    }
    return res;
  }
};

void test(){
  vector<string> r={"(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12, 3)"};
  Solution sln;
  assert(sln.ambiguousCoordinates("(0123)") == r);
}

}


#endif //PNSEI_816_AMBIGUOUS_COORDINATES_H
