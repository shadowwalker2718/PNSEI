//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_ID_ALLOCATOR_H
#define PNSEI_ID_ALLOCATOR_H

/*
 * https://www.1point3acres.com/bbs/thread-361979-1-1.html

 * 第一轮算法，alloc id. HashTable + Queue
 写了一个简单实现，然后分析这个解法哪里不好，计算了一下memory
 usage。然后说可以用BitSet来记录每个Id的使用情况，这样可以把内存使用降低到1/32。
 简单聊了一下BitSet的实现原理，分析了时间复杂度是O(n)。没有实现，然后继续讨论了优化可可能性，给出了Segment
 Tree的解法。面试官说suppose给你的max
 capacity永远是2的N次，帮我降低实现难度，让我实现了一下。中间出了点小bug，被面试官发现了，很快修正了。做完以后还有10分钟左右，面试官问有没有一个解法可以做到O
 constant的复杂度，不是O(1)。
 想了一会儿没想出来，只想到了从HashMap的角度出发，时间不多了就结束了，最后面试官简单说了一下思路，没太搞明白，但是确实是HashMap的方向。


alloc id 我onsite也遇到了， 最后的最优解法 是建立一个2n个bit的 segment tree 然后o（lg n）的复杂度完成所有操作
 */

/*
 * 编程题就一道,给一个数N,生成N个id, 用户可以调用allocate()来分配一个id, 用完后调用release()释放id, 这样别的用户可以用. 一开始给了基于bit的解法,但allocate的复杂度是O(N), 要求改进,并提示memory不是问题. 最后的方法是基于hash的.所有的id生成后放到hash table里,然后从里面取

Dropbox 真是万年题不变啊。 当时我用Tree, 刚好是space有要求

嗯，挺开放的题目，可难可易，取决于那一位面试官的考点在哪儿了

http://www.1point3acres.com/bbs/thread-194896-1-1.html

实现两个函数,int allocate()和void release(intid),每调用一次allocate返回的id需要unique,为1到N之间的一个整数.如果release以后,就可以继续被allocate.之前用array+hashmap,达到O(1)时间和O(N)空间.后来被告知空间用得太多,map空间效率低,最后用了bitmap.这题其实和实现文件系统的metadata区域比较类似,不过最后居然是用时间换空间,有点让我诧异.

https://blog.csdn.net/whuwangyi/article/details/43112895

http://massivealgorithms.blogspot.com/2016/08/leetcode-379-design-phone-directory.html

Related OJ:
https://leetcode.com/problems/design-phone-directory/



 * */

#endif // PNSEI_ID_ALLOCATOR_H
