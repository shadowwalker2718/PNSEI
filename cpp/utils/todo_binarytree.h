#pragma once

#include "henry.h"

/////////////////////////////////////////////////////////////////////////////////
// binary tree
struct TreeNode { // leetcode def
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
typedef TreeNode BTNode;

// binary tree node with parent link
struct BTPNode {
  int val;
  BTPNode *left;
  BTPNode *right;
  BTPNode *parent;
  BTPNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

struct AVLTreeNode {
  int val, height;
  AVLTreeNode *left;
  AVLTreeNode *right;
  AVLTreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};

// ternary tree node
struct TTNode {
    int val = 0;
    TTNode *l = 0;
    TTNode *m = 0;
    TTNode *r = 0;
    TTNode(int v) : val(v), l(0), m(0), r(0) {}
};

// Nary node - n is unkown beforehand
struct NTNode {
    char key;
    vector<NTNode *> children;  // An array of pointers for N children
};

// list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

TreeNode *createTree1();
// complete tree
TreeNode *createTree2();
TreeNode *createTree3();
TreeNode *createTree4();
BTPNode *createTree5();

TreeNode *create_A_BST();

// https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
/*
```
       15
   10       5
 9   1   2   3
4 5
```
*/
TreeNode *build_segment_tree_algo1(const vector<int>& v);
TreeNode *build_segment_tree_algo2(const vector<int>& v);
int dep_by_node(TreeNode* n);
void print_binary_tree_horizontal_dfs(TreeNode* n, vector<vector<string>>& r, int i, int j, int c);
void print_binary_tree_horizontal(TreeNode* root);
void print_binary_tree_vertical(TreeNode* root);
void print2D(TreeNode *root);
void cleanup();
void binarytree_test();
void binarytree_test_bug();





