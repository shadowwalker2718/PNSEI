#include <gtest/gtest.h>
#include "787_Cheapest_Flights_Within_K_Stops.h"

TEST(graph, 787_Cheapest_Flights_Within_K_Stops){
  using namespace _787;
  VVI flights={{0,1,100},{1,2,100},{0,2,500}};
  EXPECT_TRUE(Solution().findCheapestPrice(3, flights, 0, 2, 0)==500);
  EXPECT_TRUE(Solution().findCheapestPrice(3, flights, 0, 2, 1)==200);
}