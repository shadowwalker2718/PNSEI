//
// Created by Henry Wu on 11/6/18.
//

#ifndef PNSEI_MINESWEEPER_H
#define PNSEI_MINESWEEPER_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=437824&highlight=cruise
 * 店面 : 扫雷游戏,从随机生成雷开始写.最后时间还有就又做了一个linkedlist 简单排序, 给一个target,小的在前,大的在后.
 *
 * LATTES 发表于 2018-8-13 03:50
想问一下随机生成雷这个用什么方法啊,就是n个格子k个雷,复杂度达到o(k)的算法..

>>>> random出两个数,作为row, col.一共生成k对不一样的就行.

 好吧我一直在想那种类似Reservoir sampling 先把头k个设置成雷然后用swap来分布,保证每个位置的概率都是k/n呢...一个一个生成感觉不能保证
 这个概率啊

 DavidLi210 发表于 2018-10-25 08:45
可否问下LZ扫雷游戏 这一道题还有其他的要求吗 只要求生成雷区就好了?

生成雷区,"bomb","num""empty"和 "undiscovered"表示每个格子的状态,然后就是随机点一个格子,显示结果棋局的样子.

 DavidLi210 发表于 2018-10-25 11:43
可以给个例子吗,是要像真的扫雷那样 点一个undiscovered格子 周围一片都空了然后继续点 但如果点到一个 ...

对,就是像真的扫雷一样. 点一个"undiscovered".如果**是数字就开一个,如果是雷就gameover,如果是空白就四个方向延伸,直到数字或者边界**.所以
 在游戏开始之前就要预处理棋盘,将每个格子的最终状态计算出来.开始游戏之后就是一个递归打开格子就可以.

 DavidLi210 发表于 2018-10-25 13:47
你提到 - 开始游戏之后就是一个递归打开格子就可以. 这个是什么意思啊,是只从一个给定的位置开始直接做 ...

对,只从一个格子
*/
#include "pnsei.h"

namespace _529_minesweeper {
class Solution {
public:
  Solution(){srand(0xdeadbeef);}
  vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click) {
    int R = board.size(), C = board[0].size();
    int x = click[0], y = click[1];
    if (board[x][y] == 'M') {
      board[x][y] = 'X';
      cout << "Game Over! Lose!!" << endl;
      return board;
    }
    // counter how many mines near the click point
    int counter = 0;
    for (int i = -1; i <= 1; i++){
      for (int j = -1; j <= 1; j++) {
        if(i==0 && j==0) continue;
        int nx = x + i, ny = y + j;
        if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
        if (board[nx][ny] == 'M') counter++;
      }
    }
    //display
    if (counter > 0) {
      board[x][y] = counter + '0';
      return board;
    } else { // if the counter is 0, it makes sense to show up all the cells adjacent to it.
      board[x][y] = 'B';
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
          int nx = x + i, ny = y + j;
          if (nx < 0 || nx >= R || ny < 0 || ny >= C || board[nx][ny] != 'E') continue;
          vector<int> nextClick = {nx, ny};
          updateBoard(board, nextClick);
        }
      return board;
    }
  }
  VVC generateBoard(int R, int C, int k){// RxC cells and k mines
    VVC b(R, VC(C,'E'));
    while(k--){
      b[rand()%R][rand()%C] = 'M';
    }
    return b;
  }
  void run(){
    auto board=generateBoard(10,20,20);
    int i=0;
    while(true){
      printBoard(board);
      int x, y;
      cout << "Please input two coordinates:\n";
      cin>> x >> y;
      VI click={x,y};
      updateBoard(board,click);
      cout << string(40,'*') << "Jack Wu Step "<< i++ << string(40,'*') << endl;
    }
  }
  void printBoard(VVC board){
    for (int i = 0; i < board.size(); ++i) {
      for(char c: board[i])
        cout << (c=='M'?'E':c) << ' ';
      cout << endl;
    }
  }
};



void test() {
  Solution sln;
  sln.run();
  VVC board = {{'E', 'E', 'E', 'E', 'E'},
               {'E', 'E', 'M', 'E', 'E'},
               {'E', 'E', 'E', 'E', 'E'},
               {'E', 'E', 'E', 'E', 'E'}};
  VI click={3,0};
  sln.updateBoard(board,click);
  /*VI click={3,0};
  printBoard(board);
  sln.updateBoard(board,click);
  cout << string(40,'*') << "Jack Wu 1" << string(40,'*') << endl;
  printBoard(board);

  click={0,2};
  sln.updateBoard(board,click);
  cout << string(40,'*') << "Jack Wu" << string(40,'*') << endl;
  printBoard(board);
  int i=0;
  while(true){
    int x, y;
    cin>> x;
    cin>> y;
    VI click={x,y};
    printBoard(board);
    sln.updateBoard(board,click);
    cout << string(40,'*') << "Jack Wu Step "<< i++ << string(40,'*') << endl;
    printBoard(board);
  }*/




}
}

#endif //PNSEI_MINESWEEPER_H
