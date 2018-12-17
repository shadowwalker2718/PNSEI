//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_SHORTEST_PATH_H
#define PNSEI_SHORTEST_PATH_H

// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=447712&highlight=%BE%B0%B3%DB

/*
 * 2018(7-9月) 码农类General 硕士 全职@Jingchi - 内推 - 技术电面  | Fail | fresh grad应届毕业生
景驰new grad店面.国内朋友帮忙递的简历,之前有给个take home test, 两天之内做完.

一个是快递员送东西最短距离路线,类似二维数组找路径的.一个是求convex hull, 二维三维都有.(3D option,我觉得特麻烦特难写就没做)

题后面说明第一行写着可以用C++,Java或Python. 第二行说better to use C++/Python. Java选手写个Python写了好久.
过几天收到店面,今天下午面的.

很简单的二维数组,0能过1不能过,给start,end点找最短距离的,到不了就返回-1.
理应BFS秒解,但是我状态不太好,一个BFS写得挺慢的,还有几个小bug,调了两分钟调好了跑个case没问题.
followup1: 给k个点,求k1到剩下所有点的最短距离,按顺序输出.我给的是加个HashMap.只说了思路没写
followup2:还是k个点,求里面任意两个点所组成的pair中距离最短的.开始给的方法不好复杂度高,面试官给了提示我才终于给出O(MN)的方法.
没什么时间了就只写了几行sudo-code


全程中文,面试官人很nice,奈何自己太菜,连个BFS都能写出bug来,后面挺简单的思路也是半天才想出来,来不及写code,
按Jingchi的bar估计九成九是凉了,move on了.嗯他们基本不用Java,十成凉了

设一个visited的二维矩阵代表一个格子是否被访问过,初始化为-1,把所有的k个点处初始化为0.把点都放进queue中,还是做BFS,
每次访问到一个点就更新该处visited值为当前step,当BFS访问到之前访问到的点(>=0)时,distance = step + visited[j]. 即是最短的距离了

https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=449608&highlight=%BE%B0%B3%DB
2018(10-12月) 码农类General 硕士 全职@景驰 - 网上海投 - 技术电面  | Fail | fresh grad应届毕业生
上周三的挂经.求米~~
给矩阵,0可以通行,1为障碍物,找出指定的start和end之间的最短距离 // BFS
follow 1: 指定一个点start和list of ends,找出start 分别到这些ends 的最短距离 // BFS
follow 2:list of points,找出这些点之间的最短距离,这个没答上,应该就是这里挂了. // Multi-Source BFS
*/

#endif //PNSEI_SHORTEST_PATH_H
