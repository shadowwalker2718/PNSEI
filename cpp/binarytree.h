#pragma once

struct TreeNode {
  int val = 0;
  TreeNode *l = 0;
  TreeNode *r = 0;
  TreeNode(int v) : val(v), l(0), r(0) {}
};

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

TreeNode *createTree1() {
  TreeNode *R = new TreeNode(2);
  R->l = new TreeNode(7);
  R->r = new TreeNode(5);
  R->r->r = new TreeNode(9);
  R->r->r->l = new TreeNode(4);

  R->l->l = new TreeNode(2);
  R->l->r = new TreeNode(6);
  R->l->r->l = new TreeNode(5);
  R->l->r->r = new TreeNode(11);
  return R;
}
