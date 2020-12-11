#ifndef PNSEI_QTREE_H
#define PNSEI_QTREE_H
#include "pnsei.h"

namespace atg{

struct quadtree{
  // leaf node has value
  int val;
  // children number is 4, so it is called quad
  quadtree* cn[4]={};
  // construct a leaf node
  quadtree(int v): val(v){}
  // construct an inner node
  quadtree(quadtree* a,quadtree* b,quadtree* c,quadtree* d){
    cn[0]=a, cn[1]=b, cn[2]=c, cn[3]=d;
  }
  bool leaf(){
    return all_of(cn,cn+3,[](quadtree* x){return x== nullptr;});
  }
};

bool valid_index(vector<vector<int>>& m, int x1, int x2, int y1, int y2){
  return !(x1>x2 or y1>y2 or x1>=m.size() or x2>=m.size() or y1>=m[0].size() or y2>=m[0].size());
}

quadtree* make_qtree(vector<vector<int>>& m, int x1, int x2, int y1, int y2){
  if (x1==x2 and y1==y2){
    return new quadtree(m[x1][y1]);
  }
  quadtree* a= nullptr, *b= nullptr, *c= nullptr, *d= nullptr;
  if(valid_index(m,x1,x1+(x2-x1)/2,y1,y1+(y2-y1)/2))
    a = make_qtree(m,x1,x1+(x2-x1)/2,y1,y1+(y2-y1)/2);
  if(valid_index(m,x1,x1+(x2-x1)/2,y1+(y2-y1)/2+1,y2))
    b = make_qtree(m,x1,x1+(x2-x1)/2,y1+(y2-y1)/2+1,y2);
  if(valid_index(m,x1+(x2-x1)/2+1,x2,y1,y1+(y2-y1)/2))
    c = make_qtree(m,x1+(x2-x1)/2+1,x2,y1,y1+(y2-y1)/2);
  if(valid_index(m,x1+(x2-x1)/2+1,x2,y1+(y2-y1)/2+1,y2))
    d = make_qtree(m,x1+(x2-x1)/2+1,x2,y1+(y2-y1)/2+1,y2);

  if (a==nullptr or b==nullptr or c== nullptr or d== nullptr)
    return new quadtree(a,b,c,d);

  if (a->val == b->val and b->val == c->val and c->val == d->val){
    return new quadtree(a->val);
  } else {
    return new quadtree(a,b,c,d);
  }
}

quadtree* make_quadtree(vector<vector<int>>& m){
  if (m.empty() or m[0].empty())
    return nullptr;
  int R=m.size(), C=m[0].size();
  make_qtree(m, 0, R-1, 0, C-1);
}

}

#endif // PNSEI_QTREE_H
