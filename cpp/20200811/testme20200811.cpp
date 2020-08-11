#include "gtest/gtest.h"
#include "stretched_tree.h"

TEST(abc, efg){
  TreeNode* r = createTree1();
  Stretcher stretcher;
  stretcher.stretch(r, 2);
  cout << r->val << endl;
}

TEST(abc, empty_tree){
  TreeNode* r = nullptr;
  Stretcher stretcher;
  stretcher.stretch(r, 2);
}

TEST(abc, invalid_argument){
  TreeNode* r = createTree1();
  Stretcher stretcher;
  stretcher.stretch(r, 0);
  stretcher.stretch(r, -1);
  stretcher.stretch(r, INT_MAX);
  stretcher.stretch(r, INT_MIN);
}

