#ifndef PNSEI_PERMUTATION_H
#define PNSEI_PERMUTATION_H

#include "henry.h"

namespace nb{

void dfs(vector<string>& vs, string& p, const string& s, vector<bool>& visited){
  if (p.size()==s.size()){
    vs.push_back(p);
    return;
  }
  for(int i=0;i<s.size();i++){
    if (!visited[i]){
      p += s[i];
      visited[i]=true;
      dfs(vs,p,s,visited);
      visited[i]= false;
      p.pop_back();
    }
  }
}

vector<string> perm(const string& s){
  vector<string> r;
  string p;
  vector<bool> vb(s.size());
  dfs(r, p, s, vb);
  return r;
}

}

#endif // PNSEI_PERMUTATION_H
