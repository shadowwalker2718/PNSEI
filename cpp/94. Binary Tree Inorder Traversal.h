#pragma once
#include "henry.h"

namespace _94 {
// https://leetcode.com/problems/binary-tree-inorder-traversal/

/**Definition for a binary tree node.*/
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  vector<int> inorderTraversal_1(TreeNode *root) { // Recursive
    vector<int> r;
    rec(root, r);
    return r;
  }
  void rec(TreeNode *root, vector<int> &r) {
    if (root) {
      if (root->left)
        rec(root->left, r);
      r.push_back(root->val);
      if (root->right)
        rec(root->right, r);
    }
  }

  vector<int> inorderTraversal_2(TreeNode *root) { // Iterative
    vector<int> r;
    if (root) {
      stack<TreeNode *> stk;
      TreeNode *c = root;
      while (c)
        stk.push(c), c = c->left;
      while (!stk.empty()) {
        c = stk.top(), stk.pop();
        r.push_back(c->val);
        if (c->right) {
          c = c->right;
          while (c)
            stk.push(c), c = c->left;
        }
      }
    }
    return r;
  }

  vector<int> inorderTraversal_2_1(TreeNode *root) {
    vector<int> r;
    if (!root)
      return r;
    stack<TreeNode *> stk;
    TreeNode *c = root;
    while (!stk.empty() || c) {
      while (c)
        stk.push(c), c = c->left;
      c = stk.top(), stk.pop();
      if (c)
        r.push_back(c->val);
      c = c->right;
    }
    return r;
  }

  // Morris Traversal - Tree is modified and restored!!!
  // O(N)
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> r;
    if (!root)
      return r;
    TreeNode *c = root, *pre = 0;
    while (c) {
      if (c->left) {
        pre = c->left;
        while (pre->right && pre->right != c)
          pre = pre->right;
        if (pre->right) { // unwind stack
          pre->right = 0;
          r.push_back(c->val), c = c->right; ////!!!!
        } else
          pre->right = c, c = c->left; // connect to successor
      } else {
        r.push_back(c->val), c = c->right; ////!!!!
      }
    }
    return r;
  }
};

void test() {}
} // namespace _94
