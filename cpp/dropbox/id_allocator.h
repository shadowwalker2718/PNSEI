//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_ID_ALLOCATOR_H
#define PNSEI_ID_ALLOCATOR_H

/*
 * https://www.bfilipek.com/2017/08/cpp17-details-filesystem.html

 * 第一轮算法，alloc id. HashTable + Queue 写了一个简单实现，然后分析这个解法哪里不好，计算了一下memory usage。然后说可以用BitSet来记录每个Id的使用情况，这样可以把内存使用降低到1/32。 简单聊了一下BitSet的实现原理，分析了时间复杂度是O(n)。没有实现，然后继续讨论了优化可可能性，给出了Segment Tree的解法。面试官说suppose给你的max capacity永远是2的N次，帮我降低实现难度，让我实现了一下。中间出了点小bug，被面试官发现了，很快修正了。做完以后还有10分钟左右，面试官问有没有一个解法可以做到O constant的复杂度，不是O(1)。 想了一会儿没想出来，只想到了从HashMap的角度出发，时间不多了就结束了，最后面试官简单说了一下思路，没太搞明白，但是确实是HashMap的方向。*/

#endif //PNSEI_ID_ALLOCATOR_H
