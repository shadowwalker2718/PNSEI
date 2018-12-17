//
// Created by Henry Wu on 11/6/18.
//

#ifndef PNSEI_CALCULATOR_H
#define PNSEI_CALCULATOR_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=454803&highlight=cruise
 *
 * 2018(10-12月) 码农类General 硕士 全职@Cruise - 内推 - 技术电面  | Other | fresh grad应届毕业生
地里老哥帮忙推的Cruise Infra Engineer,电面是一个Caltech的小哥,总共一个小时.前十五分钟聊了聊背景什么的,然后做题,计算器系列
1. 只有+和-的计算器
2. +, -, ()的计算器
3. 多项式计算器
第三个最后没完全写完,但是小哥说可以了,我知道你会了..

这家面试体验还是很不错的,小哥很友好,HR之前约电面啥的也都挺顺利的.
 *
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=448543&highlight=cruise
 * 2018(10-12月) 码农类General 硕士 全职@Cruise - 内推 - 技术电面  | Other | fresh grad应届毕业生
今天刚刚面了Cruise,湾区一家无人驾驶汽车公司,是找地里内推的,发发面经求有后续!

c++不太灵所以申的infra组,约了12点的电话,12点10分面试官才打过来,拜仁小哥.
一开始问简历问题,lz太久没看了反而有点卡壳,场面一度极为尴尬,好在面试官似乎不想纠结过多,给我发了个coderpad链接开始做题.
面经题做题网站尔尔斯,需要compile.一开始不带括号,followup就是带括号版本,和原题一样.第一问秒了,followup手抖出了点小bug,但及时改了过来
后来面试官似乎还对其他testcase有一点疑问,不过compile以后发现结果没任何问题,就随便让我问了几个问题然后结束了

求人品求过,这家看起来bar还挺高的

补充内容 (2018-10-16 06:14):
刚收到hr回信说挂了...说experience和skill set不是best fit...明明题都答出来了 有点无奈..算了move on
 * */
#include "henry.h"

namespace _224 {

/*class Solution {
public:
  int calculate(string s) {
    s.erase(std::remove(s.begin(), s.end(), ' '),s.end());
  }
};*/

// Only consider plus and minus operators
int sum_with_only_plus_minus(string s) { // 1+2-3, -1+2 == 1
  int r = 0, sign_of_next_calculation = 1, n = 0; // sign is for next calculation
  for (char c: s) {
    if (c == '-' || c =='+') { // always + here as we have sign
      r += sign_of_next_calculation * n;
      n = 0, sign_of_next_calculation = c=='-'?-1:1;
    } else if (isdigit(c)) {
      n = n * 10 + c - '0';
    }
  }
  r += n * sign_of_next_calculation; //!!
  return r;
}

class Solution {
  /* With plus minus and parenthesis operators, and NO multiplication and division
   * 那么就没啥计算的优先级之分了.于是这道题就变的没有那么复杂了.
   * 我们需要一个栈来辅助计算,用个变量sign来表示当前的符号,我们遍历给定的字符串s,如果遇到了数字,由于可能是个多位数,所
   * 以我们要用while循环把之后的数字都读进来,然后用sign*num来更新结果res;如果遇到了加号,则sign赋为1,如果遇到了符号,
   * 则赋为-1;如果遇到了左括号,则把当前结果res和符号sign压入栈,res重置为0,sign重置为1;如果遇到了右括号,结果res乘以
   * 栈顶的符号,栈顶元素出栈,结果res加上栈顶的数字,栈顶元素出栈.
   */
  // When see this parenthesis, we can think of DFS's parenthesis property(CLRS graph chapter),
  // which we can use stack of recursive function
public:
  int calculate(string s) {
    int r = 0, n = 0, sign = 1, L = s.size();
    stack<int> stk;
    for (int i = 0; i < L; ++i) {
      char c = s[i];
      if (isdigit(c)) {
        n = 10 * n + (c - '0');
      } else if (c == '+' || c == '-') {
        r += sign * n;
        n = 0, sign = (c == '+') ? 1 : -1;
      } else if (c == '(') {
        stk.push(r);
        stk.push(sign);
        r = 0, sign = 1; // reset
      } else if (c == ')') {
        r += sign * n;
        n = 0;
        r *= stk.top(), stk.pop();// top of stack is sign(1 or -1)
        // if(stk.top()==-1) r=-r; stk.pop();
        r += stk.top(), stk.pop();
      }
    }
    r += sign * n;
    return r;
  }
};

class Solution2 {
public:
  int calculate(string s) {
    int r = 0, n = 0, sign = 1;
    stack<pair<int, char>> st; // result,sign
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      if (isdigit(c)) {
        n = 10 * n + (c - '0');
      } else if (c == '+' || c == '-') {
        r += sign * n;
        n = 0;
        sign = (c == '+') ? 1 : -1;
      } else if (c == '(') {
        st.emplace(r, sign);
        r = 0, sign = 1; // clear states!
      } else if (c == ')') {
        r += sign * n;
        n = 0;
        auto pr = st.top();
        st.pop();
        r *= pr.second;
        r += pr.first;
      }
    }
    r += sign * n;
    return r;
  }
};

void test() {

  assert(sum_with_only_plus_minus("1+2-3") == 0);
  assert(sum_with_only_plus_minus("-3") == -3);
  assert(sum_with_only_plus_minus("-3-2") == -5);
  assert(sum_with_only_plus_minus("+0-2") == -2);

  Solution2 sln;
  assert(sln.calculate("1-(5)") == -4);
  assert(sln.calculate("-(5)") == -5);
}

}

#endif //PNSEI_CALCULATOR_H
