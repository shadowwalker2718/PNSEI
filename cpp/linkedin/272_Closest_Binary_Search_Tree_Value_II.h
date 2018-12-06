//
// Created by Henry Wu on 12/4/18.
//

#ifndef PNSEI_272_CLOSEST_BINARY_SEARCH_TREE_VALUE_II_H
#define PNSEI_272_CLOSEST_BINARY_SEARCH_TREE_VALUE_II_H

#include "henry.h"
#include "utils/todo_binarytree.h"

namespace _272 {

// http://www.cnblogs.com/grandyang/p/5247398.html
// https://leetcode.com/problems/closest-binary-search-tree-value-ii/
struct Solution {
  vector<int> closestKValues(TreeNode *R, double T, int k) {
    vector<int> r;
    stack<TreeNode *> pre, suc;
    while (R) // O(LogN)
      if (R->val <= T)
        pre.push(R), R = R->right;
      else
        suc.push(R), R = R->left;
    while (k--) { // O(min(K*LogN,N))
      if (suc.empty() || !pre.empty() && (T - pre.top()->val < suc.top()->val - T)) {
        r.push_back(pre.top()->val);
        push_pre(pre);
      } else {
        r.push_back(suc.top()->val);
        push_suc(suc);
      }
    }
    return r;
  }

  void push_pre(stack<TreeNode *> &stk) {
    TreeNode *t = stk.top();
    stk.pop();
    if (!t->left)
      return;
    stk.push(t->left);
    while (stk.top()->right)
      stk.push(stk.top()->right);
  }

  void push_suc(stack<TreeNode *> &stk) {
    TreeNode *t = stk.top();
    stk.pop();
    if (!t->right)
      return;
    stk.push(t->right);
    while (stk.top()->left)
      stk.push(stk.top()->left);
  }
};

void test() {
  auto R = create_A_BST();
  print_binary_tree_horizontal(R);
  auto r = Solution().closestKValues(R, 9.6, 20);
  for (auto i: r) {
    cout << i << endl;
  }
}

}

#endif //PNSEI_272_CLOSEST_BINARY_SEARCH_TREE_VALUE_II_H
