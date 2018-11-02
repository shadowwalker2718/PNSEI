#pragma once

#include "henry.h"

struct treenode {
  int val = 0;
  treenode *l = 0;
  treenode *r = 0;
  treenode(int v) : val(v), l(0), r(0) {}
};

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

treenode *createTree1() {
  treenode *R = new treenode(2);
  R->l = new treenode(7);
  R->r = new treenode(5);
  R->r->r = new treenode(9);
  R->r->r->l = new treenode(4);

  R->l->l = new treenode(2);
  R->l->r = new treenode(6);
  R->l->r->l = new treenode(5);
  R->l->r->r = new treenode(11);
  return R;
}

// complete tree
treenode *createTree2(){
  /*0,1,2,3...  ==> left 2i, right 2i+1*/
  vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15,13};
  int L=v.size();
  vector<treenode*> vn(L);
  for (int i=L-1; i>0; i--) {
    vn[i] = new treenode(v[i]);
    if(2*i < L){
      vn[i]->l = vn[2*i];
    }
    if(2*i+1 < L){
      vn[i]->r = vn[2*i+1];
    }
  }
  return vn[1];
};

treenode *createTree3(){
  /*0,1,2,3...  ==> left 2i, right 2i+1*/
  vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15};
  int L=v.size();
  vector<treenode*> vn(L);
  for (int i=L-1; i>0; i--) {
    vn[i] = new treenode(v[i]);
    if(2*i < L){
      vn[i]->l = vn[2*i];
    }
    if(2*i+1 < L){
      vn[i]->r = vn[2*i+1];
    }
  }
  return vn[1];
};

treenode *createTree4(){
  /*0,1,2,3...  ==> left 2i, right 2i+1*/
  vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15};
  int L=v.size();
  vector<treenode*> vn(L);
  for (int i=L-1; i>0; i--) {
    vn[i] = new treenode(v[i]);
    if(2*i < L){
      vn[i]->l = vn[2*i];
    }
    if(2*i+1 < L){
      vn[i]->r = vn[2*i+1];
    }
  }
  return vn[1];
};

// https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
/*
```
       15
   10       5
 9   1   2   3
4 5
```
*/
treenode *build_segment_tree_algo1(const vector<int>& v){ // sum segment tree
  int L=v.size();
  vector<treenode*> vn(L*2);
  for(int i=0;i<L;i++){
    vn[i+L] = new treenode(v[i]);
  }
  for(int i=L-1;i>0;i--){
    int t=vn[2*i]->val + vn[2*i+1]->val;
    vn[i] = new treenode(t);
    vn[i]->l = vn[2*i];
    vn[i]->r = vn[2*i+1];
  }
  return vn[1];
};

int dep_by_node(treenode* n){
    return n==0?0:max(dep_by_node(n->l), dep_by_node(n->r))+1;
}

void print_binary_tree_horizontal_dfs(treenode* n, vector<vector<string>>& r, int i, int j, int c){
    if(!n) return;
    r[i][j] = to_string(n->val); // preorder traversal
    int distance = (c+1)/2;
    print_binary_tree_horizontal_dfs(n->l, r, i+1, j-distance, c/2);
    print_binary_tree_horizontal_dfs(n->r, r, i+1, j+distance, c/2);
}

void print_binary_tree_horizontal(treenode* root){
    int R=dep_by_node(root), C=(1<<R)-1;
    if(R==0) return;
    vector<vector<string>> res(R, vector<string>(C, " "));
    print_binary_tree_horizontal_dfs(root,res,0,C/2,C/2);
    for(auto vs: res){
        for(string& s: vs)
            cout << s ;
        cout << endl;
    }
}


void print_binary_tree_vertical(treenode* root){

}


void binarytree_test();





