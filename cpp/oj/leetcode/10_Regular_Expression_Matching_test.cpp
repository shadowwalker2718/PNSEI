#include <gtest/gtest.h>
#include "10_Regular_Expression_Matching.h"

TEST(_10_Regular_Expression_Matching, a){
  using namespace _10;
  Solution    sln;
  Solution_DP sln2;

  string s = "mississippi";
  string p = "mis*is*p*.";
  assert(sln.isMatch(s, p) == sln2.isMatch(s, p));

  s="aa", p="a*";
  assert(sln2.isMatch(s, p) == 1);

  // invalid example as we require all inputs are valid
  //s="aa", p="*a";
  //assert(sln2.isMatch(s, p) == 1);
}

TEST(_10_Regular_Expression_Matching, dp){
  using namespace _10;

  Solution_DP sln2;

  string s = "mississippi";
  string p = "mis*is*p*.";
  EXPECT_FALSE(sln2.isMatch(s, p));

  s="aa", p="a*";
  EXPECT_EQ(sln2.isMatch(s, p), 1);
}