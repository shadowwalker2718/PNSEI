//
// Created by Henry Wu on 11/7/18.
//

#ifndef PNSEI_166_FRACTION_TO_RECURRING_DECIMAL_H
#define PNSEI_166_FRACTION_TO_RECURRING_DECIMAL_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=428275&highlight=cruise
 * 2017(10-12月) DataEng 硕士 全职@GM Cruise - 网上海投 - 技术电面 Onsite  | Fail | 在职跳槽
去年年底的时候面的,跪了,最近比较有空,跟大家分享一下面经,也希望大家能给我加点米.

我面的是 big data 相关的职位,应该算是 data engineer组,具体是哪个组忘了,面试的时候 manager 跟我她们组主要是收集车上各种 sensor
 的数据,然后做一些 aggregation 提供给其他的组.

电面:就一个题,蠡口 两百,数小岛,题目和原题不一样,但是换汤不换药.面试官妹子一句话也不想多说,code pad 上贴完题目就不说话了,我秒了之
 后跑完Test,她看结果是对的就啥也没说,就结束了,连问题都没让问,整个电面不到二十分钟.然后当天就安排了 onsite.

onsite:一共三轮,主要都是算法,少量 BQ,因为是组里是做 data pipeline 方面,所以不用 c++,我面试写的是 Java 代码,因为用 scala 写面试
 题有点诡异.挂在第一轮了,因为走错了 office,第一轮耽误了很多时间.我没仔细看邮件里面的地址,google 了一下就去了那个大车库的 office,
 check in 之后等了半天,有人过来告诉我我的面试不在这个 office,然后换到另外一个地方耽误了二十多分钟.

1) 蠡口 壹溜溜 ＋ 貳玖综合版, 给两个 int 整数,输出一个 tuple（整数部分,小数部分),如果是循环小数,需要标记循环的位置,具体细节有
 点忘了,要求不能用除法和取模运算,所以需要写一个类似蠡口貳玖的函数来计算两个数的商和余数,记得要用到 hashmap,这轮代码没写完,
 挂在这里了.

2)这轮是 manager 面试,少量 BQ,出了一个题,题目叫做 key value store,其实要求和 LRU一模一样,可以参考蠡口 LRU那个题目,这轮是在电
 脑上写的,一边讨论要求,一边打代码还算比较顺利的写完了,然后问我怎么测试,我写了一些需要测试的 Corner case,然后结束,这轮应该还行.

3) 第三轮是最简单的一轮,题目是 parse 一个树形结构的字符串,然后保存每个单词的parent,类似于解析一段 Python 代码,然后用 hashmap 保
 存每个单词的 parent.写完代码简单聊了聊这轮结束.

时间过去的有点久,题目的具体细节有点忘记了,只能说个大概,请见谅.
 *
 * https://leetcode.com/problems/fraction-to-recurring-decimal/
 *
 * https://leetcode.com/problems/divide-two-integers/
 *
 * Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 2, denominator = 3
Output: "0.(6)"

 *
 * */

#endif //PNSEI_166_FRACTION_TO_RECURRING_DECIMAL_H
