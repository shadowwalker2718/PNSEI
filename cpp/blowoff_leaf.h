#pragma once

#include "binarytree.h"
#include "henry.h"

namespace blowoff_leaf {

  void dfs(TreeNode* c, int k, int& md) {
    if (!c) { md = 0; return; }
    if (!c->l && !c->r) { md = 1; return; }
    int d1 = 0, d2 = 0;
    dfs(c->l, k, d1);
    dfs(c->r, k, d2);
    md = max(d1, d2)+1;
    if (md == k + 1) {
      c->l = c->r = 0;
    }
  }

  int dfs(TreeNode* c, int k) {
    if (!c) { return 0; }
    if (!c->l && !c->r) { return 1; }
    int md =max(dfs(c->l, k), dfs(c->r, k))+1;
    if (md == k + 1)
      c->l = c->r = 0;
    return md;
  }

  TreeNode * blowoff(TreeNode *R, int k) {
    if (!R || k <= 0) return R;
    int mdep = 0;
    //dfs(R, k, mdep);
    dfs(R, k);
    return R;
  }

  void test() {
    TreeNode* p = createTree1();
    TreeNode* r = blowoff(p, 2);
    assert(r->val == 2);
    assert(r->l->val == 7);
    assert(r->l->l == 0);
    assert(r->l->r == 0);
    assert(r->r->val == 5);
    assert(r->r->l == 0);
    assert(r->r->r == 0);
  }
   


}




