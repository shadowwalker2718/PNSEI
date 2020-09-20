#include "149_Max_Points_on_a_Line.h"
#include <gtest/gtest.h>

TEST(_149_Max_Points_on_a_Line, a){
  using namespace _149;
  {
    Solution sln;
    vector<Point> ps = {{0, 0}, {1, 1}, {1, -1}};
    EXPECT_TRUE(sln.maxPoints(ps) == 2);
  }
  {
    Solution sln;
    vector<Point> ps = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    EXPECT_TRUE(sln.maxPoints_v2(ps) == 4);
  }
  {
    Solution2 sln;
    vector<Point> ps = {{0, 0}};
    EXPECT_TRUE(sln.maxPoints(ps) == 1);
  }
  {
    Solution2 sln;
    vector<Point> ps = {{0, 0}, {100, 10}, {100, 10}};
    int r = sln.maxPoints(ps);
    EXPECT_TRUE( r == 3);
  }


}