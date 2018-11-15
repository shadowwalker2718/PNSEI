//
// Created by root on 11/3/18.
//

#ifndef PNSEI_37_SUDOKU_SOLVER_H
#define PNSEI_37_SUDOKU_SOLVER_H

#include "henry.h"

/*
 * 2017(1-3月) 码农类General 硕士 全职@Addepar - 网上海投 - 技术电面  | Pass | 在职跳槽
linkedin 上看到申请的,一轮电面问的lc原题 solve sudoku.写出来跑了下testcase.没什么问题,
 提前结束了.现在准备第二轮电面,发面经,攒人品 :)
 * */
namespace _37_dfs {

// https://leetcode.com/problems/valid-sudoku/
struct SolutionX { // 9ms 81%
  bool isValidSudoku(vector<vector<char> > &board) {
    if (board.size() != 9 || board[0].size() != 9) return false;
    // check row
    for (int i = 0; i < 9; i++) {
      vector<bool> used(9, false);
      for (int j = 0; j < 9; j++) {
        if (!isdigit(board[i][j])) continue;
        int k = board[i][j] - '0';
        if (k == 0 || used[k - 1]) return false;
        used[k - 1] = true;
      }
    }
    //check col
    for (int j = 0; j < 9; j++) {
      vector<bool> used(9, false);
      for (int i = 0; i < 9; i++) {
        if (!isdigit(board[i][j])) continue;
        int k = board[i][j] - '0';
        if (k == 0 || used[k - 1]) return false;
        used[k - 1] = true;
      }
    }
    // check subbox
    for (int i = 0; i < 3; i++) { // 1
      for (int j = 0; j < 3; j++) { // 2
        int row = 3 * i, col = 3 * j;
        vector<bool> used(9, false);
        for (int m = row; m < row + 3; m++) { // 3
          for (int n = col; n < col + 3; n++) { // 4
            if (!isdigit(board[m][n])) continue;
            int k = board[m][n] - '0';
            if (k == 0 || used[k - 1]) return false;
            used[k - 1] = true;
          }
        }
      }
    }
    return true;
  }
};

// https://leetcode.com/problems/sudoku-solver/
struct Solution { // 16ms, 78%
  void solveSudoku(vector<vector<char> > &board);

  bool dfs(vector<vector<char>> &board, int irow, int icol);

  // if we could not find duplicates, it is valid!!
  bool isValid(vector<vector<char>> &board, int irow, int icol);
};

// return if the path so far is valid?
bool Solution::dfs(vector<vector<char>> &board, int irow, int icol) {
  if (irow == 9) return true; // base case
  // 1. to get next step's coordinates
  int irow2, icol2;
  if (icol == 8)
    irow2 = irow + 1, icol2 = 0; // move to the beginning of next line
  else
    irow2 = irow, icol2 = icol + 1;  // move left
  // 2. check if the current indices are valid, MOVE to next step
  if (board[irow][icol] == '.') { // we need to try to fill `1`~`9`
    for (int i = 1; i <= 9; i++) {
      board[irow][icol] = '0' + i;
      if (isValid(board, irow, icol) and dfs(board, irow2, icol2))
        return true;
    }
    board[irow][icol] = '.'; // reset grid - unwind
    return false;
  } else { // validate existing digit (in char form)
    if (isValid(board, irow, icol))
      return dfs(board, irow2, icol2);
    else
      return false;
  }
}

bool Solution::isValid(vector<vector<char>> &board, int irow, int icol) {
  char target_value = board[irow][icol];
  if (target_value - '0' < 1 || target_value - '0' > 9) return false;
  for (int i = 0; i < 9; i++) { // check row & col
    if (board[irow][i] == target_value && i != icol) return false;
    if (board[i][icol] == target_value && i != irow) return false;
  }
  //check 3x3 box -- locate the correct index!!!
  int X = irow / 3 * 3;
  int Y = icol / 3 * 3;
  for (int i = X; i < X + 3; i++)
    for (int j = Y; j < Y + 3; j++)
      if (board[i][j] == target_value && (i != irow || j != icol))
        return false;
  return true;
}

void Solution::solveSudoku(vector<vector<char> > &board) {
  if (board.size() < 9 || board[0].size() < 9) return;
  bool findSol = dfs(board, 0, 0);
}

void test() {
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
}

#endif //PNSEI_37_SUDOKU_SOLVER_H
