//
// Created by henry on 10/21/18.
//

#ifndef C_LRU_H
#define C_LRU_H

#include "henry.h"
/*
 *
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=448226&ctid=228575
地里找人帮忙内推了一下Infra方向, 形式是 Video Interview,
面试官是个白人小姐姐.地里可参考的面经比较少.自我介绍后题目就是LRU,只不过加了个delete
function. 打开coderpad要用python写,问可不可以java,同意后就用java写了.
先写了每个function的思路,确认后写code,最后一个delete functionc没来得及写code.
然后问了一下如果这个用于多线程会有什么问题.
最后例行问问题.求大米呀求大米!!!*/

// Multithreaded LRU

// https://www.ebayinc.com/stories/blogs/tech/high-throughput-thread-safe-lru-caching/
// https://www.codeproject.com/Articles/23396/A-High-Performance-Multi-Threaded-LRU-Cache
// https://github.com/tstarling/thread-safe-lru
// https://github.com/mohaps/lrucache
// https://github.com/mohaps/lrucache11

// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=402851&ctid=228575
/*
 * koga 发表于 2018-9-12 00:49
请问LRU, follow up templated version 是什么意思

就是存的node value不一定是int,是T怎么写,需要自定义hash function.
 *
 *
 * 2018(7-9月) 码农类General 硕士 全职@Cruise - 猎头 - Onsite  | Other | 在职跳槽
1点开始4点半结束,4个面试官,连饭好不好吃都不给体验一下的...productivitiy 组. 一亩-三分-地,独家发布
1.聊了挺久现在在做啥,然后上个design问题,因为面试官的是productivity组里的搭测试framework的,所以就问我要怎么样搭个给他们跑测试的环境
 ,刚好和我现在工作的framework沾边,所以可以扯挺多.他们每个test都需要跑很长时间,而且test data也很大,要怎样优化这些.
 讲一些scalability的东东,跟面试官聊的挺不错的感觉
2.manager聊天,了解这个组的情况,没什么behavior问题就问问你做什么,对cruise想法怎样.
3.白板,基本上可以算是golang问题...如果你有好几个ordered stream（channel),如何合成一个ordered stream,写完后面试官说我的答案
 没用最优的golang pattern,中间还得问面试官golang的channel syntax,嘤嘤嘤,如果我挂了肯定是因为这个!.
4.  两人坐下来面对面写coderpad...不用自己带电脑,他们提供个chromebook.题目是LRU cache,笔者刷题不精,没刷过这个经典题,不过算是从
 头导出了Queue + hashmap的解法...好处就是不用装没刷过（emmm)

今早recruiter发邮件说明天约电话时间,看了地里面筋,如果拒就是模版据信,所以应该是有戏?地点在SF的costco旁边,离地铁有点远就是了.
 *
 * */

namespace cruise_20181009 {

// Actually an ordered hashmap ordered by insertion/access time
class LRUCache {
  list<pair<int, int>> ls;
  map<int, list<pair<int, int>>::iterator> m;
  int cnt;

public:
  LRUCache(int capacity) : cnt(capacity) {}

  int get(int key) {
    if (!m.count(key))
      return -1;
    int r = m[key]->second;
    if (m[key] != ls.begin()) {
      ls.splice(ls.begin(), ls, m[key], next(m[key])); // move to front
      m[key] = ls.begin();
    }
    return r;
  }

  void put(int key, int value) {
    if (m.count(key)) {
      if (m[key] != ls.begin()) {
        ls.splice(ls.begin(), ls, m[key], next(m[key]));
        m[key] = ls.begin();
      }
      ls.begin()->second = value; // dont forget this
      return;
    }
    if (cnt == ls.size()) {
      m.erase(ls.back().first); // the reason why we need list<Key,Value>
                                // instead of list<Value>
      ls.pop_back();
    }
    ls.emplace_front(key, value);
    m[key] = ls.begin();
  }

  void del(int key) {
    if (m.count(key)) {
      ls.erase(m[key]);
      m.erase(key);
    }
  }
};


// https://www.openmymind.net/High-Concurrency-LRU-Caching/
// https://github.com/karlseguin/ccache
// https://www.ebayinc.com/stories/blogs/tech/high-throughput-thread-safe-lru-caching/
// https://www.openmymind.net/Shard-Your-Hash-table-to-reduce-write-locks/
template <typename KT, typename VT>
class distributedLRU{
  int cap;
public:
  distributedLRU(int capacity) : cap(capacity) {}
  void del(const KT&);
};

template<typename KT, typename VT>
void distributedLRU<KT, VT>::del(const KT& key) {

}

} // namespace cruise_20181009
#endif // C_LRU_H
