//
// Created by root on 11/3/18.
//

#ifndef PNSEI_37_SUDOKU_SOLVER_H
#define PNSEI_37_SUDOKU_SOLVER_H

#include "henry.h"

/*
 * 2017(1-3月) 码农类General 硕士 全职@Addepar - 网上海投 - 技术电面  | Pass | 在职跳槽
linkedin 上看到申请的，一轮电面问的lc原题 solve sudoku。写出来跑了下testcase。没什么问题，
 提前结束了。现在准备第二轮电面，发面经，攒人品 :)
 * */
namespace _37_dfs{

// https://leetcode.com/problems/valid-sudoku/
struct SolutionX { // 9ms 81%
  bool isValidSudoku(vector<vector<char> > &board) {
    if(board.size()!=9 || board[0].size()!=9) return false;
    // check row
    for(int i=0; i<9; i++) {
      vector<bool> used(9,false);
      for(int j=0; j<9; j++) {
        if(!isdigit(board[i][j])) continue;
        int k = board[i][j]-'0';
        if(k==0 || used[k-1]) return false;
        used[k-1] = true;
      }
    }
    //check col
    for(int j=0; j<9; j++) {
      vector<bool> used(9,false);
      for(int i=0; i<9; i++) {
        if(!isdigit(board[i][j])) continue;
        int k = board[i][j]-'0';
        if(k==0 || used[k-1]) return false;
        used[k-1] = true;
      }
    }
    // check subbox
    for(int i=0; i<3; i++) { // 1
      for(int j=0; j<3; j++) { // 2
        int row = 3*i, col = 3*j;
        vector<bool> used(9,false);
        for(int m=row; m<row+3; m++) { // 3
          for(int n=col; n<col+3; n++) { // 4
            if(!isdigit(board[m][n])) continue;
            int k = board[m][n]-'0';
            if(k==0 || used[k-1]) return false;
            used[k-1]=true;
          }
        }
      }
    }
    return true;
  }
};

// https://leetcode.com/problems/sudoku-solver/
struct Solution { // 16ms, 78%
  void solveSudoku(vector<vector<char> > &board) {
    if(board.size()<9 || board[0].size()<9) return;
    bool findSol = dfs(board, 0, 0);
  }
  bool dfs(vector<vector<char>> &board, int irow, int icol) {
    if(irow==9) return true;
    int irow2, icol2;
    if(icol==8)
      irow2 = irow+1, icol2 = 0;
    else
      irow2 = irow, icol2 = icol+1;
    if(board[irow][icol]!='.') {
      if(!isValid(board, irow, icol)) return false;
      return dfs(board, irow2, icol2);
    }
    for(int i=1; i<=9; i++) {
      board[irow][icol] = '0'+i;
      if(isValid(board, irow, icol) && dfs(board, irow2, icol2))
        return true;
    }
    board[irow][icol] = '.'; // reset grid
    return false;
  }
  bool isValid(vector<vector<char>> &board, int irow, int icol) {
    char val = board[irow][icol];
    if(val-'0'<1 || val-'0'>9) return false;
    for(int i=0; i<9; i++) { // check row & col
      if(board[irow][i]==val && i!=icol) return false;
      if(board[i][icol]==val && i!=irow) return false;
    }
    //check 3x3 box
    int irow0 = irow/3*3; int icol0 = icol/3*3;
    for(int i=irow0; i<irow0+3; i++)
      for(int j=icol0; j<icol0+3; j++)
        if(board[i][j]==val && (i!=irow || j!=icol)) return false;
    return true;
  }
};
}

#endif //PNSEI_37_SUDOKU_SOLVER_H
