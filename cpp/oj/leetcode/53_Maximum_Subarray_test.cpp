#include <gtest/gtest.h>
#include "53_Maximum_Subarray.h"

TEST(_53_Maximum_Subarray, basic){
  using namespace _53;
  Solution sln;
  vector<int> vi = {1,2,3,4};
  EXPECT_EQ(sln.maxSubArray(vi), 10);
}


TEST(_53_Maximum_Subarray, followup){
  using namespace _53;
  Solution sln;
  vector<int> vi = {1,2,3,4};
  auto r=sln.maxSubArray_followup(vi);
  EXPECT_EQ(get<0>(r), 0);
  EXPECT_EQ(get<1>(r), 3);
  EXPECT_EQ(get<2>(r), 10);
  auto r2=sln.maxSubArray_followup2(vi);
  EXPECT_EQ(r, r2);

  vi = {-1,-2,-3,-4};
  r=sln.maxSubArray_followup(vi);
  EXPECT_EQ(get<0>(r), 0);
  EXPECT_EQ(get<1>(r), 0);
  EXPECT_EQ(get<2>(r), -1);
  r2=sln.maxSubArray_followup2(vi);
  EXPECT_EQ(r, r2);

  vi = {-1};
  r=sln.maxSubArray_followup(vi);
  EXPECT_EQ(get<0>(r), 0);
  EXPECT_EQ(get<1>(r), 0);
  EXPECT_EQ(get<2>(r), -1);

  r2=sln.maxSubArray_followup2(vi);
  EXPECT_EQ(r, r2);
}

TEST(_53_Maximum_Subarray, followup2){
  using namespace _53;
  Solution sln;
  auto vi={-2,1,-3,4,-1,2,1,-5,4};
  auto r1=sln.maxSubArray_followup(vi);
  auto r2=sln.maxSubArray_followup2(vi);
  EXPECT_EQ(r1, r2);
}