#ifndef PNSEI_91__DECODE_WAYS_H
#define PNSEI_91__DECODE_WAYS_H
#include "henry.h"

namespace _91{

//https://blog.csdn.net/worldwindjp/article/details/19938131
class Solution {
public:
  int numDecodings(string s) {
    int L=s.size();
    if(L==0 or s[0]=='0')
      return 0;
    vector<int> v(L+1);
    v[0]=v[1]=1;

    for(int l=2; l<=L; ++l){
      int t=stoi(s.substr(l-2,2));
      if (s[l-1] != '0'){
        v[l] = v[l-1];
      }
      if (t>=10 and t<=26){
        v[l] += v[l-2];
      }
    }
    return v[L];
  }
};
}

#endif // PNSEI_91__DECODE_WAYS_H
