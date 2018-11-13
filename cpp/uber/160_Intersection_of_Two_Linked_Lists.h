//
// Created by root on 11/12/18.
//

#ifndef PNSEI_160_INTERSECTION_OF_TWO_LINKED_LISTS_H
#define PNSEI_160_INTERSECTION_OF_TWO_LINKED_LISTS_H

#include "henry.h"

namespace _160{

/*
 * Uber的整个招聘过程也是很需要耐心。9月5日中午内推，当天下午就收到电面，当时还是感觉很惊喜的，没想到反应这么快；然后约了9月17日的电面，
 * 电面是国人小哥，人很好，题也不难，顺利的解决了。次日收到约Onsite的邮件。

但是从此开始就陷入了漫长的等待中……发了availability给HR后一直没有收到回复，等了一周等不及了就发邮件催，还是没回复。因为给availability
 的时候没想到会等这么久，一次给了前后跨度一个月的，然后有好几个时间陆陆续续被其他公司的onsite给占掉了，我又得发邮件给HR更新（这点确实是
 我不好不应该三番五次改动，但我真的没想到要等那么久。。。），但是更新的邮件也从未收到回复；后面联系了内推人问情况，但也没什么好办法，就只
 能保持一周一次的频率催着。终于终于，在接近一个月后的10月15日，HR回了一封邮件把日期定下了。。。真的是唯一一家约onsite约了一个月的公司。

然而这还没完，定下了onsite日期后，有过了半个月才有coordinator联系告诉了地点和时间，这时候才知道是NYC的office，还挺意外的。然后由pana
 来负责订机票和酒店。然而pana那边又是一遍百般催促，它先要向uber那边approve budget，然后又发现机票超预算了，要再次请示budget，最后周
 五的面试，周四的航班终于在周二给我订好了票，周三订好了酒店。。。拖这么晚uber真是不心疼钱啊。。。



吐槽完了，接下来是面试体验+面经。
以下内容需要积分高于 180 您已经可以浏览

提前一天飞抵NYC，入住酒店，当天没有活动，第二天早上直接去面试。NYC的office在曼哈顿的核心区域，离时间广场五分钟步行距离。Uber大概占了
 一栋楼的一整层，听说最近正准备买（租？）下另一层。之前邮件没有说提供早饭，但其实是可以到了那里喝杯咖啡吃点小零食的。会领你进一个会议室，
 一天的面试就在那里进行。桌上会有张纸告诉你每轮的时间，面试官和focus area，10点开始第一轮。


我的五轮依次是hire manager, coding, bar raiser, problem solving/design, coding

第一轮hire manager，问简历和BQ的。简历的project问的还比较细，BQ我只记得一个了：说一下你的三个优点和三个缺点。

第二轮coding，是个在亚麻工作了3年又来uber工作了两年的国人小哥。出了个number of islands的题，follow up是如果二维数组很大很大，memory
 放不下怎么办？我一开始说的是类似于demand paging，把整个数组划分成内存能容纳下的小区域，遇到不在内存中的就swap一下。后来面试官hint说可以
 假设数组里绝大部分都是0，只有很少数量的island，那我就说只要记录下islands的坐标然后进行traverse就行了。follow up没有写码，我说完想法面
 试官说是对的，就让我问问题了，整整问了20分钟问题，不知道是放我水还是想直接挂我了。。。

第三轮bar raiser，感觉这轮挂了。一进门就问BQ，不知道是不是bar raiser需要故意这样？然后做题，题目是蠡口二路器，我的思路就是计算每个char
 的数量，其中odd数量的只能有一个而且要在string本身的odd长度下才行，然后如果valid的话就把每个char的数量除以2，用这些char生成所有
 permutation，再每个加上自己的reverse（如果存在odd的char把它放中间），就得到结果了。但有bug改了半天，最后一秒钟才debug出来，面试官说
 你把代码发我邮件我回头再看。。。

第四轮是problem solving/design，国人面试官。本来以为会是system design的，因为自己毫无基础感觉很慌，没想到并没有问。一开始让实现一个
 数独的validator，很快写完了，然后有问如果这个validator是一个大project里的一部分，或者说是一个class的一部分，你会增加些什么？这就让我
 很懵了，说了一些乱七八糟的也没说对。

 然后就问了第二题，是设计一个数据结构，能够实现word insert和word search。我一想那不就是Trie吗？然
 后就写了个Trie给她。word search的代码她一开始觉得有问题，口头跑了个case才说服了她。之后就是问答时间了。

 sherry0419 发表于 2018-11-10 10:41
实现一个数独的validator那道题面试官最后有没有说要增加什么啊？
没有，我其实一直没搞懂她到底想要我说什么

第五轮是coding，美国人面试官。第一题是蠡口姚柳玲。我没想到two pointer的方法，说了两个，一个是用hashtable记录第一个list的node，另一个
 是traverse第一个list的时候修改list，两个都写了。然后面试官又问如果既不想修改list，又想constant space怎么办？想了半天没想出来，面完以
 后才想到two pointer的做法。
 第二题是best time to buy and sell stock II，就是允许多次买卖的。假装自己想出了最优解，说服了面试官，结果
 他又问假如只允许买卖一次怎么办？我脑子一秀逗，说在多次买卖的方法上找到max profit的那次就行，面试官竟然好像也没发现不对，让我写码，写完跑
 了个case就进入问答时间了。我回家以后才想到这尼玛好像是错的啊。。。不知道是他真的没发现，还是对我绝望了就不想指出了？
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
