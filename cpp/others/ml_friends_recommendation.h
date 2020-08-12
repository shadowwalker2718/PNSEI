#pragma once
/*

https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=462619&highlight=linkedin

2018(10-12月) MachineLearningEng 博士 全职@Linkedin - 内推 - HR筛选 技术电面
Onsite  | Fail | fresh grad应届毕业生 回馈地里，发送一个最新的L家MLengineer的面经。

背景：LZ物理渣校物理PhD，准备毕业了寻思转行，背景只有PhD期间几个研究勉强能凑得上有用ML（比如简单地KNN这类的）。湾区企业对不同背景的申请者还是非常宽容的，只要有相关project，即使是academic
level也会给个面试。找了个在里头工作的小伙伴内推，一周左右收到HR电话。

第一轮HR面，问了下简历和相关背景，有哪些相关的project啊，各种语言和各种包的熟练程度。半个小时，伶牙俐齿点不难过。

第二轮phone interview。一小时，前半小时问ML的基本知识，比如挑一个你熟悉的ML
algorithm，然后问参数啥意思，适合什么样的数据，是否是linear
classifier，如何train，什么是overfitting，如何防止overfitting。特别细，特别基础，但是不为难人。
认真选1-2个算法准备一下就可以了。后半小时考coding，非常简单，就是find range （binary search原
題，一个sorted array with repeat elements，寻找某个数的range在哪）。用二叉树+递归写写即可。

过了phone interview，再一周就收到onsite的通知。onsite在sunnyvale，一整天，总共6轮，一轮一小时。
考察点非常全面，设置也非常科学的：

1.
第一轮是ML技术面，跟电面很像。从简历挑一个proj开始说，他会问很细，怎么实现，为什么这么实现。
有没有overfitting，你觉得怎么判断又没有overfitting，怎么解决overfitting。你的result是什么，
怎么justify这个result（如何做hypothesis test)。总之问得宽泛基础，需要好好准备

2. 第二轮是算法CODE面，两道题。ML track的岗位不同于一般SWE，对算法code要求不高。所以基本上是LC上easy
level。遇上的两道题一个是问了number of islands，用dfs快速解决。另一个是find the
highest level of a tree，但是楼主刷题不勤，所以没有写完。这个埋下了祸根。。

3. 第三轮是吃饭！！！吃饭也算！！不过好办，使劲儿夸面官就可以了

4. 第四轮是 product design。让你设计一个好友推荐算法。LZ搞network所以非常在行。
我说推荐好友有两种：一种是你可能认识的。一种是你感兴趣的。分别讨论了两种好友如何找。
他还问了如果人特别多如何并行计算，怎么设计map-reduce。这轮虽然不懂mapreduce但是还是把面官忽悠得非常满意。

5.
第五轮是director的behavior面，大概就是问你喜欢code还是research，你觉得你在linkedin定位是啥。
你未来十年打算在linkedin怎么发展这类的~谈笑风生对答如流有明确的职业发展规划是特别讨喜的。

6. 最后一轮是 data coding，这个很多小伙伴不知道是啥。但其实就是data相关的coding，比较数学。
我抽到的一个经典题目，用一个bias的0，1生成器模拟一个筛子。因为楼主准备充分，所以一下子给出两个答案：

一个是变成1~6表示成二进制，每个位数生成一对bit,分别通过（0，1）和（1，0）来决定是0还是1，然后扔掉状况外的。

其实还有一个更好的方法，是利用二项式展开的系数。当p不是特别bias的时候，因为二项式系数:C_4^2= 6。
所以你可以生成4个bit, 对应的1只出现两次的情况概率是相等的，都是C_4^2p^2(1-p)^2。把这6种情况分别map到1~6即可。
如果p特别bias(p接近0或者1）。可以用二项式系数C_6_1，即生成6个bit，1-6对应不同的1-hot（或0-hot)vector。


还有一题是快速寻找median。这个很有意思，遵循标准方法即可。我用快排中的partition method O(n)时间就可以找到。
后来又一周，楼主收到加面通知，原因是coding弱。新的加面是如何在binary search tree当中插入和查找元素。
因为有Onsite的经验所以特地准备了一番。夸夸夸写的特别快。结果三哥面官说我没有交流最
后把我挂掉了？？？？这明明很基础啊....

anyway这就是linkedin的面经。考的基础但是非常全面，其实对外行还是非常友好的。
*/