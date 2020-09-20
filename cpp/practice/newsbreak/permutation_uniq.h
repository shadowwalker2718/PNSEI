#ifndef PNSEI_PERMUTATION_UNIQ_H
#define PNSEI_PERMUTATION_UNIQ_H

#include "henry.h"

namespace nb2{

void dfs(vector<string>& vs, string& p, const string& s, vector<bool>& visited){
  if (p.size()==s.size()){
    vs.push_back(p);
    return;
  }
  for(int i=0;i<s.size();i++){
    if (visited[i] or (i>=1 and !visited[i-1] and s[i]==s[i-1])){
      continue;
    }
    p += s[i];
    visited[i]=true;
    dfs(vs,p,s,visited);
    visited[i]= false;
    p.pop_back();
  }
}

vector<string> perm(const string& s){
  vector<string> r;
  string p;
  string tmp(s);
  sort(tmp.begin(),tmp.end());
  vector<bool> vb(tmp.size());
  dfs(r, p, tmp, vb);
  return r;
}

}

#endif // PNSEI_PERMUTATION_UNIQ_H
