//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_MULTITHREAD_WEB_CRAWLER_H
#define PNSEI_MULTITHREAD_WEB_CRAWLER_H

/*
 *
 * 第四轮多线程，小哥对我现在做的项目比较感兴趣，简单聊了聊。然后开始web crawler，我问是多线程还是单线程。小哥说好问题，让我说说为什么多线程，单线程慢在哪里，多线程怎么提高速度的。说完以后让我先从单线程开始实现，给了isInternal(url)和getLinks(url)两个API，让实现crawl(root)方法，返回这个domain下所有的links。 很快实现，然后开始多线程版本。我问小哥能不能直接用Executor Service，小哥表示犹豫，说用Executor的话太简单了，希望我用condition varialble来实现。我说可以，但是我想把线程管理和crawl本身的代码分开，这样decouple以后容易管理代码，结构会比较清晰，所以我还是想用Executor Service，我可以快速实现一个simple executor，小哥表示同意。然后用condition variable实现了一个Blocking Queue，又用Blocking Queue实现了一个Executor，不过没有实现线程池，每次有task进来就直接开一个线程来执行这个task。实现过程中问小哥要不要考虑termination，小哥说暂时不用考虑。但是其实最终还是要考虑的，不然程序没办法终止，拿不到结果。最后补上了termination condition，同时讨论了一下Java程序终止是main thread结束就终止还是所有thread都退出才终止。 昨晚以后还有10分钟左右，小哥又问了问我正在做的项目，看来真的是挺感兴趣。
 *
 * */

#endif //PNSEI_MULTITHREAD_WEB_CRAWLER_H
