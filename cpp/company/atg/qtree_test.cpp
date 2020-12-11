#include <gtest/gtest.h>
#include "qtree.h"

TEST(quadtree, a){
  using namespace atg;
  vector<vector<int>> m={{2,2,3,3},
                         {2,2,3,3},
                         {4,2,5,5},
                         {2,3,5,5}};
  quadtree* q = make_quadtree(m);
  EXPECT_EQ(q->cn[0]->val, 2);
  EXPECT_TRUE(q->cn[0]->leaf());
  EXPECT_FALSE(q->leaf());
}

TEST(quadtree, b){
  using namespace atg;
  vector<vector<int>> m={{2,2,3,3,3},
                         {2,2,3,3,3},
                         {4,2,5,5,5},
                         {2,3,5,5,5}};
  quadtree* q = make_quadtree(m);
  EXPECT_EQ(q->cn[0]->val, 2);
  EXPECT_TRUE(q->cn[0]->leaf());
  EXPECT_FALSE(q->leaf());
}