//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_MULTITHREAD_WEB_CRAWLER_H
#define PNSEI_MULTITHREAD_WEB_CRAWLER_H

/* https://www.1point3acres.com/bbs/thread-361979-1-1.html
 *
 * 第四轮多线程,小哥对我现在做的项目比较感兴趣,简单聊了聊.然后开始web
 * crawler,我问是多线程还是单线程.小哥说好问题,让我说说为什么多线程,单线程慢在哪里,多线程怎么提高速度的.
 * 说完以后让我先从单线程开始实现,给了isInternal(url)和getLinks(url)两个API,让实现crawl(root)方法,返回这个domain下所有的links.
 * 很快实现,然后开始多线程版本.我问小哥能不能直接用Executor
 * Service,小哥表示犹豫,说用Executor的话太简单了,希望我用condition
 * varialble来实现.我说可以,但是我想把线程管理和crawl本身的代码分开,这样decouple以后容易管理代码,结构会比较清晰,所以我还是想用Executor
 * Service,我可以快速实现一个simple executor,小哥表示同意.然后用condition
 * variable实现了一个Blocking Queue,又用Blocking
 * Queue实现了一个Executor,不过没有实现线程池,每次有task进来就直接开一个线程来执行这个task.实现过程中问小哥要不要考虑termination,
 * 小哥说暂时不用考虑.但是其实最终还是要考虑的,不然程序没办法终止,拿不到结果.最后补上了termination
 * condition,同时讨论了一下Java程序终止是main
 * thread结束就终止还是所有thread都退出才终止.
 * 昨晚以后还有10分钟左右,小哥又问了问我正在做的项目,看来真的是挺感兴趣.
 *
 *
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=459243
 * 2018(10-12月)-[]CS本科+<3个月短暂实习/全职 - 内推| 码农类General实习@Dropbox其他
上周五 onsite 发一下面经 攒个人品第一轮 国人小哥问的 isdownloadcomplete的问题 和地里的基本一摸一样
第二轮 一道给了一个网址 让返回所有这个网址可以访问到的地址 给了一个 getlink的API.
 写的时候忘了考虑重复的link会有cycle的问题
 然后稳bottleneck. 最后问了怎么解决
第三轮 老题duplicate fil 只给了一个根目录 然后让你用提供的几个API来做。其他思路完全一样 follow up也和地里面经一样


 https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=409815&highlight=dropbox

 Q1: FindSharpness Val
---------------------------
The same question but change the way it asks... into water level, land elevation.
But, my interview seems not very familiar with the solution, I need to explain him the dp. and the logics all these things...
the i, j , all these indexing make it hard to understand as well...
I make one logic bug and find out during testing... it is I switch the two nested loop
I made wrong...
for(int i=0; i<m...)
   for(int j=1; j<n; ...)
This is wrong, the outer loop should be the col loop as we move from left to right...

Talk a bit about my proposal on optimised space usage... just store one prev column and use one var called prev...
There is no ask on what if the input is very large etc....

Problem in details:
Let say, I have a water level x;

in the matrix, left to right, find a path that is not get flooded by the water...(means the height/elevation that cell represents should be > x)///
well, in the path, we pick the smallest val, and that smallest val has to be >x...
Then we find the path which give that best value... so we can assue there is always a path if x is not greater or equal to that value...
(same problem as sharpness val then)

No follow up... the space optimised is suggested by me.... 1point3acres

Lunch
Demo

Q2: Find the largest island...
-----------------------------------------------
Just leetcode question,
I got one small bug regarding visited marking,... I didn't mark the starting point as visited... find it out during testing and corrected.

Follow up:
1. What if we start with board with all 0... and there is fun can flip the cell (i, j) value;
each time after the function call, return the current largest island...
like leetcode addLand... num of island II

//no need to write exact working code...
//explained Union find ... and
// assumed api for find set... and set set ... etc...
just write a piece of logic..

2. Ask about the running time...-baidu 1point3acres
- I gave some explanation over the worst case of UF, and path compression and weighting etc... saying hard to prove the running time ... it is nlog*n after optimised etc


Q3: Web Crawler
-------------------
First, single thread version...-baidu 1point3acres
Talked a bit about DFS, BFS, stack overflow... endless depth etc problem...
Implemented simple BFS, using result set to do visisted checking as well

Multithreading:
Which part is bottle neck: the getURL part... network latency etc... parser etc
I mentioned Master / slave model, and how it can be achieved using ThreadPool, Callable, and check futures...
and metioned it is even more efficient if we don't do the syn of these queue, set checking logic just let master manage all these... he seems like this...

Then, he asked, in some language/machine, there is no support of threadPool, how would we do it ...
He gave an API... to let you avoid writing some setup code///
setThread(THREAD_COUNT, method)...
implement the method... actually it is the BFS method... but with right locking



There is some back and forth about where to put lock, and
also asked the terminating conditions... (queue is empty and no working thread)
public void crawl() {
        while(true){ //this simplify my code for locking / unlock
                lock.lock();
                if(q.isEmpty() && workingThread<1) {
                        lock.unlock();
                        break;
                }

                //need to use while to guard it
                while(q.isEmpty()) {//queue is empty but cannot terminate yet
                        wait(); //wait will release the lock...
                }
                String currURL = q.poll();
                lock.unlock();

                //you don't want to lock the part that takes most time and that part is not accessing common data
                String newURLGathered = getURL(currURL);

                lock.lock();. 1point3acres
                for(each){
                        add to q & add to result set
                }
                notifyAll(); //in case there is someone waiting due to empty queue.
                lock.unlock();

        }

}
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
