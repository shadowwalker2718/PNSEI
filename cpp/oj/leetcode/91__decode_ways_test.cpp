#include "gtest/gtest.h"
#include "91__decode_ways.h"

TEST(_91__decode_ways, basic){
  _91::Solution sln;
  EXPECT_EQ(0, sln.numDecodings("100"));
  EXPECT_EQ(0, sln.numDecodings("0"));
  EXPECT_EQ(0, sln.numDecodings(""));
  EXPECT_EQ(0, sln.numDecodings("01"));
  EXPECT_EQ(1, sln.numDecodings("10"));
  EXPECT_EQ(2, sln.numDecodings("11"));
}