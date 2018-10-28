//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_MULTITHREAD_WEB_CRAWLER_H
#define PNSEI_MULTITHREAD_WEB_CRAWLER_H

/* https://www.1point3acres.com/bbs/thread-361979-1-1.html
 *
 * 第四轮多线程，小哥对我现在做的项目比较感兴趣，简单聊了聊。然后开始web
 * crawler，我问是多线程还是单线程。小哥说好问题，让我说说为什么多线程，单线程慢在哪里，多线程怎么提高速度的。
 * 说完以后让我先从单线程开始实现，给了isInternal(url)和getLinks(url)两个API，让实现crawl(root)方法，返回这个domain下所有的links。
 * 很快实现，然后开始多线程版本。我问小哥能不能直接用Executor
 * Service，小哥表示犹豫，说用Executor的话太简单了，希望我用condition
 * varialble来实现。我说可以，但是我想把线程管理和crawl本身的代码分开，这样decouple以后容易管理代码，结构会比较清晰，所以我还是想用Executor
 * Service，我可以快速实现一个simple executor，小哥表示同意。然后用condition
 * variable实现了一个Blocking Queue，又用Blocking
 * Queue实现了一个Executor，不过没有实现线程池，每次有task进来就直接开一个线程来执行这个task。实现过程中问小哥要不要考虑termination，
 * 小哥说暂时不用考虑。但是其实最终还是要考虑的，不然程序没办法终止，拿不到结果。最后补上了termination
 * condition，同时讨论了一下Java程序终止是main
 * thread结束就终止还是所有thread都退出才终止。
 * 昨晚以后还有10分钟左右，小哥又问了问我正在做的项目，看来真的是挺感兴趣。
 *
 * */

// http://massivetechinterview.blogspot.com/2015/06/design-web-crawler.html

#include "henry.h"

namespace dropbox_concurrency {
using LINK = string;
bool isInternal(string url) { return true; };
vector<LINK> getLinks(string url) { return vector<string>(); };

// BFS
vector<LINK> crawl(const string &root_url) {
  set<LINK> result_set;
  queue<LINK> q; // a queue for all internal URLS
  q.push(root_url);
  while (!q.empty()) {
    int k = q.size();
    while (k--) {
      LINK lnk = q.front();
      q.pop();
      if (result_set.count(lnk) == 0) {
        result_set.insert(lnk);
        vector<LINK> new_links = getLinks(lnk);
        for (const LINK &e : new_links) {
          if (isInternal(e))
            q.push(e);
        }
      }
    }
  }
  return vector<LINK>(result_set.begin(), result_set.end());
}

class BBQ {
  mutex mu;
  condition_variable cv;
  queue<LINK> q;
  int cap;

public:
  BBQ(int x) : cap(x) {}
  void push(LINK &s) {
    unique_lock<mutex> ul;
    while (q.size() == cap) {
      cv.wait(ul);
    }
    q.push(s);
    if (q.size() == 1)
      cv.notify_one();
  }
  LINK pop() {
    unique_lock<mutex> ul;
    while (q.size() == 0) {
      cv.wait(ul);
    }
    LINK r = q.front();
    q.pop();
    if (q.size() == cap - 1)
      cv.notify_one();
    return r;
  }
};

BBQ global_queue(1024);
vector<LINK> crawl_multithread(const string &lnk) {}

} // namespace dropbox_concurrency

#endif // PNSEI_MULTITHREAD_WEB_CRAWLER_H
