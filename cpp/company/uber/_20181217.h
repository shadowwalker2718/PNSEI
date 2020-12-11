//
// Created by henry on 12/17/18.
//

#ifndef PNSEI_UBER_ONSITE_H
#define PNSEI_UBER_ONSITE_H

#include "pnsei.h"

namespace _20181227{

string process(string s){
  bool ws= false;
  string r;
  REP(i,0,s.size()){
    if(s[i]==' '){
      ws=true;
    }else{
      if(ws) r+=' ',ws=false;
      r+=s[i];
    }
  }
  if(ws) r+=' ';
  return r;
}

void test(){
  assert(process("")=="");
  assert(process("a  ")=="a ");
  assert(process("   ")==" ");
  assert(process("   a")==" a");
  assert(process("ab  c d  ")=="ab c d ");
}

void dfs(VVI &r, VI p, VI& v, int h){
  r.push_back(p);
  REP(i,h,v.size()){
    auto t=p;
    t.push_back(v[i]);
    dfs(r,t,v,i+1);
  }
}
VI get(VI v, int T){
  VVI r;
  VI p;
  dfs(r,p,v,0);
  for(auto e: r){
    if (accumulate(e.begin(),e.end(), 0) == T){
      return e;
    }
  }
  return {};
}

void test2(){
  VI v={2,5,14,3};
  VI r=get(v, 8);
  for(int i: r) {
    cout << i << endl;
  }
};

int longest_subseq(string a, string b){
  int M=a.size(), N=b.size();
  if(M==0 or N==0) return 0;
  VVI dp=VVI(M+1,VI(N+1));
  REP(i,1,M+1){
    REP(j,1,N+1){
      if(a[i-1]==b[j-1]){dp[i][j]=1+dp[i-1][j-1];}
      else{
        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  return dp[M][N];
}

void test3(){
  int r=longest_subseq("abbcda","bdcgda");
  assert(r == 4);
}

}

#endif //PNSEI_UBER_ONSITE_H
