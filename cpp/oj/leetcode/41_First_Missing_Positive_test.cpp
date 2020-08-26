#include <gtest/gtest.h>
#include "41_First_Missing_Positive.h"

TEST(_41_First_Missing_Positive, a){
  using namespace _41;
  Solution sln;
  vector<int> vi={3,9,-1,1};
  int res = sln.firstMissingPositive(vi);
  EXPECT_EQ(res, 2);
}

TEST(_41_First_Missing_Positive, b){
  using namespace _41;
  Solution sln;
  vector<int> vi={};
  int res = sln.firstMissingPositive(vi);
  EXPECT_EQ(res, 1);
}

TEST(_41_First_Missing_Positive, c){
  using namespace _41;
  Solution sln;
  vector<int> vi={1,2};
  int res = sln.firstMissingPositive(vi);
  EXPECT_EQ(res, 3);
}
