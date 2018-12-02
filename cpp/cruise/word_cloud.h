//
// Created by Henry Wu on 11/6/18.
//

#ifndef PNSEI_WORD_CLOUD_H
#define PNSEI_WORD_CLOUD_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=444345&highlight=cruise
 * 2018(7-9月) 码农类General 硕士 全职@Cruise - 猎头 - 技术电面  | Fail | 在职跳槽
刚面完,印度小哥迟到了,花了15分钟相互介绍,问了写过什么数据库的Service, 问了如何实现.然后 剩下 45 开始 Coding:


写一个生成 词云  的 function,输入 一个 URL (URL 是一个Gist,里面有需要处理的公司名称文本),
 保留的最频繁词的数量K, 和可取的词的最小长度 L. 返回一个JSON 字符串.
.
[
["管理", 2301],
["资本", 1617],
["投资", 867],
]
.

反馈:
想出解决方案的速度很快（+),
设计的也很模块化（+)
调试能力也还不错（+)
没有用org.json.simple.JSONObject 来生成结果 ,所以结果容易出错,而且会在后续问题中产生更加多的工作量（-)
时刻留意还有多少时间（+)
但是没有早点写完,所以没有来得及讨论followup questions (-)
面完 5分钟 跪了
 *
 *
 *
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=452669&highlight=cruise
2018(10-12月) 码农类General 硕士 全职@Cruise - 内推 - 技术电面  | Fail | fresh grad应届毕业生
报一个Cruise店面 跪经

地里大佬帮我内推,一直在看dfs,没有想到考地里出现过的的那个词云,目标是github的issue comment,没想到真的考这个..
问了20分钟简历,通话还断了好几次
问题的本质就是就top出现的元素,但是要发http request得到response和然后parse json,小哥的要求是能在他那个编译器里运行..
top k word 地里的人都会写, bug free发request 接受response,得到string,然后parse json确实有点不好弄啊,它还给
了GitHub RESTful API的教程和样例,让我现场学..

最后就给他写了个top k的算法..其实熟悉request和response还有Java的json parser写起来还是很快的,但是真的不记得了..
感觉小哥期望我是运行出结果的,重点应该不是考算法



noelzhao 发表于 2018-10-28 09:30
请问楼主地里出现的词云的链接

估计它随便找的吧
关键得是现场学他提供的API,
你搜一下GitHub的developer API
 * */

#endif //PNSEI_WORD_CLOUD_H
