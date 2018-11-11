//
// Created by root on 11/6/18.
//

#ifndef PNSEI_CLOSEST_CAR_H
#define PNSEI_CLOSEST_CAR_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=455844&highlight=cruise
 * 2018(10-12月)-[10]MFE/Fin/FinMath博士+<3个月短暂实习/全职 - 内推|Chicago MachineLearningEng全职@cruisefresh grad应届毕业生
 *
对方先介绍了公司情况,然后就是聊简历,不知道怎么准备,结结巴巴的,后来做题就好了.
问的是一个matrix,其中一个点是起点P,周围有4个车,问**最近的**到任意一个车的距离.

 当时觉得用dfs,bfs,和用heap run dijstra4次都能做,但跑4
 次某些点肯定会重复计算.写的时候用的是bfs+map,做完了让我优化,对方的意思是用heap,并且遇到其中一个车就return.我是顺着他说,所以都聊的
 挺好的.但疑问是,如果用heap,不应该在压入pq的时候就return吧,因为先压入的不一定是最短的.其次不管so far的是不是最短的,都要检查暂时不
 是最短的最后会不会relax,以及找到了一个车,还要继续搜索其它三个车的距离进行比较,先搜后搜都没关系.
 *
 * */



#endif //PNSEI_CLOSEST_CAR_H
