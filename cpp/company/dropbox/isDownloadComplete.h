//
// Created by Henry Wu on 11/21/18.
//

#ifndef PNSEI_ISDOWNLOADCOMPLETE_H
#define PNSEI_ISDOWNLOADCOMPLETE_H

#include "pnsei.h"

namespace _dropbox_isDownloadComplete {

/* https://1point3acres.com/bbs/thread-456257-1-1.html
 *
 * 2019(10-12月) 码农类General 硕士 全职@Dropbox - 校园招聘会 - Onsite  | Other | fresh grad应届毕业生
昨天刚面的dropbox onsite,今天来发个帖子希望可以帮到大家,楼主是新人,求大米...
10-11第一轮:在一个很大的file里找一个str,第一个考点在于file很大不能一下子读进内存,所以需要自己写一个nextByte()来一个byte一个byte的
 读.第二个考点在于优化时间复杂度,用rolling hash可以把时间复杂度从O(NK)优化到O(N),N是file的长度,K是str的长度,面试官没有让我
 实现rolling hash（可能是因为我时间不够了)

11-12第二轮:首先是实现isDownloadComplete(chunks, filesize),chunks表示已经下载好的区间,filesize表示文件大小.比如
 chunks=[[0,3],[5,8]], filesize=8, 那么isDownloadComplete应该返回FALSE.这里楼主用了排序chunks然后一个个merge的方法,
 时间复杂度是O(logN). /// Should be O(NLogN)
 写完以后followup:chunk是一个一个进来的,所以要实现一个class,支持addChunk(chunk)和isComplete()
 两个API,楼主当时想法是在class里维持一个sorted的chunks,在addChunk里用python bisect来做binary search然后进行merge,
 这样的话时间复杂度应该是O(logN).但是面试官一直想要引导我用heap来做,楼主无法理解为什么要用heap,为此浪费了十多分钟,导致
 我最后代码没写完....

12-1午饭: 一个刚入职几个月的小姐姐来带着吃饭,不知道吃午饭算不算面试?楼主当时没有太在意,跟小姐姐聊天的时候开了几次小差,因为脑
 子里还在想上午没面好的题目...
1-2 demo:介绍一些dropbox产品

2-3第三轮:allocate id,三种做法:1) set 2)bit array 3)segment tree,每种做法都要分析时间和空间复杂度.前两种面试官只让我
 说了思路,然后直接实现第三种.

3-4第四轮:多线程web crawl,是一个白人小姐姐面的.楼主之前没写过多线程,所以这一轮就是面试官手把手教我多线程了...楼主已经
 无法记得完整的逻辑,只记得需要用到condition variable, thread pool, notify_all, wait等操作


总结:dropbox每道题都会有很多followup,楼主答题速度太慢,好几轮都有点没面完的感觉,所以建议大家面试的时候注意时间,加快节奏,争
 取多答点followup的话feedback应该会比较好

最后,求大米....
 * */

// http://sde.quant365.com/math-probability.html#coupon-collectors-problem
// http://sde.quant365.com/linkedin-before-2015.html#gettotalcoveredlength
// http://sde.quant365.com/array.html#insert-interval
// https://www.geeksforgeeks.org/merging-intervals/

bool isDownloadComplete(vector<pair<int, int>> chunks, size_t filesize) {
  priority_queue<PII> pq(chunks.begin(), chunks.end()); // min heap O(N)
  auto prev = pq.top();
  pq.pop();
  int z = prev.second - prev.first;
  while (!pq.empty()) { // O(NLogN)
    auto cur = pq.top();
    z += cur.second - cur.first;
    if (prev.second < cur.first) return false;
    pq.pop();
    prev = cur;
  }
  return z == filesize;
}

class Downloader{
  list<PII> chunks;
  size_t filesize;
  size_t z=0;
public:
  Downloader(size_t fz):filesize(fz){}

  void add_merge_chunk(PII& c){ // O(N)
    bool inserted=false;
    auto it=chunks.begin();
    while(it!=chunks.end()){
      if(c.second < it->first){ // NNNN [it]
        if(!inserted){
          chunks.insert(it, c); // insert before it
          z+=c.second-c.first;
          inserted=true;
          break;
        }
      }else if(c.first > it->second){ // [it] NNNNN

      }else{
        c={min(c.first, it->first), max(c.second, it->second)};
        z-=(it->second - it->first), it=chunks.erase(it);
        continue;
      }
      ++it;
    }
    if(!inserted)
      chunks.push_back(c), z+=c.second-c.first, inserted=true;
  }
  bool isDownloadComplete(){
    return z==filesize;
  }
};


struct Intervals { // bool - 起始点或者终止点
    vector<pair<int, bool>> intervals;//interval data structure
    void addInterval(int from, int to) { // O(1)
      intervals.emplace_back(from, 1);
      intervals.emplace_back(to, 0);
    }
    int getTotalCoveredLength() { // O(NLogN) - N is number of intervals added
      sort(intervals.begin(), intervals.end());
      int r = 0, count = 0;
      stack<int> stk; // max size are 2
      for (int i = 0; i < intervals.size(); i++) {
        if (stk.empty()) {
          stk.push(intervals[i].first);
        }
        if (intervals[i].second)
          count++;
        else
          count--;
        if (count == 0) { // we have found a `continuously covered range`
          r += intervals[i].first - stk.top();
          stk.pop();
        }
      }
      return r;
    }
};

};

#endif //PNSEI_ISDOWNLOADCOMPLETE_H
