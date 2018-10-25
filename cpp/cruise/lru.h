//
// Created by henry on 10/21/18.
//

#ifndef C_LRU_H
#define C_LRU_H

#include "henry.h"
/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=448226&ctid=228575
地里找人帮忙内推了一下Infra方向, 形式是 Video Interview, 面试官是个白人小姐姐。地里可参考的面经比较少。自我介绍后题目就是LRU，只不过加了个delete function. 打开coderpad要用python写，问可不可以java，同意后就用java写了。
先写了每个function的思路，确认后写code，最后一个delete functionc没来得及写code。
然后问了一下如果这个用于多线程会有什么问题。
最后例行问问题。求大米呀求大米！！！*/

// Multithreaded LRU

// https://www.ebayinc.com/stories/blogs/tech/high-throughput-thread-safe-lru-caching/
// https://www.codeproject.com/Articles/23396/A-High-Performance-Multi-Threaded-LRU-Cache
// https://github.com/tstarling/thread-safe-lru
// https://github.com/mohaps/lrucache
// https://github.com/mohaps/lrucache11


// https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=402851&ctid=228575
/*
 * koga 发表于 2018-9-12 00:49
请问LRU， follow up templated version 是什么意思

就是存的node value不一定是int,是T怎么写，需要自定义hash function。
 * */

namespace cruise_20181009{

  class LRUCache {
    list<pair<int,int>> ls;
    map<int, list<pair<int,int>>::iterator> m;
    int cnt;
  public:
    LRUCache(int capacity) : cnt(capacity){}

    int get(int key) {
      if(!m.count(key)) return -1;
      int r=m[key]->second;
      if(m[key]!=ls.begin()){
        ls.splice(ls.begin(), ls, m[key], next(m[key]));
        m[key]=ls.begin();
      }
      return r;
    }

    void put(int key, int value) {
      if(m.count(key)){
        if(m[key]!=ls.begin()){
          ls.splice(ls.begin(), ls, m[key], next(m[key]));
          m[key]=ls.begin();
        }
        ls.begin()->second = value; // dont forget this
        return;
      }
      if(cnt==ls.size()){
        m.erase(ls.back().first); // the reason why we need list<Key,Value> instead of list<Value>
        ls.pop_back();
      }
      ls.emplace_front(key,value);
      m[key]=ls.begin();
    }

    void del(int key){
      if(m.count(key)){
        ls.erase(m[key]);
        m.erase(key);
      }
    }
  };


}
#endif //C_LRU_H
