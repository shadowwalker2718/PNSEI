#pragma once

#include "pnsei.h"
#include "utils/todo_binarytree.h"

namespace blowoff_leaf {

void dfs(TreeNode *c, int k, int &md) {
  if (!c) {
    md = 0;
    return;
  }
  if (!c->left && !c->right) {
    md = 1;
    return;
  }
  int d1 = 0, d2 = 0;
  dfs(c->left, k, d1);
  dfs(c->right, k, d2);
  md = max(d1, d2) + 1;
  if (md == k + 1) {
    c->left = c->right = 0;
  }
}

int dfs(TreeNode *c, int k) {
  if (!c) {
    return 0;
  }
  if (!c->left && !c->right) {
    return 1;
  }
  int md = max(dfs(c->left, k), dfs(c->right, k)) + 1;
  if (md == k + 1)
    c->left = c->right = 0;
  return md;
}

TreeNode *blowoff(TreeNode *R, int k) {
  if (!R || k <= 0)
    return R;
  int mdep = 0;
  // dfs(R, k, mdep);
  dfs(R, k);
  return R;
}

void test() {
  TreeNode *p = createTree1();
  TreeNode *r = blowoff(p, 2);
  assert(r->val == 2);
  assert(r->left->val == 7);
  assert(r->left->left == 0);
  assert(r->left->right == 0);
  assert(r->right->val == 5);
  assert(r->right->left == 0);
  assert(r->right->right == 0);
}

} // namespace blowoff_leaf
