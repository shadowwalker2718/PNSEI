//
// Created by Henry Wu on 10/31/18.
//

#ifndef PNSEI_STOCK_RECONCILIATION_H
#define PNSEI_STOCK_RECONCILIATION_H

#include "pnsei.h"

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=271510&extra=&page=1
 * 楼主三月初找人推了addepar,这周一收到电面通知,定在了这周四,刚刚结束
只有一道题:给你一个txt file,格式如下:
D0-POS
APPL      100
GOOGL     200
Cash      10

D1-TRN
APPL    SL   50   30000
GOOGL   BY  200   10000

D1-POS
APPL       50
GOOGL      410
CASH       20000

DX-POS代表第X天的状态,比如D0-POS这一部分代表在第0天（开始时)手里有Apple 公司的100股,Google公司的200股,以及10刀现金

DX-TRN代表第X天的动作,比如D1-TRN这一系列动作代表第一天时我们卖出Apple公司的50股,收入30000刀;买入Google公司的200股,支出10000刀;
 然后D1-POS描述了第一天交易后的状态:手里还有Apple公司的50股,Google公司的400股,以及cash20000刀.

要求输出
DIFF
GOOGL     10
Cash         -10

代表经过上述过程之后,系统记录的股票和现金数量与实际数量的差别.比如经过上述操作后状态实际应该是apple公司50股,Google公司400股,
 现金20010刀,然而系统却记录成了Google 410 和现金20000.输出这个差别.

每一行都是string,每天的TRN 和 POS间都有空行分隔.求大神给个思路~

吐槽下,电面一共才一小时,刨去15分钟聊简历和问问题剩下的时间根本不够做一道新题,搞明白题意还需要时间啊
 ......也许他家真的只招best of the best== anyway move on 了

看在打了这么多字的份上求大米~~~~求RP!!!
 补充:
不会要求读文件.这部分会直接给.也不要求写文件,直接输出
题没啥难度, 注意代码写得漂不漂亮
 *
 *
 * 用key value 的map 存初始值 然后直接在读TRN的update map,最后在D1-POS的时候和map里的比较.
 * 这是偷懒的办法 最好提一下 读取操作和update操作分开写（Module Design)
 * */

namespace addepar_reconcile {
map<string, int> ticker2position;
double cash_balance;

void init() {
  ticker2position["APPL"] = 100;
  ticker2position["GOOG"] = 200;
  ticker2position["AMZN"] = 200;
  cash_balance = 10;
}

void trade(const string &ticker, string action, int volume, double cashflow) {
  if (action == "SL") {
    ticker2position[ticker] -= volume;
    cash_balance += cashflow;
  } else if (action == "BY") {
    ticker2position[ticker] += volume;
    cash_balance -= cashflow;
  }
}

map<string,int> reconcile() {
  // 1. get d1-pos info
  // Another method is to update map directly!
  map<string, int> eod_position;// ticker position
  map<string, int> diff;
  double eod_cash_balance;

  eod_position["APPL"] = 50;
  eod_position["GOOG"] = 410;
  eod_position["MSFT"] = 40;
  eod_cash_balance = 20000;

  // 2.output diff
  // get difference of two maps
  // https://stackoverflow.com/questions/24276045/how-to-find-the-difference-of-two-maps
  auto it1 = eod_position.begin(), it2 = eod_position.end();
  auto it3 = ticker2position.begin(), it4 = ticker2position.end();
  while (it1 != it2 && it3 != it4) {
    if (it1->first == it3->first) {
      if (it1->second != it3->second) {
        diff[it1->first] = it1->second - it3->second;
      }
      it1++, it3++;
    } else if (it1->first > it3->first) {
      diff[it3->first] = - it3->second;
      it3++;
    } else {
      diff[it1->first] = it1->second;
      it1++;
    }
  }
  while(it1!=it2){
    diff[it1->first] = it1->second;
    it1++;
  }
  while(it3!=it4){
    diff[it3->first] = -it3->second;
    it3++;
  }
  if (cash_balance != eod_cash_balance)
    diff["Cash"] = eod_cash_balance - cash_balance;
  return diff;
}

void test() {
  init();

  trade("APPL", "SL", 50, 30000);
  trade("GOOG", "BY", 200, 10000);

  auto diff=reconcile();
  cout << "DIFF" << endl;
  for(auto& pr: diff)
    cout << pr.first << " " << pr.second << endl;
}

}

#endif //PNSEI_STOCK_RECONCILIATION_H
