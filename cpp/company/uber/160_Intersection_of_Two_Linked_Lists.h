//
// Created by Henry Wu on 11/12/18.
//

#ifndef PNSEI_160_INTERSECTION_OF_TWO_LINKED_LISTS_H
#define PNSEI_160_INTERSECTION_OF_TWO_LINKED_LISTS_H

#include "pnsei.h"

namespace _160{

/*
 * uber的整个招聘过程也是很需要耐心.9月5日中午内推,当天下午就收到电面,当时还是感觉很惊喜的,没想到反应这么快;然后约了9月17日的电面,
 * 电面是国人小哥,人很好,题也不难,顺利的解决了.次日收到约Onsite的邮件.

吐槽完了,接下来是面试体验+面经.
以下内容需要积分高于 180 您已经可以浏览

提前一天飞抵NYC,入住酒店,当天没有活动,第二天早上直接去面试.NYC的office在曼哈顿的核心区域,离时间广场五分钟步行距离.uber大概占了
 一栋楼的一整层,听说最近正准备买（租?)下另一层.之前邮件没有说提供早饭,但其实是可以到了那里喝杯咖啡吃点小零食的.会领你进一个会议室,
 一天的面试就在那里进行.桌上会有张纸告诉你每轮的时间,面试官和focus area,10点开始第一轮.


我的五轮依次是hire manager, coding, bar raiser, problem solving/design, coding

第一轮hire manager,问简历和BQ的.简历的project问的还比较细,BQ我只记得一个了:说一下你的三个优点和三个缺点.

第二轮coding,是个在亚麻工作了3年又来uber工作了两年的国人小哥.出了个number of islands的题,follow up是如果二维数组很大很大,memory
 放不下怎么办?我一开始说的是类似于demand paging,把整个数组划分成内存能容纳下的小区域,遇到不在内存中的就swap一下.后来面试官hint说可以
 假设数组里绝大部分都是0,只有很少数量的island,那我就说只要记录下islands的坐标然后进行traverse就行了.follow up没有写码,我说完想法面
 试官说是对的,就让我问问题了,整整问了20分钟问题,不知道是放我水还是想直接挂我了...

第三轮bar raiser,感觉这轮挂了.一进门就问BQ,不知道是不是bar raiser需要故意这样?然后做题,题目是蠡口二路器,我的思路就是计算每个char
 的数量,其中odd数量的只能有一个而且要在string本身的odd长度下才行,然后如果valid的话就把每个char的数量除以2,用这些char生成所有
 permutation,再每个加上自己的reverse（如果存在odd的char把它放中间),就得到结果了.但有bug改了半天,最后一秒钟才debug出来,面试官说
 你把代码发我邮件我回头再看...

第四轮是problem solving/design,国人面试官.本来以为会是system design的,因为自己毫无基础感觉很慌,没想到并没有问.一开始让实现一个
 数独的validator,很快写完了,然后有问如果这个validator是一个大project里的一部分,或者说是一个class的一部分,你会增加些什么?这就让我
 很懵了,说了一些乱七八糟的也没说对.

 然后就问了第二题,是设计一个数据结构,能够实现word insert和word search.我一想那不就是Trie吗?然
 后就写了个Trie给她.word search的代码她一开始觉得有问题,口头跑了个case才说服了她.之后就是问答时间了.

 sherry0419 发表于 2018-11-10 10:41
实现一个数独的validator那道题面试官最后有没有说要增加什么啊?
没有,我其实一直没搞懂她到底想要我说什么

第五轮是coding,美国人面试官.第一题是蠡口姚柳玲.我没想到two pointer的方法,说了两个,一个是用hashtable记录第一个list的node,另一个
 是traverse第一个list的时候修改list,两个都写了.然后面试官又问如果既不想修改list,又想constant space怎么办?想了半天没想出来,面完以
 后才想到two pointer的做法.
 第二题是best time to buy and sell stock II,就是允许多次买卖的.假装自己想出了最优解,说服了面试官,结果
 他又问假如只允许买卖一次怎么办?我脑子一秀逗,说在多次买卖的方法上找到max profit的那次就行,面试官竟然好像也没发现不对,让我写码,写完跑
 了个case就进入问答时间了.我回家以后才想到这尼玛好像是错的啊...不知道是他真的没发现,还是对我绝望了就不想指出了?
 * */

//https://leetcode.com/problems/intersection-of-two-linked-lists/description/
/*
 *
 * Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
 *
 * */
}

#endif //PNSEI_160_INTERSECTION_OF_TWO_LINKED_LISTS_H
