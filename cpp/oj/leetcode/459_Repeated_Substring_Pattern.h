//
// Created by henry on 1/7/19.
//

#ifndef PNSEI_459_REPEATED_SUBSTRING_PATTERN_H
#define PNSEI_459_REPEATED_SUBSTRING_PATTERN_H

#include "pnsei.h"

namespace _459{

struct Solution {
  vector<int> LPPP(const string& s){//Longest Proper Prefix Postfix array
    vector<int> r(s.size());
    for (int i=1, j=0; i<s.size();)// i for s, j for pattern, last LPPP value
      if(s[i]==s[j]) r[i++]=++j; else if(j) j=r[j-1]; else r[i++]=0;
    return r;
  }
  bool repeatedSubstringPattern(string str) {
    auto lppp = LPPP(str);
    return !lppp.empty() && lppp.back()>0 && (str.size()%(str.size()-lppp.back())==0);
  }

  string repeatedSubstringPattern2(string str) {
    auto lppp = LPPP(str);
    if (!lppp.empty() && lppp.back()>0 && (str.size()%(str.size()-lppp.back())==0)){
      return str.substr(0,str.size()-lppp.back());
    }
    return "";
  }

  string contiguous_repeated_string(string A){
    string r(1,A[0]);
    for(int i=0;i<A.size();i++){
      for(int l=2;l<=A.size();l++){
        string s=A.substr(i,l);
        if ((s+s).substr(1,2*s.size()-1).find(s)!=s.size()-1 and s.size()>r.size()){
          r=s;
        }
      }
    }
    return r;
  }
};


void test(){
  Solution sln;
  cout << sln.contiguous_repeated_string("ATCGATCGA") << endl;
}

}


#endif //PNSEI_459_REPEATED_SUBSTRING_PATTERN_H
