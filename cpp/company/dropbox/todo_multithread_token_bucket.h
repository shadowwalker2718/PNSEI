//
// Created by Henry Wu on 11/27/18.
//

#ifndef PNSEI_TODO_MULTITHREAD_TOKEN_BUCKET_H
#define PNSEI_TODO_MULTITHREAD_TOKEN_BUCKET_H

/*
 * http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=277537

>2017(1-3月) 码农类 硕士 全职Dropbox - 猎头 - Onsite |Fail在职跳槽
1. 多线程tokenbucket, 实现gettoken(int n), token不够就block. 我用的pthread_cond_timedwait, 但是要注意sleep 的时间不保证是准确的, 所以需要while loop sleep .
2. 多线程爬虫带终止条件,秒了, 附代码(crtl+A显示代码), 另外要估算线程数量(based on IO_TIME/CPU_TIME)
```
pthread_mutex_t lock;
pthread_cond_t cond;
queue<string> seeds;
unordered_set<string> visited;
int nwait = 0;
int nthreads = N;
crawl() {
        while(1) {
                pthread_mutex_lock(&lock);
                while(seeds.empty()){
                        nwait++:
                        if(nwait==N) {
                                pthread_cond_signal(&cond);
                                pthread_mutex_unlock(&lock);
                                return;
                        }. from: 1point3acres.com/bbs.
                        pthread_cond_wait(&cond, &lock);
                        nwait—;
                }
                string url = seeds.front();
                seeds.pop();
                pthread_mutex_unlock(&lock);
                vector<string> urls = geturls(url);
                pthread_mutex_lock(&lock);
                for(auto &a:urls) {
                        if(visited.count(a)) continue;
                         visited.insert(a);
                        seeds.push(a);
                }
                if(!seeds.empty()) pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&lock);
        }
}
```
>3. behaviour, failed project etc
4. dive deep
5. 设计twitter, 从single box 扩展.post_tweet, read_tweet, get_news_feed. 怎么实现scroll up/down 更新feed(存上次更新的timestamp)
祝大家好运.另求bless余下的面试有好结果
 * */

#endif //PNSEI_TODO_MULTITHREAD_TOKEN_BUCKET_H
