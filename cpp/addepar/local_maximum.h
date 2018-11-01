//
// Created by root on 10/31/18.
//

#ifndef PNSEI_LOCAL_MAXIMUM_H
#define PNSEI_LOCAL_MAXIMUM_H

/*
 *  https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=227852&highlight=Addepar
2016(10-12月) 码农类General 博士 全职@Addepar - Other - 校园招聘会  | Fail | fresh grad应届毕业生
要提前毕业各种忙，趁有点空闲，继续贡献个早前的onsite，个人感觉非常promissing的fintech startup，叫addepar。主要做金融大数据分析，目
 标群体是高净值人群，founder是palantir的co-founder。继承了palantir，addepar的逼格也是极高，参加了他们的座谈会，号称招聘通过率是1%，
 only hire the best of best （onsite下来感觉不算吹牛，面试官还有几个一起吃饭的engineer要么牛校毕业，要么flg工作好几年跳过来的）。然
 后产品的确很cool，帮高净值财富人群提供资产分析（听完他们技术分享，感觉亿万富豪们的财富管理的确很复杂的事情，有时候自己多少钱都不知道，哪
 像我们这普通人，就没有这种烦恼），可视化是亮点。

第一面，韩裔/亚裔ABC小哥？。返回二叉树任意一个local maximal的节点（就是节点的值要比儿子节点和父节点都要大），一开始说遍历一遍。
 followup说复杂度降到O(lgn)。follow-up，1d array的local maximal，再接着2d array的local maximal,都要log级别复杂度。

第二面，感觉国人小哥，给个sorting array，返回平衡二叉树。sorting list？。follow-up，sorting list 复杂度降到O(n)  。。
第
 三面，感觉也是个屌屌的国人小哥（说facebook跳过来），给了个需求，要写线段树。那时候没刷多少题。。写出来后小哥说有bug。。。好吧。。
第四面，白人年轻小哥（说berkerly毕业？）。。给了需求（具体记得不是很清楚了，glassdoor上有这题），一开始你有比如Goog 200， Apple 100股
 票，然后每天你/基金公司会进行操作，比如sell goog 200, buy Amazon200，然后银行最终给出当天你最后拥有多少每个公司的股票。你的代码判断对
 不对 （可能还有些其他需求？记不大清）。
第五面，白人中年小叔（说linkined 5年跳过来），给了一个很大python程序，一跑起来就崩掉了。。让debug。我说我不懂python，他说他其实做前端
 的，他也不懂。。大家一起来慢慢找bug。。在他各种给提示不断找。。。终于找到。。。

结果当然是挂了，那时候实习忙也没刷几题，倒是很开心有个逼格很高的公司给自己开始面试热身的机会（1%通过率是真的话，现在让我去面估计还是挂），
 所以看得很开就是。。然后感觉他们家的工程师的质量的确非常高，followup都问的很细。。复杂度不断优化。不想有些公司engineer可能题库里临时
 看了个标准答案就来面试那种。。有几个follow-up后来想出来，然后偶尔在别的面试又遇到，说我遇过这题，然后有个优化，那个公司engineer愣是没
 有听懂。。。。。。
anyway这次经历也当做给大家多分享几个不错的公司咯。。
 *
 * */

namespace addepar_onsite{

    /*
     * https://stackoverflow.com/questions/15656871/finding-a-local-minimum-in-a-binary-tree
     * https://algorithms.tutorialhorizon.com/find-local-minimum-or-local-maximum-in-o1/
     * https://www.geeksforgeeks.org/find-local-minima-array/
     * https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
     * https://www.geeksforgeeks.org/find-peak-element-2d-array/
     * https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/MIT6_006F11_lec01.pdf
     * */
}

#endif //PNSEI_LOCAL_MAXIMUM_H
