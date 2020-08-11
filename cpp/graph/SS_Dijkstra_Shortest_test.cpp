#include "gtest/gtest.h"
#include "SS_Dijkstra_Shortest.h"

// http://sde.quant365.com/graph.html#dijkstra-algorithm
TEST(test, test_dijkstra){
  vector<vector<int>> graph = {
      {1, 2, 24},
      {1, 4, 20},
      {3, 1, 3},
      {4, 3, 12},

      {2, 1, 24},
      {4, 1, 20},
      {1, 3, 3},
      {3, 4, 12}
  };
  vector<int> r = {24, 3, 15};
  EXPECT_EQ(r,graph_Dijkstra::shortestReach(4, graph, 1));
}

