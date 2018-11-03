#pragma once

#include "henry.h"

/////////////////////////////////////////////////////////////////////////////////
// binary tree
struct treenode {
  int val = 0;
  treenode *l = 0;
  treenode *r = 0;
  treenode(int v) : val(v), l(0), r(0) {}
};

// ternary tree node
struct ttnode {
    int val = 0;
    ttnode *l = 0;
    ttnode *m = 0;
    ttnode *r = 0;
    ttnode(int v) : val(v), l(0), m(0), r(0) {}
};

// Nary node
struct nnode {
    char key;
    vector<nnode*> children;  // An array of pointers for N children
};

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

treenode *createTree1();
// complete tree
treenode *createTree2();
treenode *createTree3();
treenode *createTree4();

// https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
/*
```
       15
   10       5
 9   1   2   3
4 5
```
*/
treenode *build_segment_tree_algo1(const vector<int>& v);
treenode *build_segment_tree_algo2(const vector<int>& v);
int dep_by_node(treenode* n);
void print_binary_tree_horizontal_dfs(treenode* n, vector<vector<string>>& r, int i, int j, int c);
void print_binary_tree_horizontal(treenode* root);
void print_binary_tree_vertical(treenode* root);
void binarytree_test();





