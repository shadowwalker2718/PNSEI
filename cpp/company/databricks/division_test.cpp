#include <gtest/gtest.h>
#include "division.h"

TEST(division, add_sub){
  using namespace databricks;
  auto r=division_with_add_sub2(11,2);
  EXPECT_TRUE(r.first==5);
  EXPECT_TRUE(r.second==1);
}