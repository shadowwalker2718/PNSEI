#pragma once

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
