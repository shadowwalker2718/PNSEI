#include <gtest/gtest.h>
#include "8puzzle_AStar.h"

TEST(_8puzzle_AStar, a){
  using namespace addepar_AStar;
  iMatrix a = {{0, 1, 3},
               {4, 2, 5},
               {7, 8, 6}};
  solution sln;
  EXPECT_TRUE(sln.solve_bfs(a) == 4);
  sln.print_path(GOAL);
/*
0 1 3
4 2 5
7 8 6
********************************************************************************
1 0 3
4 2 5
7 8 6
********************************************************************************
1 2 3
4 0 5
7 8 6
********************************************************************************
1 2 3
4 5 0
7 8 6
********************************************************************************
1 2 3
4 5 6
7 8 0
********************************************************************************
*/
}