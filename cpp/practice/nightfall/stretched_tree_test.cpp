#include "gtest/gtest.h"
#include "stretched_tree.h"

TEST(night_fall, basic){
  TreeNode* r = createTree1();
  Stretcher stretcher;
  stretcher.stretch(r, 2);
  cout << r->val << endl;
}

TEST(night_fall, empty_tree){
  TreeNode* r = nullptr;
  Stretcher stretcher;
  stretcher.stretch(r, 2);
}

TEST(night_fall, invalid_argument){
  TreeNode* r = createTree1();
  Stretcher stretcher;
  stretcher.stretch(r, 0);
  stretcher.stretch(r, -1);
  stretcher.stretch(r, INT_MAX);
  stretcher.stretch(r, INT_MIN);
}

