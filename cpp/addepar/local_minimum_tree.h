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

/*11.15号面的第一轮:
        第一题：有n个数，需要比几次才能选出最大值，n-1，然后怎么证明……证明…………证……怎么跟高数一样，这还需要证？这还能这么证……
第二题：矩阵给定起点和终点找最短路径，BFS

        刚刚结束的第二轮：
第一题：二叉树里面找local max，第一遍用BFS，第二遍用了二分，第三遍减少比较次数…………
*/
#include "utils/binarytree.h"

namespace _addepar{

    /*
     * https://stackoverflow.com/questions/15656871/finding-a-local-minimum-in-a-binary-tree
     * https://algorithms.tutorialhorizon.com/find-local-minimum-or-local-maximum-in-o1/
     * https://www.geeksforgeeks.org/find-local-minima-array/
     * https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
     * https://www.geeksforgeeks.org/find-peak-element-2d-array/
     * https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/MIT6_006F11_lec01.pdf
     * */


    /*
     By definition, a local min is a node whose value is smaller than that of any other nodes that are joined to it.
     Thus in your example, '1', '5', '6', '2', '7', '13' are all local minimums.
     Once that's clear, the problem is simple.
     First we check the root and see if it's smaller than both children. If yes, then we are done. If not, then we pick
     up its smaller child and recursively apply the check.
     We terminate either:
     1) we found a node that is smaller than both of its children, or
     2) we reach the bottom level(i.e. the leaves).
     In case 1), the node at which we stop is the local min, because i) it's smaller than both of its children, and ii)
     it's smaller than its parent, which is the precondition of our deciding to check this node.
     In case 2), we are left with two leaves (that are siblings), and at least one of them is smaller than the parent
     (otherwise the parent will be returned). Then, either (or both) of them are local min, as long as it's smaller
     than its parent.
     Following this approach, at most 2 nodes per level are being looked at, thus requiring only O(log n) checks.*/
    int get_any_local_minimum(treenode *root){
        if(!root) return INT_MAX;
        if(!root->l and !root->r) return root->val;

        if(root->l and root->r){
            if(root->val < root->l->val and root->val < root->r->val )
                return root->val;
            return get_any_local_minimum(root->l->val > root->r->val?
                                         root->r : root->l);
        }
        if(root->l){ // and !root->r
            if (root->val < root->l->val)
                return root->val;
            return get_any_local_minimum(root->l);
        }
        if(root->r) { // and !root->l
            if (root->val < root->r->val)
                return root->val;
            return get_any_local_minimum(root->r);
        }
    }

    void test(){
        vector<int> v={1,2,3,4,5};
        treenode* r1 = build_segment_tree_algo1(v);
        print_binary_tree_horizontal(r1);
        treenode* r2 = createTree2();

        set<int> result={1,5,6,2,7,13};
        assert(result.count(get_any_local_minimum(r2)));

        treenode* r3 = createTree3();
    }

}

#endif //PNSEI_LOCAL_MAXIMUM_H
