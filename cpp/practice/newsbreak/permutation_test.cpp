#include <gtest/gtest.h>
#include "permutation.h"
#include "permutation_uniq.h"

TEST(permutation, a){
  return;
  using namespace nb;
  auto r = perm("abc");
  EXPECT_EQ(r.size(), 6);
}

TEST(permutation, b){
  using namespace nb2;
  auto r = perm("acc");
  EXPECT_EQ(r.size(), 3);
}