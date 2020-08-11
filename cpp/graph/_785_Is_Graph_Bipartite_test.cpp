#include "gtest/gtest.h"
#include "_785_Is_Graph_Bipartite.h"

/*
  0----1
  | \  |
  |  \ |
  3----2
*/
TEST(test, test1){
  vector<vector<int>> vvi={{1,2,3}, {0,2}, {0,1,3}, {0,2}};
  EXPECT_EQ(_785_Is_Graph_Bipartite::isBipartite_BFS(vvi), false);
}