#include <gtest/gtest.h>
#include "number_of_islands_variant1.h"

TEST(number_of_islands_variant1, a) {
  using namespace _cruise_islands;
  Solution sln;
  auto vs = sln.generateIslands(20, 30);
  sln.printBoard(vs);
  EXPECT_TRUE(sln.numIslands_different_char_ufo(vs)==152);
  EXPECT_TRUE(sln.numIslands_different_char_ufo2(vs)==148);
  EXPECT_TRUE(sln.numIslands_different_char(vs) == 152);
  EXPECT_TRUE(sln.numIslands_different_char_left_right_connected(vs) == 148);
  vs = sln.generateIslands(4, 5);
  sln.printBoard(vs);
  /*
    0 1 2 2 3
    0 1 1 2 3
    0 1 2 2 3
    0 1 1 2 3*/
  EXPECT_TRUE(sln.numIslands_different_char(vs) == 4);
  EXPECT_TRUE(sln.numIslands_different_char_left_right_connected(vs) == 4);
}

TEST(number_of_islands_variant1, b) {
  using namespace _cruise_islands;
  Solution sln;
  auto vs = sln.generateIslands(3, 3);
  sln.printBoard(vs);
  EXPECT_EQ(sln.numIslands_different_char_ufo(vs), 3);
}

TEST(number_of_islands_variant1, c) {
  using namespace _cruise_islands;
  Solution sln;
  auto vs = sln.generateIslands(4, 5);
  sln.printBoard(vs);
  /*
    0 1 2 2 3
    0 1 1 2 3
    0 1 2 2 3
    0 1 1 2 3*/
  EXPECT_TRUE(sln.numIslands_different_char(vs) == 4);
  EXPECT_TRUE(sln.numIslands_different_char_left_right_connected(vs) == 4);

  cout << endl;
  sln.set_grid(1,4,'2');
  sln.printBoard(sln.grid);
  cout << sln.numIslands_different_char(sln.grid) << endl;
}

TEST(number_of_islands_variant1, d) {
  using namespace _cruise_islands;
  Solution sln;
  auto vs = sln.generateIslands(4, 5);
  sln.printBoard(vs);
  /*
    0 1 2 2 3
    0 1 1 2 3
    0 1 2 2 3
    0 1 1 2 3*/
  islands o(vs);
  EXPECT_TRUE(o.island_number() == 4);
  o.set_grid(1,4,'2');
  sln.printBoard(o.grid);
  EXPECT_TRUE(o.island_number() == 5);
  o.set_grid(1,4,'3');
  EXPECT_TRUE(o.island_number() == 4);
  o.set_grid(2,1,'2');
  EXPECT_TRUE(o.island_number() == 5);
}
