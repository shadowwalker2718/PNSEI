//
// Created by Henry Wu on 11/4/18.
//

#ifndef PNSEI_43_MULTIPLY_STRINGS_H
#define PNSEI_43_MULTIPLY_STRINGS_H

#include "henry.h"

namespace _43{

// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=230745&highlight=addepar

//题目虽然不难.要完全写对也不容易.
//1. 首先要注意num1[i] * num2[j]的结果应该加到ret[i+j]的位置上.
//2. 其次要注意ln 16不能遗漏最高位的进位,由于此时ret中该位为0,所以只需要将carry转为字符即可.
//3. 最容易遗漏的corner case是ln 18.如999*0 = 0000,此时需要去掉开始的0,但又需要保留最后一个0.

class Solution {
public:
  string multiply(string x, string y) {
    if(x.empty() || y.empty())
      return "";
    reverse(x.begin(),x.end()), reverse(y.begin(),y.end());

    int M=x.size(), N=y.size();

    string r(M+N,'0'); //
    for(int j=0; j<N; j++) { //???
      int carry = 0;
      int val = y[j] - '0';
      for(int i=0; i<M; i++) {
        carry += ((x[i]-'0')*val + (r[i+j]-'0'));
        r[i+j] = carry%10 + '0';
        carry /= 10;
      }
      //if(carry==1) //
      r[M+j] = '0'+carry;
    }

    while(r.size()!=1 && r.back()=='0') // xxxxxxx00000
      r.pop_back(); // 0*999
    reverse(r.begin(),r.end());
    return r;
  }
};

void test(){
  Solution sln;
  assert(sln.multiply("123", "456") == "56088");
}



}

#endif //PNSEI_43_MULTIPLY_STRINGS_H
