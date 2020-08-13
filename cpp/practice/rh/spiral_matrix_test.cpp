#include <gtest/gtest.h>
#include "spiral_matrix.h"

TEST(rh, sm){
  Solution sln;
  auto r = sln.spiralOrder({{1, 2, 3}, { 4, 5, 6 }, { 7, 8, 9 }});
  vector<int> expected={1,2,3,6,9,8,7,4,5};
  EXPECT_EQ(r, expected);
}

TEST(rh, sm2){
  Solution sln;
  auto r = sln.spiralOrder({});
  vector<int> expected={};
  EXPECT_EQ(r, expected);
}

TEST(rh, sm3){
  Solution sln;
  auto r = sln.spiralOrder({{1}});
  vector<int> expected={1};
  EXPECT_EQ(r, expected);
}

TEST(rh, sm4){
  Solution sln;
  auto r = sln.spiralOrder({{1,2,3}});
  vector<int> expected={1,2,3};
  EXPECT_EQ(r, expected);
}

TEST(rh, sm5){
  Solution sln;
  auto r = sln.spiralOrder({{1},{2},{3}});
  vector<int> expected={1,2,3};
  EXPECT_EQ(r, expected);
}