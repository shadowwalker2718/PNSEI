//
// Created by Henry Wu on 11/13/18.
//

#ifndef PNSEI_SHORT_MESSAGE_FORMATTING_H
#define PNSEI_SHORT_MESSAGE_FORMATTING_H

#include "pnsei.h"

namespace _uber_msg{

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=457865&highlight=uber
 * 2018(10-12月) 码农类General 硕士 全职@uber - 内推 - 技术电面  | Pass | 在职跳槽
uber店面:
首先先吐槽一下不靠谱的recruitor.第一次打电话聊得好好的,结果等我想面试了,人找不到了.消失了至少3个礼拜!活不见人死不见尸!
 之后那哥们说出去玩了!你妹啊!你不会再找一个人替你!

1. 聊简历,话说uber的攻城狮真的很牛逼!超级有经.问了两个问题,每个问题都是我们工程上的痛点!所以好好准备简历!把所有细节都想到了!
2. 设计一个all way stop先到先走.可以把它当成OOD,大家发挥想象力!
3. uber需要给客户发短信,整条message可能会很长,他们就需要把一条长的短信分成很多个短的短信发出去.但是用户接受到的短信顺序可能和原顺
 序不一样,所以每条短信后边都要有一个（K_Branches/n)举例:"this is a message, this is a message, this is a message" -->
 第一条:"this is a message (1/3)",第二条:"this is a message (2/3)",第三条:"this is a message (3/3)",你的任
 务是写一个程序来计算每一个短信的内容.保证每条短信的字是完整的,而且每条短信要塞进去尽量多的字.注意（K_Branches/n)里边的n有可能是多位的.
 有可能是（2/5)... 也有可能是（100/1000)...

uber这家公司的面试真心好.很有意思.而且uber的攻城狮水平也很高!他们在大力扩张,想学东西的小伙伴,这里是不二的选择!但是我onsite挂了,
 挂的我哭笑不得.不过我需要绿卡,现在也有点不敢去startup.

最后,走过路过,别忘了给个大米.如果大家给的超过50颗,我就写一下我onsite的悲惨遭遇!绝对保证有借鉴意义,绝对保证精彩!
 * */

vector<string> msg_format(string s){
  vector<string> r;
  return r;
}

};

#endif //PNSEI_SHORT_MESSAGE_FORMATTING_H
