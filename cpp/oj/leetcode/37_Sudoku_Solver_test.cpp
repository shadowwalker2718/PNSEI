#include <gtest/gtest.h>
#include "37_Sudoku_Solver.h"

TEST(oj, _37_Sudoku_Solver){
  using namespace _37_dfs;
  vector<vector<char>> m = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  Solution sln;
  SolutionX sx;
  assert(sx.isValidSudoku(m));
  sln.solveSudoku(m);
  assert(sx.isValidSudoku(m));
}