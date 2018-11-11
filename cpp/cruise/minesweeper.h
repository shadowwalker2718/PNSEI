//
// Created by root on 11/6/18.
//

#ifndef PNSEI_MINESWEEPER_H
#define PNSEI_MINESWEEPER_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=437824&highlight=cruise
 * 店面 : 扫雷游戏,从随机生成雷开始写.最后时间还有就又做了一个 linkedlist 简单排序, 给一个target,小的在前,大的在后.
 *
 * LATTES 发表于 2018-8-13 03:50
想问一下随机生成雷这个用什么方法啊,就是n个格子k个雷,复杂度达到o k的算法..

random出两个数,作为row, col.一共生成k对不一样的就行.

 好吧我一直在想那种类似Reservoir sampling 先把头k个设置成雷然后用swap来分布,保证每个位置的概率都是k/n呢...一个一个生成感觉不能保证
 这个概率啊

 DavidLi210 发表于 2018-10-25 08:45
可否问下LZ扫雷游戏 这一道题还有其他的要求吗 只要求生成雷区就好了?

生成雷区,"bomb","num""empty"和 "undiscovered"表示每个格子的状态,然后就是随机点一个格子,显示结果棋局的样子.

 DavidLi210 发表于 2018-10-25 11:43
可以给个例子吗,是要像真的扫雷那样 点一个undiscovered格子 周围一片都空了然后继续点 但如果点到一个 ...

对,就是像真的扫雷一样. 点一个"undiscovered".如果是数字就开一个,如果是雷就gameover,如果是空白就四个方向延伸,直到数字或者边界.所以
 在游戏开始之前就要预处理棋盘,将每个格子的最终状态计算出来.开始游戏之后就是一个递归打开格子就可以.

 DavidLi210 发表于 2018-10-25 13:47
你提到 - 开始游戏之后就是一个递归打开格子就可以. 这个是什么意思啊,是只从一个给定的位置开始直接做 ...

对,只从一个格子
 * */

#endif //PNSEI_MINESWEEPER_H
