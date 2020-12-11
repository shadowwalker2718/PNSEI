//
// Created by root on 1/18/19.
//

#ifndef PNSEI_SNAPCHAT_H
#define PNSEI_SNAPCHAT_H

#include "pnsei.h"

namespace sc{


vector<pair<int,int>> dirs={{0,1},{0,-1},{1,0},{-1,0}};
int R,C;
#define check_validity(i,j) (0<=i and i<R and j>=0 and j<C and !bm[i][j])

bool dfs(const vector<string> &m, const string& w, int start, int i, int j, vector<vector<bool>> &bm){
  if(start==w.size())
    return true;
  if(w[start]!=m[i][j])
    return false;
  bm[i][j]=true; //
  for(auto d: dirs){
    int ni=i+d.first, nj=j+d.second;
    if(check_validity(ni,nj)){
      if(dfs(m,w,start+1,ni,nj,bm))
        return true;
    }
  }
  bm[i][j]=false; //unwind
  return false;
}
bool wordExists(vector<string> & m, string w){
  if(w.empty())
    return true;
  if (m.empty() or m[0].empty())
    return false;

  R=m.size(), C=m[0].size();
  for(int i=0;i<R;i++){
    for(int j=0;j<C;j++){
      vector<vector<bool>> bm(R,vector<bool>(C));
      if (dfs(m, w, 0, i, j, bm)){
        return true;
      }
    }
  }
  return false;
}
void test(){
  vector<string>  m={"ATGH",
                     "LGQM",
                     "NATT"};
  assert(wordExists(m,"TGQGH"));
  assert(!wordExists(m,"TGQGT"));
  assert(!wordExists(m,"TAAB"));
}


struct mynode{
  int p;
  vector<mynode*> cs;
};


map<mynode*, int> m;
int maxSumPopulation(mynode* R){
  if(R==0) return 0;
  if(R->cs.empty()) return m[R]=R->p;
  if(m.count(R))
    return m[R];
  int x=R->p;
  for(mynode* c: R->cs){
    for(mynode* cc: c->cs){
      x+=maxSumPopulation(cc);
    }
  }
  int y=0;
  for(mynode* c: R->cs){
    y+=maxSumPopulation(c);
  }
  return m[R]=max(x,y);
}

void test2(){
  mynode n1={900};
  mynode n2={1};
  mynode n3={2};
  mynode n4={100};
  mynode n5={1000};
  n3.cs.push_back(&n4);
  n2.cs.push_back(&n3);
  n1.cs.push_back(&n2);
  n1.cs.push_back(&n5);
  cout << maxSumPopulation(&n1) << endl;
}



}

#endif //PNSEI_SNAPCHAT_H
