//
// Created by henry on 10/27/18.
//

#ifndef PNSEI_KEY_VALUE_STORE_H
#define PNSEI_KEY_VALUE_STORE_H

/* https://www.1point3acres.com/bbs/thread-303414-1-1.html
 * 2017(10-12月) 码农类General 博士 全职@Dropbox - 猎头 - Onsite  | Fail |
在职跳槽 电话面试忘记了

onsite
1,web crawler,多线程.condition
variable的应用.注意何时return,可以设一个全局变量记录正在等待的thread,如果到达N了说明大家都在
 等,然后就返回.另外,main thread可以通过semaphore来等待多个thread.
2,设计一个单线程支持多个txn的key
value系统,其实就是多维护几个dictionary,不要被题目吓着了.
3,设计twitter,注意如何设计db的schema,如果设计的好,那server可以stateless,server本身不需要用consistent
hash来组织. 可以考虑twit id
是timestamp+userID+rand()或者userID+timestamp+rand(),hbase的key是sorted的.
4,bq,如何make deciscion,没有答好.
5,project deep dive
6,ask them question
最后4-6都没有答好,当时脑抽了问了不止一个面试官他们如何盈利的,估计面试官一脸黑线,你如果对我这么不了解来面个啥.
丢盒子的食堂确实不错,湾区第一for sure.
 * */

#endif // PNSEI_KEY_VALUE_STORE_H
